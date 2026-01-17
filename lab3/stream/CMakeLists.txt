add_executable(Stream main.cpp Input/IInputStream.h
        Input/CFileInputStream.h
        Output/IOutputStream.h
        Output/CFileOutputStream.h
        Output/CEncryptionOutputStream.h
        Input/CDecryptionInputStream.h
        Output/CCompressionOutputStream.h
        Input/DecompressionInputStream.h
        CStreamFactory.h)

add_executable(TestStream test.cpp
        Input/IInputStream.h
        Input/CFileInputStream.h
        Output/IOutputStream.h
        Output/CFileOutputStream.h
        Output/CEncryptionOutputStream.h
        Input/CDecryptionInputStream.h
        Output/CCompressionOutputStream.h
        Input/DecompressionInputStream.h
        CStreamFactory.h)

target_link_libraries(TestStream PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(TestStream)