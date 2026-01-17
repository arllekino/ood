//
//  ContentView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import AVKit
import AVFoundation
import SwiftUI

struct ContentView: View {
    private enum FileImpoting {
        case editor
        case media
    }
    
    private let defaultFileName: String = "Untitled.json"
    
    @ObservedObject var viewModel: EditorViewModel
    @State private var onCreatePopOverIsPresent: Bool = false
    
    @Environment(\.openWindow) var openWindow
    @Environment(\.appearsActive) var appearsActive
    
    @State private var isFileSaving: Bool = false
    @State private var importFileType: FileImpoting?
    
    private var allowedContentTypes: [UTType] {
        switch importFileType {
        case .editor:
            [.json]
        case .media:
            [.mpeg4Movie, .quickTimeMovie, .jpeg, .png]
        case nil:
            []
        }
    }
    
    var body: some View {
        VStack {
            HStack {
                Button(action: {
                    onCreatePopOverIsPresent.toggle()
                }) {
                    Text("Создать")
                }
                .buttonStyle(.glass)
                .popover(isPresented: $onCreatePopOverIsPresent, arrowEdge: .bottom) {
                    VStack(spacing: 12) {
                        Button(action: {
                            viewModel.createShape(type: .rectangle, at: .init(x: 100, y: 100))
                            onCreatePopOverIsPresent = false
                        }) {
                            Text("Прямоугольник")
                                .frame(maxWidth: .infinity)
                        }
                        .padding(.horizontal)
                        
                        Button(action: {
                            viewModel.createShape(type: .ellipse, at: .init(x: 200, y: 200))
                            onCreatePopOverIsPresent = false
                        }) {
                            Text("Эллипс")
                                .frame(maxWidth: .infinity)
                        }
                        .padding(.horizontal)
                        
                        Button(action: {
                            viewModel.createShape(type: .triangle, at: .init(x: 300, y: 300))
                            onCreatePopOverIsPresent = false
                        }) {
                            Text("Треугольник")
                                .frame(maxWidth: .infinity)
                        }
                        .padding(.horizontal)
                        
                        Button(action: {
                            importFileType = .media
                            onCreatePopOverIsPresent = false
                        }) {
                            Text("Видео/картинка")
                                .frame(maxWidth: .infinity)
                        }
                        .padding(.horizontal)
                    }
                    .padding(.vertical)
                }
                
                Button(action: viewModel.deleteSelectedShape) {
                    Text("Удалить")
                }
                .disabled(viewModel.viewState.selectedShapeId == nil)
                .buttonStyle(.glass)
                .keyboardShortcut(.delete, modifiers: [])
                
                Button(action: viewModel.undo) {
                    Text("Undo")
                }
                .buttonStyle(.glass)
                .keyboardShortcut("z", modifiers: .command)
                
                Button(action: viewModel.redo) {
                    Text("Redo")
                }
                .buttonStyle(.glass)
                .keyboardShortcut("z", modifiers: [.command, .shift])
                
                Button(action: {
                    openWindow(id: "detail")
                }) {
                    Text("Создать новое окно")
                }
                .buttonStyle(.glass)
                .keyboardShortcut("t", modifiers: .command)
                
                Button(action: { isFileSaving = true } ) {
                    Text("Сохранить")
                }
                .keyboardShortcut("s", modifiers: .command)
                
                Button(action: { importFileType = .editor }) {
                    Text("Загрузить документ...")
                }
                
                Spacer()
                
                Text("Фигур: \(viewModel.viewState.shapes.count)")
                    .padding(.horizontal)
            }
            .padding()
            
            CanvasView(
                shapes: viewModel.viewState.shapes,
                selectedShapeId: viewModel.viewState.selectedShapeId,
                onSelectShape: viewModel.selectShape,
                onShapeDragUpdate: viewModel.updateDragPosition,
                onShapeDragEnd: viewModel.stopDragging,
                onResizeEnd: viewModel.resizeShape
            )
        }
        .onChange(of: appearsActive) { _, newValue in
            //            viewModel.setWindowIsCurrent()
        }
        .fileExporter(
            isPresented: $isFileSaving,
            document: viewModel.documentToSave,
            contentType: .json,
            defaultFilename: defaultFileName
        ) { result in
            switch result {
            case .success(let success):
                print("saved to \(success.path)")
            case .failure(let failure):
                print(failure)
            }
        }
        .fileImporter(
            isPresented: .init(
                get: { importFileType != nil },
                set: {
                    if !$0 {
                        Task { @MainActor in
                            try? await Task.sleep(nanoseconds: 1_000)
                            importFileType = nil
                        }
                    }
                }
            ),
            allowedContentTypes: allowedContentTypes
        ) { result in
            handleImport(result)
            importFileType = nil
        }
    }
    
    private func handleImport(_ result: Result<URL, Error>) {
        switch result {
        case .success(let url):
            switch importFileType {
            case .editor:
                viewModel.loadDocument(from: url)
            case .media:
                viewModel.createShape(type: .media, at: .init(x: 100, y: 100), url: url)
            case nil:
                break
            }
        case .failure(let failure):
            print("Import error:", failure)
        }
    }
}
