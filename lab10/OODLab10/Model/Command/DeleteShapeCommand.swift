//
//  DeleteShapeCommand.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class DeleteShapeCommand: Command {
    let shape: MyAnyShape
    let createShape: (MyAnyShape) -> Void
    let deleteShape: (UUID) -> Void
    let onCommandDelete: (URL) -> Void
    
    private var isExecuted: Bool = false
    
    init(
        shape: MyAnyShape,
        createShape: @escaping (MyAnyShape) -> Void,
        deleteShape: @escaping (UUID) -> Void,
        onCommandDelete: @escaping (URL) -> Void
    ) {
        self.shape = shape
        self.createShape = createShape
        self.deleteShape = deleteShape
        self.onCommandDelete = onCommandDelete
    }
    
    deinit {
        if isExecuted {
            switch shape {
            case .media(let myMedia):
                onCommandDelete(myMedia.url)
            default:
                break
            }
        }
    }
    
    func execute() {
        deleteShape(shape.id)
        isExecuted = true
    }
    
    func unexecute() {
        createShape(shape)
        isExecuted = false
    }
}
