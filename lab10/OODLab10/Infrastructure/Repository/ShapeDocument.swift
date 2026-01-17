//
//  ShapeDocument.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import SwiftUI
import UniformTypeIdentifiers
import Foundation

struct ColorData: Codable {
    let r, g, b, a: UInt8
}

struct PointData: Codable {
    let x, y: Double
}

struct SizeData: Codable {
    let width, height: Double
}

enum MediaExtension: String, Codable {
    case mp4 = ".mp4"
    case mov = ".mov"
    case jpg = ".jpg"
    case jpeg = ".jpeg"
    case png = ".png"
}

struct ShapeData: Codable {
    let id: UUID
    let type: String // "rectangle", "ellipse", "triangle", "media"
    let mediaIndex: Int? // only for media
    let position: PointData
    let size: SizeData
    let fillColor: ColorData?
    let borderColor: ColorData?
    let borderWidth: Double
    let vertices: [PointData]?
}

struct MediaData: Codable {
    let data: Data
    let type: MediaExtension
}

struct DocumentData: Codable {
    let version: Int
    let shapes: [ShapeData]
    let media: [MediaData]
}

struct ShapeDocument: FileDocument {
    static var readableContentTypes: [UTType] { [.json] }
    
    var shapes: [MyAnyShape]
    
    init(shapes: [MyAnyShape] = []) {
        self.shapes = shapes
    }

    init(configuration: ReadConfiguration) throws {
        guard let data = configuration.file.regularFileContents else {
            throw CocoaError(.fileReadCorruptFile)
        }
        
        self.shapes = try DocumentManager.shared.loadDocumentFromData(data)
    }

    func fileWrapper(configuration: WriteConfiguration) throws -> FileWrapper {
        let data = try DocumentManager.shared.prepareData(shapes: shapes)
        return .init(regularFileWithContents: data)
    }
}
