#pragma once
#include <cstdint>
#include <ios>

class IOutputStream
{
public:
    virtual void WriteByte(uint8_t data) = 0;
    virtual void WriteBlock(const void* srcData, std::streamsize dataSize) = 0;
    virtual void Close() = 0;
    virtual ~IOutputStream() = default;
};

using IOutputStreamPtr = std::unique_ptr<IOutputStream>;
