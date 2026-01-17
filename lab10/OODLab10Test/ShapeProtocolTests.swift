//
//  ShapeProtocolTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("Shape protocol conformance")
func testShapeProtocol() {
    let rect = MyRectangle(
        id: UUID(),
        topleft: Point(x: 0, y: 0),
        width: 100,
        height: 50,
        fillColor: .red,
        borderColor: .blue,
        borderWidth: 2
    )
    
    let ellipse = MyEllipse(
        id: UUID(),
        center: Point(x: 50, y: 50),
        width: 100,
        height: 80,
        fillColor: .green,
        borderColor: .black,
        borderWidth: 1
    )
    
    #expect(rect.type == .rectangle)
    #expect(ellipse.type == .ellipse)
    
    #expect(rect.id != ellipse.id)
    #expect(rect.fillColor == .red)
    #expect(ellipse.fillColor == .green)
}

@Test("AnyShape wrapper")
func testAnyShape() {
    let rect = MyRectangle(
        id: UUID(),
        topleft: Point(x: 0, y: 0),
        width: 100,
        height: 50,
        fillColor: .red,
        borderColor: .blue,
        borderWidth: 2
    )
    
    let anyRect = MyAnyShape.rectangle(rect)
    
    #expect(anyRect.id == rect.id)
    #expect(anyRect.type == .rectangle)
    #expect(anyRect.shape.id == rect.id)
    
    let sameRect = MyAnyShape.rectangle(rect)
    #expect(anyRect == sameRect)
    
    let differentRect = MyAnyShape.rectangle(
        MyRectangle(
            id: UUID(),
            topleft: Point(x: 10, y: 10),
            width: 50,
            height: 25,
            fillColor: .green,
            borderColor: .yellow,
            borderWidth: 1
        )
    )
    #expect(anyRect != differentRect)
}
