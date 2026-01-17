#pragma once
#include <random>
#include "IInputStream.h"

class CDecryptionInputStream : public IInputStream
{
public:
    CDecryptionInputStream(IInputStreamPtr&& inputStream, const uint32_t key)
        : m_stream(std::move(inputStream))
    {
        std::array<uint8_t, 256> encryptionTable{};
        GenerateSubstitutionTable(key, encryptionTable);

        for (uint32_t i = 0; i < 256; i++)
        {
            m_decryptionTable[encryptionTable[i]] = i;
        }
    }

    bool IsEOF() override
    {
        return m_stream->IsEOF();
    }

    uint8_t ReadByte() override
    {
        const uint8_t encrypted = m_stream->ReadByte();
        return m_decryptionTable[encrypted];
    }

    std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override
    {
        auto* buffer = static_cast<uint8_t*>(dstBuffer);
        std::streamsize read = 0;

        while (read < size && !IsEOF())
        {
            buffer[read] = ReadByte();
            ++read;
        }

        return read;
    }
private:
    IInputStreamPtr m_stream;
    std::array<uint8_t, 256> m_decryptionTable{};

    static void GenerateSubstitutionTable(const uint32_t key, std::array<uint8_t, 256>& table)
    {
        for (int i = 0; i < 256; ++i)
        {
            table[i] = static_cast<uint8_t>(i);
        }

        std::mt19937 generator(key);
        std::ranges::shuffle(table, generator);
    }
};