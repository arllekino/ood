#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "../Document/CDocument.h"
#include "../DocumentController/DocumentController.h"

TEST_CASE("DocumentController executes commands")
{
    const std::string TEST_TEMP_DIR = "/Users/miroslav.aktuganov/CLionProjects/ood/lab5/redactor/test/testSaveDir";
    auto doc = std::make_shared<CDocument>();
    DocumentController controller(doc);
    
    SECTION("InsertParagraph")
    {
        std::string input = "InsertParagraph end Test paragraph";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetItemsCount() == 1);
        REQUIRE(doc->GetItem(0).GetParagraph()->GetText() == "Test paragraph");
    }
    
    SECTION("SetTitle") {
        std::string input = "SetTitle Test Document";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetTitle().title == "Test Document");
    }
    
    SECTION("List command doesn't throw")
    {
        std::string input = "List";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        
        REQUIRE_NOTHROW(controller.ExecuteCommand(command));
    }
    
    SECTION("Save command")
    {
        doc->SetTitle(DocumentTitle{"Test Document"});
        doc->InsertParagraph("Test content", doc->GetItemsCount() + 1);
        
        std::string input = "Save " + TEST_TEMP_DIR + "/test_save";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        
        REQUIRE_NOTHROW(controller.ExecuteCommand(command));
        REQUIRE(std::filesystem::exists(TEST_TEMP_DIR + "/test_save/content.html"));
    }
}

TEST_CASE("DocumentController handles undo/redo")
{
    auto doc = std::make_shared<CDocument>();
    DocumentController controller(doc);
    
    SECTION("Undo/redo with paragraph insertion")
    {
        std::string input = "InsertParagraph end First paragraph";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetItemsCount() == 1);
        
        input = "Undo";
        iss = std::istringstream(input);
        command = CommandLineParser::Parse(iss);
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetItemsCount() == 0);
        
        input = "Redo";
        iss = std::istringstream(input);
        command = CommandLineParser::Parse(iss);
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetItemsCount() == 1);
    }
    
    SECTION("Undo/redo with title change")
    {
        std::string input = "SetTitle New Title";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetTitle().title == "New Title");
        
        input = "Undo";
        iss = std::istringstream(input);
        command = CommandLineParser::Parse(iss);
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetTitle().title.empty());
        
        input = "Redo";
        iss = std::istringstream(input);
        command = CommandLineParser::Parse(iss);
        controller.ExecuteCommand(command);
        
        REQUIRE(doc->GetTitle().title == "New Title");
    }
    
    SECTION("History limit works")
    {
        for (int i = 0; i < 15; ++i)
        {
            std::string input = "InsertParagraph end Paragraph " + std::to_string(i);
            std::istringstream iss(input);
            auto command = CommandLineParser::Parse(iss);
            controller.ExecuteCommand(command);
        }
        
        std::string input = "Undo";
        std::istringstream iss(input);
        auto command = CommandLineParser::Parse(iss);
        
        REQUIRE_NOTHROW(controller.ExecuteCommand(command));
    }
}