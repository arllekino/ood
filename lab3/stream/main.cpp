#include <iostream>

#include "CStreamFactory.h"

int main(int argc, char* argv[])
{
    if (argc < 3 || strcmp(argv[1], "transform") != 0)
    {
        std::cerr << "Usage: transform [options] <input-file> <output-file>\n";
        std::cout << argv[1] << "\n";
        return 1;
    }

    std::vector<uint32_t> encryptKeys;
    std::vector<uint32_t> decryptKeys;
    bool compress = false;
    bool decompress = false;
    std::string inputFile, outputFile;

    for (int i = 2; i < argc; ++i)
    {
        std::string arg = argv[i];
        
        if (arg == "--encrypt" && i + 1 < argc)
        {
            encryptKeys.push_back(std::stoul(argv[++i]));
        }
        else if (arg == "--decrypt" && i + 1 < argc)
        {
            decryptKeys.push_back(std::stoul(argv[++i]));
        }
        else if (arg == "--compress")
        {
            compress = true;
        }
        else if (arg == "--decompress")
        {
            decompress = true;
        }
        else if (inputFile.empty())
        {
            inputFile = arg;
        }
        else if (outputFile.empty())
        {
            outputFile = arg;
        }
        else
        {
            std::cerr << "Invalid argument: " << arg << "\n";
            std::cout << inputFile << "\n";
            std::cout << outputFile << "\n";
            return 1;
        }
    }

    try
    {
        auto inputStream = StreamFactory::CreateInputStream(inputFile, decryptKeys, decompress);
        auto outputStream = StreamFactory::CreateOutputStream(outputFile, encryptKeys, compress);

        constexpr std::streamsize bufferSize = 4096;
        std::vector<uint8_t> buffer(bufferSize);

        while (!inputStream->IsEOF())
        {
            if (const std::streamsize read = inputStream->ReadBlock(buffer.data(), bufferSize); read > 0)
            {
                outputStream->WriteBlock(buffer.data(), read);
            }
        }
        
        outputStream->Close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
