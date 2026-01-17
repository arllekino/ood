#pragma once
#include <fstream>

#include "IInputStream.h"

class CFileInputStream : public IInputStream
{
public:
    explicit CFileInputStream(const std::string& fileName)
        : m_file(fileName, std::ios::binary)
    {
        if (!m_file.is_open())
        {
            throw std::invalid_argument("File open failed");
        }
    }

    bool IsEOF() override
    {
        return m_file.eof();
    }

    uint8_t ReadByte() override
    {
        char byte;
        if (!m_file.get(byte))
        {
            if (m_file.eof())
            {
                throw std::ios_base::failure("EOF reached");
            }
            throw std::ios_base::failure("Read error");
        }
        return static_cast<uint8_t>(byte);
    }

    std::streamsize ReadBlock(void *dstData, const std::streamsize dataSize) override
    {
        m_file.read(static_cast<char*>(dstData), dataSize);
        const std::streamsize read = m_file.gcount();

        if (m_file.bad())
        {
            throw std::ios_base::failure("Read error");
        }

        return read;
    }
private:
    std::ifstream m_file;
};
