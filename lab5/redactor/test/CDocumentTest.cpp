#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <filesystem>
#include "../Document/CDocument.h"

TEST_CASE("CDocument manages paragraphs correctly")
{
    const std::string TEST_TEMP_DIR = "/Users/miroslav.aktuganov/CLionProjects/ood/lab5/redactor/test/testSaveDir";
    CDocument doc;

    SECTION("Insert paragraph at end")
    {
        doc.InsertParagraph("First paragraph", doc.GetItemsCount() + 1);
        
        REQUIRE(doc.GetItemsCount() == 1);
        auto item = doc.GetItem(0);
        REQUIRE(item.GetParagraph() != nullptr);
        REQUIRE(item.GetParagraph()->GetText() == "First paragraph");
        REQUIRE(item.GetImage() == nullptr);
    }
    
    SECTION("Insert paragraph at specific position")
    {
        doc.InsertParagraph("Third", doc.GetItemsCount() + 1);
        doc.InsertParagraph("Second", 1);
        doc.InsertParagraph("First", 1);
        
        REQUIRE(doc.GetItemsCount() == 3);
        REQUIRE(doc.GetItem(0).GetParagraph()->GetText() == "First");
        REQUIRE(doc.GetItem(1).GetParagraph()->GetText() == "Second");
        REQUIRE(doc.GetItem(2).GetParagraph()->GetText() == "Third");
    }
    
    SECTION("Insert paragraph at invalid position throws")
    {
        doc.InsertParagraph("First", doc.GetItemsCount() + 1);
        
        REQUIRE_THROWS_AS(doc.InsertParagraph("Invalid", 5), std::out_of_range);
    }
    
    SECTION("Delete paragraph")
    {
        doc.InsertParagraph("First", doc.GetItemsCount() + 1);
        doc.InsertParagraph("Second", doc.GetItemsCount() + 1);
        
        REQUIRE(doc.GetItemsCount() == 2);
        doc.DeleteItem(0);
        REQUIRE(doc.GetItemsCount() == 1);
        REQUIRE(doc.GetItem(0).GetParagraph()->GetText() == "Second");
    }
    
    SECTION("Delete invalid position throws")
    {
        doc.InsertParagraph("First", doc.GetItemsCount() + 1);
        
        REQUIRE_THROWS_AS(doc.DeleteItem(5), std::out_of_range);
    }
    
    SECTION("Get item at invalid index throws")
    {
        REQUIRE_THROWS_AS(doc.GetItem(0), std::out_of_range);
    }
}

TEST_CASE("CDocument manages title correctly")
{
    CDocument doc;
    
    SECTION("Set and get title")
    {
        DocumentTitle title{"Test Document"};
        doc.SetTitle(title);
        
        REQUIRE(doc.GetTitle().title == "Test Document");
    }
    
    SECTION("Title is empty by default")
    {
        REQUIRE(doc.GetTitle().title.empty());
    }
    
    SECTION("Update title")
    {
        doc.SetTitle(DocumentTitle{"First Title"});
        doc.SetTitle(DocumentTitle{"Second Title"});
        
        REQUIRE(doc.GetTitle().title == "Second Title");
    }
}

TEST_CASE("CDocument saves correctly", "[CDocument]")
{
    const std::string TEST_TEMP_DIR = "/Users/miroslav.aktuganov/CLionProjects/ood/lab5/redactor/test/testSaveDir";
    CDocument doc;
    const std::string savePath = TEST_TEMP_DIR + "/test_document";
    
    SECTION("Save empty document")
    {
        doc.SetTitle(DocumentTitle{"Test Title"});
        doc.Save(savePath);
        
        REQUIRE(std::filesystem::exists(savePath + "/content.html"));
        
        std::ifstream titleFile(savePath + "/title.txt");

        std::ifstream htmlFile(savePath + "/content.html");
        std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), 
                               std::istreambuf_iterator<char>());
        REQUIRE(htmlContent.find("Test Title") != std::string::npos);
    }
    
    SECTION("Save document with paragraphs")
    {
        doc.SetTitle(DocumentTitle{"Document with paragraphs"});
        doc.InsertParagraph("First paragraph", doc.GetItemsCount() + 1);
        doc.InsertParagraph("Second paragraph", doc.GetItemsCount() + 1);
        
        doc.Save(savePath);
        
        std::ifstream htmlFile(savePath + "/content.html");
        std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), 
                               std::istreambuf_iterator<char>());
        
        REQUIRE(htmlContent.find("First paragraph") != std::string::npos);
        REQUIRE(htmlContent.find("Second paragraph") != std::string::npos);
        REQUIRE(htmlContent.find("&lt;") == std::string::npos);
    }
    
    SECTION("Save with HTML escaping")
    {
        doc.SetTitle(DocumentTitle{"Title with <tags> & symbols"});
        doc.InsertParagraph("Text with <html> & \"quotes\" 'apostrophes'", doc.GetItemsCount() + 1);
        
        doc.Save(savePath);
        
        std::ifstream htmlFile(savePath + "/content.html");
        std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)), 
                               std::istreambuf_iterator<char>());
        
        REQUIRE(htmlContent.find("&lt;tags&gt;") != std::string::npos);
        REQUIRE(htmlContent.find("&amp;") != std::string::npos);
        REQUIRE(htmlContent.find("&quot;") != std::string::npos);
        REQUIRE(htmlContent.find("&#39;") != std::string::npos);
    }
}

TEST_CASE("CDocument handles images", "[CDocument]")
{
    const std::string TEST_TEMP_DIR = "/Users/miroslav.aktuganov/CLionProjects/ood/lab5/redactor/test/testSaveDir";
    CDocument doc;
    
    SECTION("Insert image validation") {
        const std::string testImagePath = TEST_TEMP_DIR + "/test_image.txt";
        std::ofstream testImage(testImagePath);
        testImage << "fake image content";
        testImage.close();
        
        SECTION("Valid image dimensions")
        {
            doc.InsertImage(testImagePath, 100, 200, doc.GetItemsCount() + 1);
            REQUIRE(doc.GetItemsCount() == 1);
            
            auto item = doc.GetItem(0);
            REQUIRE(item.GetImage() != nullptr);
            REQUIRE(item.GetImage()->GetWidth() == 100);
            REQUIRE(item.GetImage()->GetHeight() == 200);
        }
        
        SECTION("Invalid image dimensions throw")
        {
            REQUIRE_THROWS_AS(doc.InsertImage(testImagePath, 0, 100, doc.GetItemsCount() + 1), std::invalid_argument);
            REQUIRE_THROWS_AS(doc.InsertImage(testImagePath, 100, 0, doc.GetItemsCount() + 1), std::invalid_argument);
            REQUIRE_THROWS_AS(doc.InsertImage(testImagePath, 10001, 100, doc.GetItemsCount() + 1), std::invalid_argument);
        }
        
        SECTION("Non-existent image file throws")
        {
            REQUIRE_THROWS_AS(doc.InsertImage("non_existent_file.jpg", 100, 100, doc.GetItemsCount() + 1), std::runtime_error);
        }
    }
}