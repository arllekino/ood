//
//  ResizeShapeCommand.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class ResizeShapeCommand: Command {
    let id: UUID
    let oldState: ShapeState
    let newState: ShapeState
    private let resizeShape: (UUID, ShapeState) -> Void
    
    init(id: UUID, oldState: ShapeState, newState: ShapeState, resizeShape: @escaping (UUID, ShapeState) -> Void) {
        self.id = id
        self.oldState = oldState
        self.newState = newState
        self.resizeShape = resizeShape
    }
    
    func execute() {
        resizeShape(id, newState)
    }
    
    func unexecute() {
        resizeShape(id, oldState)
    }
}
