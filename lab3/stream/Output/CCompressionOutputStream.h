#pragma once
#include <vector>
#include "IOutputStream.h"

class CCompressionOutputStream : public IOutputStream
{
public:
    explicit CCompressionOutputStream(IOutputStreamPtr&& stream)
        : m_stream(std::move(stream))
    {
    }

    void WriteByte(uint8_t data) override
    {
        if (m_buffer.empty() || m_buffer.back().first != data || m_buffer.back().second == 255)
        {
            m_buffer.emplace_back(data, 1);
        }
        else
        {
            m_buffer.back().second++;
        }

        if (m_buffer.size() >= 100)
        {
            FlushBuffer();
        }
    }

    void WriteBlock(const void* srcData, const std::streamsize size) override
    {
        const auto* data = static_cast<const uint8_t*>(srcData);
        for (std::streamsize i = 0; i < size; ++i)
        {
            WriteByte(data[i]);
        }
    }

    void Close() override
    {
        FlushBuffer();
        m_stream->Close();
    }

private:
    IOutputStreamPtr m_stream;
    std::vector<std::pair<uint8_t, uint8_t>> m_buffer{};

    void FlushBuffer()
    {
        for (const auto& entry : m_buffer)
        {
            if (entry.second > 3 || entry.first == 0xFF)
            {
                m_stream->WriteByte(0xFF);
                m_stream->WriteByte(entry.second);
                m_stream->WriteByte(entry.first);
            }
            else
            {
                for (int i = 0; i < entry.second; ++i)
                {
                    if (entry.first == 0xFF)
                    {
                        m_stream->WriteByte(0xFF);
                        m_stream->WriteByte(0x01);
                    }
                    else
                    {
                        m_stream->WriteByte(entry.first);
                    }
                }
            }
        }
        m_buffer.clear();
    }
};
