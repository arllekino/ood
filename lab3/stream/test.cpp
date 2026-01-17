#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <fstream>
#include <vector>
#include <array>

#include "./Input/CFileInputStream.h"
#include "./Input/CDecryptionInputStream.h"
#include "./Input/DecompressionInputStream.h"
#include "./Output/CFileOutputStream.h"
#include "./Output/CEncryptionOutputStream.h"
#include "./Output/CCompressionOutputStream.h"
#include "./CStreamFactory.h"

TEST_CASE("CFileInputStream")
{
    const std::string testFileName = "test_input.bin";
    std::ofstream testFile(testFileName, std::ios::binary);
    const std::vector<uint8_t> testData = {0x01, 0x02, 0x03, 0x04, 0x05};
    testFile.write(reinterpret_cast<const char*>(testData.data()), static_cast<std::streamsize>(testData.size()));
    testFile.close();

    SECTION("Read byte by byte")
    {
        CFileInputStream stream(testFileName);

        REQUIRE_FALSE(stream.IsEOF());
        REQUIRE(stream.ReadByte() == 0x01);
        REQUIRE(stream.ReadByte() == 0x02);
        REQUIRE(stream.ReadByte() == 0x03);
        REQUIRE(stream.ReadByte() == 0x04);
        REQUIRE(stream.ReadByte() == 0x05);

        REQUIRE_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
        REQUIRE(stream.IsEOF());
    }

    SECTION("Read block")
    {
        CFileInputStream stream(testFileName);
        std::array<uint8_t, 3> buffer{};

        const auto read = stream.ReadBlock(buffer.data(), 3);
        REQUIRE(read == 3);
        REQUIRE(buffer[0] == 0x01);
        REQUIRE(buffer[1] == 0x02);
        REQUIRE(buffer[2] == 0x03);

        const auto read2 = stream.ReadBlock(buffer.data(), 3);
        REQUIRE(read2 == 2);
        REQUIRE(buffer[0] == 0x04);
        REQUIRE(buffer[1] == 0x05);
    }

    SECTION("File not found exception")
    {
        REQUIRE_THROWS_AS(CFileInputStream("nonexistent.file"), std::invalid_argument);
    }

    std::remove(testFileName.c_str());
}

TEST_CASE("CFileOutputStream")
{
    const std::string testFileName = "test_output.bin";

    SECTION("Write byte by byte")
    {
        CFileOutputStream stream(testFileName);

        stream.WriteByte(0x10);
        stream.WriteByte(0x20);
        stream.WriteByte(0x30);
        stream.Close();

        std::ifstream verifyFile(testFileName, std::ios::binary);
        REQUIRE(verifyFile.get() == 0x10);
        REQUIRE(verifyFile.get() == 0x20);
        REQUIRE(verifyFile.get() == 0x30);
        verifyFile.close();
    }

    SECTION("Write block")
    {
        CFileOutputStream stream(testFileName);
        const std::vector<uint8_t> data = {0xAA, 0xBB, 0xCC, 0xDD};

        stream.WriteBlock(data.data(), static_cast<std::streamsize>(data.size()));
        stream.Close();

        std::ifstream verifyFile(testFileName, std::ios::binary);
        std::vector<uint8_t> readData(4);
        verifyFile.read(reinterpret_cast<char*>(readData.data()), 4);

        REQUIRE(readData[0] == 0xAA);
        REQUIRE(readData[1] == 0xBB);
        REQUIRE(readData[2] == 0xCC);
        REQUIRE(readData[3] == 0xDD);
        verifyFile.close();
    }

    std::remove(testFileName.c_str());
}

TEST_CASE("Compression and Decompression")
{
    const std::string testFileName = "test_compressed.bin";

    SECTION("Compress and decompress repeated data")
    {
        const std::vector<uint8_t> originalData(10, 0xAA);

        {
            auto fileStream = std::make_unique<CFileOutputStream>(testFileName);
            CCompressionOutputStream compressedStream(std::move(fileStream));

            for (const auto byte : originalData)
            {
                compressedStream.WriteByte(byte);
            }
            compressedStream.Close();
        }

        {
            auto fileStream = std::make_unique<CFileInputStream>(testFileName);
            DecompressionStream decompressedStream(std::move(fileStream));

            std::vector<uint8_t> decompressedData;
            while (!decompressedStream.IsEOF())
            {
                try
                {
                    decompressedData.push_back(decompressedStream.ReadByte());
                }
                catch (const std::ios_base::failure&)
                {
                    break;
                }
            }

            REQUIRE(decompressedData == originalData);
        }
    }

    SECTION("Compress and decompress mixed data")
    {
        const std::vector<uint8_t> originalData = {0x01, 0x01, 0x01, 0x02, 0x03, 0x03, 0x04};

        {
            auto fileStream = std::make_unique<CFileOutputStream>(testFileName);
            CCompressionOutputStream compressedStream(std::move(fileStream));

            compressedStream.WriteBlock(originalData.data(), static_cast<std::streamsize>(originalData.size()));
            compressedStream.Close();
        }

        {
            auto fileStream = std::make_unique<CFileInputStream>(testFileName);
            DecompressionStream decompressedStream(std::move(fileStream));

            std::vector<uint8_t> decompressedData;
            std::array<uint8_t, 10> buffer{};

            while (!decompressedStream.IsEOF())
            {
                const auto read = decompressedStream.ReadBlock(buffer.data(), buffer.size());
                for (std::streamsize i = 0; i < read; ++i)
                {
                    decompressedData.push_back(buffer[i]);
                }
            }

            REQUIRE(decompressedData == originalData);
        }
    }

    SECTION("Handle 0xFF marker")
    {
        const std::vector<uint8_t> originalData = {0xFF, 0xFF, 0xFF, 0x01, 0xFF};

        {
            auto fileStream = std::make_unique<CFileOutputStream>(testFileName);
            CCompressionOutputStream compressedStream(std::move(fileStream));

            for (const auto byte : originalData)
            {
                compressedStream.WriteByte(byte);
            }
            compressedStream.Close();
        }

        {
            auto fileStream = std::make_unique<CFileInputStream>(testFileName);
            DecompressionStream decompressedStream(std::move(fileStream));

            std::vector<uint8_t> decompressedData;
            while (!decompressedStream.IsEOF())
            {
                try
                {
                    decompressedData.push_back(decompressedStream.ReadByte());
                }
                catch (const std::ios_base::failure&)
                {
                    break;
                }
            }

            REQUIRE(decompressedData == originalData);
        }
    }

    std::remove(testFileName.c_str());
}

TEST_CASE("CDecryptionInputStream - Edge Cases")
{
    const std::string testFileName = "test_decrypt_edge.bin";
    const uint32_t testKey = 54321;

    SECTION("Empty file")
    {
        std::ofstream testFile(testFileName, std::ios::binary);
        testFile.close();

        auto fileStream = std::make_unique<CFileInputStream>(testFileName);
        CDecryptionInputStream decryptedStream(std::move(fileStream), testKey);

        REQUIRE_THROWS_AS(decryptedStream.ReadByte(), std::ios_base::failure);
        REQUIRE(decryptedStream.IsEOF());
    }

    SECTION("Single byte")
    {
        {
            auto fileStream = std::make_unique<CFileOutputStream>(testFileName);
            CEncryptionOutputStream encryptedStream(std::move(fileStream), testKey);
            encryptedStream.WriteByte(0x42);
            encryptedStream.Close();
        }

        {
            auto fileStream = std::make_unique<CFileInputStream>(testFileName);
            CDecryptionInputStream decryptedStream(std::move(fileStream), testKey);

            REQUIRE_FALSE(decryptedStream.IsEOF());
            const auto byte = decryptedStream.ReadByte();
            REQUIRE(byte == 0x42);
            REQUIRE_THROWS_AS(decryptedStream.ReadByte(), std::ios_base::failure);
            REQUIRE(decryptedStream.IsEOF());
        }
    }

    std::remove(testFileName.c_str());
}

TEST_CASE("DecompressionInputStream - Edge Cases")
{
    const std::string testFileName = "test_decompress_edge.bin";

    SECTION("Empty file")
    {
        std::ofstream testFile(testFileName, std::ios::binary);
        testFile.close();

        auto fileStream = std::make_unique<CFileInputStream>(testFileName);
        DecompressionStream decompressedStream(std::move(fileStream));

        REQUIRE_THROWS_AS(decompressedStream.ReadByte(), std::ios_base::failure);
        REQUIRE(decompressedStream.IsEOF());
    }

    SECTION("Invalid compression exception")
    {
        std::ofstream testFile(testFileName, std::ios::binary);
        const std::vector<uint8_t> invalidData = {0xFF};
        testFile.write(reinterpret_cast<const char*>(invalidData.data()), static_cast<std::streamsize>(invalidData.size()));
        testFile.close();

        auto fileStream = std::make_unique<CFileInputStream>(testFileName);
        DecompressionStream decompressedStream(std::move(fileStream));

        REQUIRE_THROWS_AS(decompressedStream.ReadByte(), std::ios_base::failure);
    }

    std::remove(testFileName.c_str());
}
// encrypt decrypt