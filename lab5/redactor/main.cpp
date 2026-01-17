//
// Created by Miroslav Aktuganov on 22.10.2025.
//

#include <iostream>
#include <sstream>
#include <string>

#include "Document/CDocument.h"
#include "DocumentController/DocumentController.h"

int main()
{
    std::string lineCommand;
    const auto document = std::make_shared<CDocument>();
    auto documentController = DocumentController(document);
    auto parser = CommandLineParser();

    while (std::getline(std::cin, lineCommand))
    {
        std::istringstream iss(lineCommand);
        try
        {
            const auto command = parser.Parse(iss);
            documentController.ExecuteCommand(command);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
