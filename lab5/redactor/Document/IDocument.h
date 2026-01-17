#pragma once
#include <optional>

#include "../CommandLineParameters/SetTitleParameters.h"
#include "../DocumentItem/CDocumentItem.h"
#include "../Path/Path.h"

class IDocument
{
public:
    virtual void InsertParagraph(
        const std::string& text,
        std::optional<size_t> position) = 0;

    virtual void InsertImage(
        const Path& path,
        int width,
        int height,
        std::optional<size_t> position) = 0;

    [[nodiscard]] virtual size_t GetItemsCount() const = 0;
    virtual CDocumentItem GetItem(size_t index) = 0;
    virtual void DeleteItem(size_t index) = 0;
    [[nodiscard]] virtual DocumentTitle GetTitle() const = 0;
    virtual void SetTitle(const DocumentTitle& title) = 0;
    virtual void Save(const Path& path) = 0;
    virtual ~IDocument() = default;
};

using IDocumentPtr = std::shared_ptr<IDocument>;