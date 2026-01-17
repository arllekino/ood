#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "../CommandLineParser/CommandLineParser.h"

TEST_CASE("CommandLineParserTest")
{
    SECTION("InsertParagraph with numeric position")
    {
        std::string input = "InsertParagraph 1|end Second paragraph";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::INSERT_PARAGRAPH);
        REQUIRE(std::holds_alternative<InsertParagraphParameters>(params));
        
        auto paragraphParams = std::get<InsertParagraphParameters>(params);
        REQUIRE(paragraphParams.pos.has_value());
        REQUIRE(paragraphParams.pos.value() == 1);
        REQUIRE(paragraphParams.text == "Second paragraph");
    }
    
    SECTION("InsertParagraph with end position")
    {
        std::string input = "InsertParagraph 2|end Third paragraph";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::INSERT_PARAGRAPH);
        REQUIRE(std::holds_alternative<InsertParagraphParameters>(params));
        
        auto paragraphParams = std::get<InsertParagraphParameters>(params);
        REQUIRE(paragraphParams.pos.has_value());
        REQUIRE(paragraphParams.pos.value() == 2);
        REQUIRE(paragraphParams.text == "Third paragraph");
    }
}

TEST_CASE("CommandLineParserTest1")
{
    SECTION("InsertImage with end position")
    {
        std::string input = "InsertImage end 100 150 test_image.png";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::INSERT_IMAGE);
        REQUIRE(std::holds_alternative<InsertImageParameters>(params));
        
        auto imageParams = std::get<InsertImageParameters>(params);
        REQUIRE_FALSE(imageParams.pos.has_value());
        REQUIRE(imageParams.width == 100);
        REQUIRE(imageParams.height == 150);
        REQUIRE(imageParams.path == "test_image.png");
    }
    
    SECTION("InsertImage with numeric position")
    {
        std::string input = "InsertImage 1|end 200 300 image.jpg";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::INSERT_IMAGE);
        REQUIRE(std::holds_alternative<InsertImageParameters>(params));
        
        auto imageParams = std::get<InsertImageParameters>(params);
        REQUIRE(imageParams.pos.has_value());
        REQUIRE(imageParams.pos.value() == 1);
        REQUIRE(imageParams.width == 200);
        REQUIRE(imageParams.height == 300);
    }
}

TEST_CASE("CommandLineParser SetTitle commands")
{
    std::string input = "SetTitle Document Title";
    std::istringstream iss(input);
    
    auto [action, params] = CommandLineParser::Parse(iss);
    
    REQUIRE(action == ActionType::SET_TITLE);
    REQUIRE(std::holds_alternative<DocumentTitle>(params));
    
    auto title = std::get<DocumentTitle>(params);
    REQUIRE(title.title == "Document Title");
}

TEST_CASE("CommandLineParser ReplaceText commands")
{
    std::string input = "ReplaceText 1 New text content";
    std::istringstream iss(input);
    
    auto [action, params] = CommandLineParser::Parse(iss);
    
    REQUIRE(action == ActionType::REPLACE_TEXT);
    REQUIRE(std::holds_alternative<ReplaceTextParameters>(params));
    
    auto replaceParams = std::get<ReplaceTextParameters>(params);
    REQUIRE(replaceParams.pos == 0);
    REQUIRE(replaceParams.text == "New text content");
}

TEST_CASE("CommandLineParser ResizeImage commands")
{
    std::string input = "ResizeImage 1 400 500";
    std::istringstream iss(input);
    
    auto [action, params] = CommandLineParser::Parse(iss);
    
    REQUIRE(action == ActionType::RESIZE_IMAGE);
    REQUIRE(std::holds_alternative<ResizeImageParameters>(params));
    
    auto resizeParams = std::get<ResizeImageParameters>(params);
    REQUIRE(resizeParams.pos == 0);
    REQUIRE(resizeParams.width == 400);
    REQUIRE(resizeParams.height == 500);
}

TEST_CASE("CommandLineParser DeleteItem commands")
{
    std::string input = "DeleteItem 1";
    std::istringstream iss(input);
    
    auto [action, params] = CommandLineParser::Parse(iss);
    
    REQUIRE(action == ActionType::DELETE_ITEM);
    REQUIRE(std::holds_alternative<Position>(params));
    
    auto position = std::get<Position>(params);
    REQUIRE(position == 0);
}

TEST_CASE("CommandLineParser Save commands")
{
    std::string input = "Save document.html";
    std::istringstream iss(input);
    
    auto [action, params] = CommandLineParser::Parse(iss);
    
    REQUIRE(action == ActionType::SAVE);
    REQUIRE(std::holds_alternative<SaveDocumentPath>(params));
    
    auto savePath = std::get<SaveDocumentPath>(params);
    REQUIRE(savePath == "document.html");
}

TEST_CASE("CommandLineParser simple commands")
{
    SECTION("List command")
    {
        std::string input = "List";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::LIST);
        REQUIRE(std::holds_alternative<std::monostate>(params));
    }
    
    SECTION("Undo command")
    {
        std::string input = "Undo";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::UNDO);
        REQUIRE(std::holds_alternative<std::monostate>(params));
    }
    
    SECTION("Redo command")
    {
        std::string input = "Redo";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::REDO);
        REQUIRE(std::holds_alternative<std::monostate>(params));
    }
    
    SECTION("Help command")
    {
        std::string input = "Help";
        std::istringstream iss(input);
        
        auto [action, params] = CommandLineParser::Parse(iss);
        
        REQUIRE(action == ActionType::HELP);
        REQUIRE(std::holds_alternative<std::monostate>(params));
    }
}

TEST_CASE("CommandLineParser invalid commands")
{
    SECTION("Unknown command")
    {
        std::string input = "InvalidCommand";
        std::istringstream iss(input);
        
        REQUIRE_THROWS_AS(CommandLineParser::Parse(iss), std::invalid_argument);
    }
}