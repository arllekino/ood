//
//  EditorModelTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("EditorModel basic operations")
func testEditorModel() {
    let model = EditorModel()
    
    #expect(model.documentToSave.shapes.isEmpty)
    
    let rectParams = CreateShapeParameters.rectangle(
        .init(
            topLeft: Point(x: 0, y: 0),
            size: Size(width: 100, height: 50),
            fillColor: .red,
            borderColor: .blue,
            borderWidth: 2
        )
    )
    
    model.createShape(params: rectParams)
    #expect(!model.documentToSave.shapes.isEmpty)
    
    guard let shapeId = model.documentToSave.shapes.first?.id else {
        Issue.record("No shape created")
        return
    }
    
    model.moveShape(id: shapeId, position: Point(x: 50, y: 50))
    
    model.resizeShape(id: shapeId, position: Point(x: 100, y: 100), size: Size(width: 150, height: 75))
    
    model.setBorderColor(id: shapeId, color: .green)
    model.setFillColor(id: shapeId, color: .yellow)
    model.setBorderWidth(id: shapeId, width: 5)
    
    model.deleteShape(id: shapeId)
    
    model.undo()
    #expect(model.documentToSave.shapes.count == 1)
    
    model.redo()
    #expect(model.documentToSave.shapes.isEmpty)
}

@Test("Create, modify, and delete shape")
func testShapeLifecycle() {
    let model = EditorModel()
    
    let ellipseParams = CreateShapeParameters.ellipse(
        .init(
            center: Point(x: 100, y: 100),
            size: Size(width: 200, height: 150),
            fillColor: .blue,
            borderColor: .black,
            borderWidth: 3
        )
    )
    
    model.createShape(params: ellipseParams)
    let initialCount = model.documentToSave.shapes.count
    
    if let shapeId = model.documentToSave.shapes.first?.id {
        model.moveShape(id: shapeId, position: Point(x: 150, y: 150))
        model.setBorderWidth(id: shapeId, width: 5)
        
        model.deleteShape(id: shapeId)
        #expect(model.documentToSave.shapes.count == initialCount - 1)
        
        model.undo()
        #expect(model.documentToSave.shapes.count == initialCount)
    }
}
