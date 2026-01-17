#include <catch2/catch_test_macros.hpp>
#include "../Document/CDocument.h"
#include "../Command/InsertParagraphCommand.h"
#include "../Command/SetTitleCommand.h"
#include "../Command/ReplaceTextCommand.h"

TEST_CASE("InsertParagraphCommand")
{
    auto doc = std::make_shared<CDocument>();
    InsertParagraphParameters params{std::nullopt, "Test paragraph"};
    InsertParagraphCommand command(doc, params);

    SECTION("Execute")
    {
        command.Execute();
        REQUIRE(doc->GetItemsCount() == 1);
        REQUIRE(doc->GetItem(0).GetParagraph()->GetText() == "Test paragraph");
    }

    SECTION("Unexecute")
    {
        command.Execute();
        REQUIRE(doc->GetItemsCount() == 1);

        command.Unexecute();
        REQUIRE(doc->GetItemsCount() == 0);
    }
}

TEST_CASE("SetTitleCommand")
{
    auto doc = std::make_shared<CDocument>();
    doc->SetTitle(DocumentTitle{"Old Title"});

    SetTitleCommand command(doc, DocumentTitle{"New Title"});

    SECTION("Execute")
    {
        command.Execute();
        REQUIRE(doc->GetTitle().title == "New Title");
    }

    SECTION("Unexecute")
    {
        command.Execute();
        command.Unexecute();
        REQUIRE(doc->GetTitle().title == "Old Title");
    }
}

TEST_CASE("ReplaceTextCommand")
{
    const std::string TEST_TEMP_DIR = "/Users/miroslav.aktuganov/CLionProjects/ood/lab5/redactor/test/testSaveDir";

    auto doc = std::make_shared<CDocument>();
    doc->InsertParagraph("Old text", doc->GetItemsCount() + 1);

    ReplaceTextParameters params{0, "New text"};
    ReplaceTextCommand command(doc, params);

    SECTION("Execute")
    {
        command.Execute();
        REQUIRE(doc->GetItem(0).GetParagraph()->GetText() == "New text");
    }

    SECTION("Unexecute") {
        command.Execute();
        command.Unexecute();
        REQUIRE(doc->GetItem(0).GetParagraph()->GetText() == "Old text");
    }
}