#pragma once
#include <string>

struct DocumentTitle
{
    std::string title;

    void operator=(const DocumentTitle& other)
    {
        title = other.title;
    }
};