#pragma once
#include "IDocument.h"
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_set>

#include "../DocumentItem/Image/CImage.h"
#include "../DocumentItem/Paragraph/CParagraph.h"

class CDocument : public IDocument
{
public:
    ~CDocument() override
    {
        CleanupTempFiles();
    }

    void InsertParagraph(
        const std::string& text,
        const std::optional<size_t> position) override
    {
        const auto item = CDocumentItem(std::make_shared<CParagraph>(text));
        if (position.has_value())
        {
            const auto itemPosition = position.value() - 1;
            if (itemPosition > m_items.size())
            {
                throw std::out_of_range("Position is out of range");
            }
            m_items.insert(m_items.begin() + static_cast<long>(itemPosition), item);
        }
        else
        {
            m_items.push_back(item);
        }
    }

    void InsertImage(
        const Path& path,
        int width,
        int height,
        const std::optional<size_t> position) override
    {
        if (width < 1 || width > 10000 || height < 1 || height > 10000)
        {
            throw std::invalid_argument("Image dimensions must be between 1 and 10000");
        }

        auto copiedPath = CopyImageToDocumentStorage(path);
        std::cout << copiedPath << std::endl;
        const auto item = CDocumentItem(std::make_shared<CImage>(copiedPath, width, height));
        if (position.has_value())
        {
            const auto itemPosition = position.value() - 1;
            if (itemPosition > m_items.size())
            {
                throw std::out_of_range("Position is out of range");
            }
            m_items.insert(m_items.begin() + static_cast<long>(itemPosition), item);
        }
        else
        {
            m_items.push_back(item);
        }

        m_managedImageFiles.insert(copiedPath);
    }

    [[nodiscard]] size_t GetItemsCount() const override
    {
        return m_items.size();
    }

    CDocumentItem GetItem(const size_t index) override
    {
        if (index >= m_items.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return m_items[index];
    }

    void DeleteItem(const size_t index) override
    {
        if (index >= m_items.size())
        {
            throw std::out_of_range("Index out of range");
        }

        auto item = m_items[index];
        if (auto image = item.GetImage(); image != nullptr)
        {
            m_filesToDelete.insert(image->GetPath());
        }

        m_items.erase(m_items.begin() + static_cast<long>(index));
    };

    [[nodiscard]] DocumentTitle GetTitle() const override
    {
        return m_title;
    }

    void SetTitle(const DocumentTitle& title) override
    {
        m_title = title;
    }

    void Save(const Path& path) override
    {
        std::filesystem::path savePath(path);
        create_directories(savePath);

        std::ofstream contentFile(savePath / "content.html");
        contentFile << "<!DOCTYPE html>\n";
        contentFile << "<html>\n";
        contentFile << "    <head><title>" << EscapeHtml(m_title.title) << "</title></head>\n";
        contentFile << "    <body>\n";
        contentFile << "        <h1>" << EscapeHtml(m_title.title) << "</h1>\n";

        for (auto& item : m_items)
        {
            if (auto image = item.GetImage())
            {
                auto imagePath = std::filesystem::path(image->GetPath());
                auto imageName = imagePath.filename();
                auto destPath = savePath / "images" / imageName;

                create_directories(savePath / "images");

                if (exists(imagePath))
                {
                    copy_file(
                        imagePath,
                        destPath,
                        std::filesystem::copy_options::overwrite_existing);
                }

                contentFile << "        <img src=\"images/" << EscapeHtml(imageName.string())
                    << "\" width=\"" << image->GetWidth()
                    << "\" height=\"" << image->GetHeight() << "\" />\n";
            }
            else if (auto paragraph = item.GetParagraph())
            {
                contentFile << "        <p>" << EscapeHtml(paragraph->GetText()) << "</p>\n";
            }
        }

        contentFile << "    </body>\n";
        contentFile << "</html>\n";
        contentFile.close();

        CleanupMarkedFiles();
    }

private:
    DocumentTitle m_title;
    std::vector<CDocumentItem> m_items;
    std::unordered_set<Path> m_managedImageFiles;
    std::unordered_set<Path> m_filesToDelete;

    static Path CopyImageToDocumentStorage(const Path& originalPath)
    {
        try
        {
            if (!std::filesystem::exists(originalPath))
            {
                throw std::runtime_error("Image file not found: " + originalPath);
            }

            auto docStorageDir = std::filesystem::temp_directory_path() / "document_editor_storage";
            if (!exists(docStorageDir))
            {
                create_directories(docStorageDir);
            }

            auto originalFile = std::filesystem::path(originalPath);
            auto storageFile = docStorageDir / originalFile.filename();

            int counter = 1;
            while (exists(storageFile))
            {
                auto stem = originalFile.stem().string();
                auto extension = originalFile.extension().string();
                storageFile = docStorageDir / (stem + "_" + std::to_string(counter) + extension);
                counter++;
            }

            copy_file(originalPath, storageFile);

            return storageFile.string();
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            throw std::runtime_error("Failed to copy image file to document storage: " + std::string(e.what()));
        }
    }

    void CleanupMarkedFiles()
    {
        for (const auto& filePath : m_filesToDelete)
        {
            try
            {
                if (std::filesystem::exists(filePath))
                {
                    std::filesystem::remove(filePath);
                    m_managedImageFiles.erase(filePath);
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Warning: Failed to delete file " << filePath << ": " << e.what() << std::endl;
            }
        }
        m_filesToDelete.clear();
    }

    void CleanupTempFiles()
    {
        for (const auto& filePath : m_managedImageFiles)
        {
            try
            {
                if (std::filesystem::exists(filePath))
                {
                    std::filesystem::remove(filePath);
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Warning: Failed to cleanup temp file " << filePath << ": " << e.what() << std::endl;
            }
        }
        m_managedImageFiles.clear();

        CleanupMarkedFiles();
    }

    static std::string EscapeHtml(const std::string& text) {
        std::string result;
        for (const char ch : text)
        {
            switch (ch)
            {
                case '&':
                    result += "&amp;";
                    break;
                case '\"':
                    result += "&quot;";
                    break;
                case '\'':
                    result += "&#39;";
                    break;
                case '<':
                    result += "&lt;";
                    break;
                case '>':
                    result += "&gt;";
                    break;
                default:
                    result += ch;
                break;
            }
        }
        return result;
    }
};