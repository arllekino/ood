#pragma once
#include "IInputStream.h"

class DecompressionStream : public IInputStream
{
public:
    explicit DecompressionStream(IInputStreamPtr&& stream)
        : m_stream(std::move(stream)), m_currentByte(0), m_repeatCount(0)
    {
    }

    bool IsEOF() override
    {
        return m_repeatCount == 0 && m_stream->IsEOF();
    }

    uint8_t ReadByte() override
    {
        if (m_repeatCount > 0)
        {
            m_repeatCount--;
            return m_currentByte;
        }

        if (m_stream->IsEOF())
        {
            throw std::ios_base::failure("EOF reached");
        }

        const auto byte = m_stream->ReadByte();

        if (byte == 0xFF)
        {
            if (m_stream->IsEOF())
            {
                throw std::ios_base::failure("Unexpected EOF after compression marker");
            }

            const auto count = m_stream->ReadByte();

            if (count == 0x01)
            {
                return 0xFF;
            }

            if (m_stream->IsEOF())
            {
                throw std::ios_base::failure("Unexpected EOF in compressed sequence");
            }

            m_currentByte = m_stream->ReadByte();
            m_repeatCount = count - 1;
            return m_currentByte;
        }
        return byte;
    }

    std::streamsize ReadBlock(void* dstData, const std::streamsize dataSize) override
    {
        auto* buffer = static_cast<uint8_t*>(dstData);
        std::streamsize read = 0;

        try
        {
            while (read < dataSize && !IsEOF())
            {
                buffer[read] = ReadByte();
                read++;
            }
        }
        catch (const std::ios_base::failure& e)
        {
            if (read == 0)
            {
                throw;
            }
        }

        return read;
    }

private:
    IInputStreamPtr m_stream;
    uint8_t m_currentByte;
    uint8_t m_repeatCount;
};