//
//  MoveShapeCommand.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class MoveShapeCommand: Command {
    let prevPoint: Point
    let newPoint: Point
    let moveShape: (Point) -> Void
    
    init(prevPoint: Point, newPoint: Point, moveShape: @escaping (Point) -> Void) {
        self.prevPoint = prevPoint
        self.newPoint = newPoint
        self.moveShape = moveShape
    }
    
    func execute() {
        moveShape(newPoint)
    }
    
    func unexecute() {
        moveShape(prevPoint)
    }
}
