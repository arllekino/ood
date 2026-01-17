#pragma once
#include <fstream>

#include "IOutputStream.h"

class CFileOutputStream : public IOutputStream
{
public:
    explicit CFileOutputStream(const std::string& filename) : m_file(filename, std::ios::binary)
    {
        if (!m_file.is_open())
        {
            throw std::ios_base::failure("Failed to open file: " + filename);
        }
    };

    void WriteByte(const uint8_t data) override
    {
        if (!m_file.put(static_cast<char>(data)))
        {
            throw std::ios_base::failure("Failed to write to file");
        }
    }

    void WriteBlock(const void *srcData, std::streamsize dataSize) override
    {
        const auto data = static_cast<const char*>(srcData);
        m_file.write(data, dataSize);

        if (m_file.bad())
        {
            throw std::ios_base::failure("Failed to write to file");
        }
    }

    void Close() override
    {
        m_file.close();
    }
private:
    std::ofstream m_file;
};