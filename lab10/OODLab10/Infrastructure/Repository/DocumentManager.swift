//
//  DocumentManager.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 23.12.2025.
//

import Foundation

class DocumentManager {
    static let shared = DocumentManager()
    
    func prepareData(shapes: [MyAnyShape]) throws -> Data {
        var mediaFiles: [MediaData] = []
        var mediaIndices: [UUID: Int] = [:]
        
        for anyShape in shapes {
            if case .media(let myMedia) = anyShape {
                do {
                    let mediaData = try Data(contentsOf: myMedia.url)
                    mediaIndices[myMedia.id] = mediaFiles.count
                    mediaFiles.append(
                        .init(data: mediaData, type: myMedia.conreteMediaType.asMediaExtension)
                    )
                } catch {
                    print("Error loading media: \(error)")
                }
            }
        }
        
        let storageShapes = shapes.map { anyShape in
            let s = anyShape.shape
            
            var verticesData: [PointData]? = nil
            if case .triangle(let triangle) = anyShape {
                verticesData = triangle.vertices.map { PointData(x: $0.x, y: $0.y) }
            }
            
            let mediaIndex = mediaIndices[anyShape.id]
            
            return ShapeData(
                id: s.id,
                type: s.type.description.lowercased(),
                mediaIndex: mediaIndex,
                position: PointData(x: s.center.x, y: s.center.y),
                size: SizeData(width: s.width, height: s.height),
                fillColor: s.fillColor.map { ColorData(r: $0.red, g: $0.green, b: $0.blue, a: $0.alpha) },
                borderColor: s.borderColor.map { ColorData(r: $0.red, g: $0.green, b: $0.blue, a: $0.alpha) },
                borderWidth: Double(s.borderWidth),
                vertices: verticesData
            )
        }
        
        let document = DocumentData(version: 1, shapes: storageShapes, media: mediaFiles)
        return try JSONEncoder().encode(document)
    }
    
    func loadDocument(from url: URL) throws -> [MyAnyShape] {
        let data = try Data(contentsOf: url)
        return try loadDocumentFromData(data)
    }

    func loadDocumentFromData(_ data: Data) throws -> [MyAnyShape] {
        let decoder = JSONDecoder()
        let decoded = try decoder.decode(DocumentData.self, from: data)
        
        var restoredMediaUrls: [Int: URL] = [:]
        
        for (index, mediaData) in decoded.media.enumerated() {
            do {
                let tempFileName = UUID().uuidString + mediaData.type.rawValue
                let tempFileURL = FileManager.default.temporaryDirectory
                    .appendingPathComponent(tempFileName)
                
                try mediaData.data.write(to: tempFileURL)
                
                let permanentURL = try MediaStorage.shared.store(
                    url: tempFileURL,
                    filename: UUID().uuidString
                )
                
                restoredMediaUrls[index] = permanentURL
                
                try? FileManager.default.removeItem(at: tempFileURL)
            } catch {
                print("Error storing media: \(error)")
            }
        }
        
        return decoded.shapes.compactMap { data in
            let fillColor = data.fillColor.map { MyColor(red: $0.r, green: $0.g, blue: $0.b, alpha: $0.a) }
            let borderColor = data.borderColor.map { MyColor(red: $0.r, green: $0.g, blue: $0.b, alpha: $0.a) }
            
            switch data.type {
            case "rectangle":
                let rect = MyRectangle(
                    id: data.id,
                    topleft: Point(x: data.position.x - data.size.width/2, y: data.position.y - data.size.height/2),
                    width: data.size.width,
                    height: data.size.height,
                    fillColor: fillColor,
                    borderColor: borderColor,
                    borderWidth: data.borderWidth
                )
                return .rectangle(rect)
            case "ellipse":
                let ellipse = MyEllipse(
                    id: data.id,
                    center: Point(x: data.position.x, y: data.position.y),
                    width: data.size.width,
                    height: data.size.height,
                    fillColor: fillColor,
                    borderColor: borderColor,
                    borderWidth: data.borderWidth
                )
                return .ellipse(ellipse)
            case "triangle":
                let triangle = MyTriangle(
                    id: data.id,
                    vertices: data.vertices!.map { Point(x: $0.x, y: $0.y) },
                    fillColor: fillColor,
                    borderColor: borderColor,
                    borderWidth: data.borderWidth
                )
                return .triangle(triangle)
            case "media":
                let url = restoredMediaUrls[data.mediaIndex!]
                
                let media = MyMedia(
                    id: data.id,
                    url: url!,
                    topleft: Point(x: data.position.x - data.size.width/2, y: data.position.y - data.size.height/2),
                    width: data.size.width,
                    height: data.size.height,
                    fillColor: fillColor,
                    borderColor: borderColor,
                    borderWidth: data.borderWidth
                )
                return .media(media)
            default:
                return nil
            }
        }
    }
}

fileprivate extension MyMedia.ConcreteMediaType {
    var asMediaExtension: MediaExtension {
        switch self {
        case .mp4:
            .mp4
        case .mov:
            .mov
        case .png:
            .png
        case .jpg:
            .jpg
        case .jpeg:
            .jpg
        }
    }
}
