#pragma once
#include <random>
#include "IOutputStream.h"

class CEncryptionOutputStream : public IOutputStream
{
public:
    CEncryptionOutputStream(IOutputStreamPtr&& stream, const uint32_t key)
        : m_stream(std::move(stream))
    {
        GenerateSubstitutionTable(key, m_encryptionTable);
    }

    void WriteByte(const uint8_t data) override
    {
        m_stream->WriteByte(m_encryptionTable[data]);
    }

    void WriteBlock(const void *srcData, const std::streamsize dataSize) override
    {
        const auto* data = static_cast<const uint8_t*>(srcData);
        for (std::streamsize i = 0; i < dataSize; ++i)
        {
            WriteByte(data[i]);
        }
    }

    void Close() override
    {
        m_stream->Close();
    }
private:
    IOutputStreamPtr m_stream;
    std::array<uint8_t, 256> m_encryptionTable{};

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