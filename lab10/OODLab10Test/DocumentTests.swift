//
//  DocumentTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import UniformTypeIdentifiers
import Testing
@testable import OODLab10

@Test("ShapeDocument file operations")
func testShapeDocument() {
    let shapes = [
        MyAnyShape.rectangle(
            MyRectangle(
                id: UUID(),
                topleft: Point(x: 0, y: 0),
                width: 100,
                height: 50,
                fillColor: .red,
                borderColor: .blue,
                borderWidth: 2
            )
        )
    ]
    
    let document = ShapeDocument(shapes: shapes)
    
    #expect(document.shapes.count == 1)
    #expect(ShapeDocument.readableContentTypes.contains(.json))
}
