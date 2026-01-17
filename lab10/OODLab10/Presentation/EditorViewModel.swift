//
//  EditorViewModel.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import Foundation
import Combine
import AppKit
import UniformTypeIdentifiers

class EditorViewModel: ObservableObject, ShapeNotifiable {
    let id: UUID = .init()
    private let editorModel: EditorModel

    @Published private(set) var viewState: EditorViewState = .defaultState
    
    var documentToSave: ShapeDocument {
        editorModel.documentToSave
    }
    
    init(redactorModel: EditorModel) {
        self.editorModel = redactorModel
        self.viewState = .defaultState
    
        self.editorModel.addReciever(self)
    }
    
    deinit {
        editorModel.removeReciever(self)
    }
    
    func createShape(type: ShapeType, at position: Point, url: URL? = nil) {
        let createShapeParams: CreateShapeParameters
        switch type {
        case .rectangle:
            createShapeParams = .rectangle(
                .init(
                    topLeft: position,
                    size: .init(width: 100, height: 50),
                    fillColor: .cyan,
                    borderColor: nil,
                    borderWidth: 0
                )
            )
        case .ellipse:
            createShapeParams = .ellipse(
                .init(
                    center: position,
                    size: .init(width: 200, height: 200),
                    fillColor: .black,
                    borderColor: nil,
                    borderWidth: 0
                )
            )
        case .triangle:
            createShapeParams = .triangle(
                .init(
                    vertices: [
                        .init(x: 100, y: 100),
                        .init(x: 200, y: 100),
                        .init(x: 150, y: 150)
                    ],
                    fillColor: .green,
                    borderColor: nil,
                    borderWidth: 0
                )
            )
        case .media:
            guard let url,
                  let onCopyUrl = loadMedia(from: url)
            else {
                return
            }
            createShapeParams = .media(
                .init(
                    url: onCopyUrl,
                    topLeft: position,
                    size: .init(width: 1080, height: 720),
                    borderColor: nil,
                    borderWidth: 0
                )
            )
        }
        
        editorModel.createShape(params: createShapeParams)
    }
    
    func selectShape(id: UUID?) {
        viewState = viewState.changing {
            $0.selectedShapeId = id
        }
    }
    
    func deleteSelectedShape() {
        guard let selectedShapeId = viewState.selectedShapeId else { return }
        
        editorModel.deleteShape(id: selectedShapeId)
    }
        
    func updateDragPosition(id: UUID, position: Point) {
        editorModel.moveShape(id: id, position: position)
        
        viewState = viewState.changing {
            $0.selectedShapeId = id
        }
    }

    func stopDragging() {
        callRender()
    }
    
    func resizeShape(newPosition: Point, newSize: Size) {
        guard let selectedId = viewState.selectedShapeId else { return }
        
        editorModel.resizeShape(
            id: selectedId,
            position: newPosition,
            size: newSize
        )
    }
    
    func undo() {
        editorModel.undo()
    }
    
    func redo() {
        editorModel.redo()
    }
    
    func notify(_ shapes: [MyAnyShape]) {
        viewState = viewState.changing {
            $0.shapes = shapes
        }
        
        callRender()
    }
    
    func loadDocument(from url: URL) {
        do {
            try editorModel.loadDocument(from: url)
            selectShape(id: nil)
        } catch {
            print("Failed to load document: \(error)")
        }
    }
    
    private func loadMedia(from url: URL) -> URL? {
        do {
            return try editorModel.storeMedia(from: url)
        } catch {
            print("Failed to load media: \(error)")
            return nil
        }
    }
}

fileprivate extension EditorViewModel {
    
    // TODO: remove
    func callRender() {
        let selectedShapeId = viewState.selectedShapeId
        viewState = viewState.changing {
            $0.selectedShapeId = UUID()
        }
        Task { @MainActor in
            try? await Task.sleep(nanoseconds: 1_000)
            viewState = viewState.changing {
                $0.selectedShapeId = selectedShapeId
            }
        }
    }
}
