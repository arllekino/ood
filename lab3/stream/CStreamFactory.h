#pragma once

#include <ranges>

#include "Input/CDecryptionInputStream.h"
#include "Input/CFileInputStream.h"
#include "Input/DecompressionInputStream.h"
#include "Input/IInputStream.h"
#include "Output/CCompressionOutputStream.h"
#include "Output/CEncryptionOutputStream.h"
#include "Output/CFileOutputStream.h"
#include "Output/IOutputStream.h"

using IInputStreamPtr = IInputStreamPtr;
using IOutputDataStreamPtr = IOutputStreamPtr;

class StreamFactory
{
public:
    static IInputStreamPtr CreateInputStream(
        const std::string& filename,
        const std::vector<uint32_t>& decryptKeys,
        const bool decompress)
    {
        IInputStreamPtr stream = std::make_unique<CFileInputStream>(filename);

        for (unsigned int decryptKey : std::ranges::reverse_view(decryptKeys))
        {
            stream = std::make_unique<CDecryptionInputStream>(std::move(stream), decryptKey);
        }

        if (decompress)
        {
            stream = std::make_unique<DecompressionStream>(std::move(stream));
        }

        return stream;
    }

    static IOutputDataStreamPtr CreateOutputStream(
        const std::string& filename,
        const std::vector<uint32_t>& encryptKeys,
        const bool compress)
    {
        IOutputDataStreamPtr stream = std::make_unique<CFileOutputStream>(filename);

        for (uint32_t key : encryptKeys)
        {
            stream = std::make_unique<CEncryptionOutputStream>(std::move(stream), key);
        }

        if (compress)
        {
            stream = std::make_unique<CCompressionOutputStream>(std::move(stream));
        }

        return stream;
    }
};