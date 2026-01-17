//
//  CreateShapeCommand.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class CreateShapeCommand: Command {
    let shape: MyAnyShape
    let createShape: (MyAnyShape) -> Void
    let deleteShape: (UUID) -> Void
    let onCommandDispose: (URL) -> Void
    
    private var isExecuted: Bool = false
    
    init(
        shape: MyAnyShape,
        createShape: @escaping (MyAnyShape) -> Void,
        deleteShape: @escaping (UUID) -> Void,
        onCommandDispose: @escaping (URL) -> Void
    ) {
        self.shape = shape
        self.createShape = createShape
        self.deleteShape = deleteShape
        self.onCommandDispose = onCommandDispose
    }
    
    deinit {
        if !isExecuted {
            if case .media(let myMedia) = shape {
                onCommandDispose(myMedia.url)
            }
        }
    }
    
    func execute() {
        createShape(shape)
        isExecuted = true
    }
    
    func unexecute() {
        deleteShape(shape.id)
        isExecuted = false
    }
}
