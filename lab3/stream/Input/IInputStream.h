#pragma once
#include <cstdint>
#include <ios>

class IInputStream
{
public:
    virtual bool IsEOF() = 0;
    virtual uint8_t ReadByte() = 0;
    virtual std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) = 0;
    virtual ~IInputStream() = default;
};

using IInputStreamPtr = std::unique_ptr<IInputStream>;
