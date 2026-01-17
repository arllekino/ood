//
//  ShapeTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("MyRectangle properties and operations")
func testMyRectangle() {
    let rect = MyRectangle(
        id: UUID(),
        topleft: Point(x: 0, y: 0),
        width: 100,
        height: 50,
        fillColor: .red,
        borderColor: .blue,
        borderWidth: 2
    )
    
    #expect(rect.type == .rectangle)
    #expect(rect.center.x == 50)
    #expect(rect.center.y == 25)
    #expect(rect.boundRectCenter == rect.center)
    
    rect.move(to: Point(x: 10, y: 10))
    #expect(rect.topleft.x == 10)
    #expect(rect.topleft.y == 10)
    
    rect.setSize(width: 200, height: 100)
    #expect(rect.width == 200)
    #expect(rect.height == 100)
    
    rect.setFillColor(.green)
    #expect(rect.fillColor == .green)
    
    rect.setBorderColor(.yellow)
    #expect(rect.borderColor == .yellow)
    
    rect.setBorderWidth(5)
    #expect(rect.borderWidth == 5)
    
    rect.setBorderWidth(-1)
    #expect(rect.borderWidth == 0)
}

@Test("MyEllipse properties and operations")
func testMyEllipse() {
    let ellipse = MyEllipse(
        id: UUID(),
        center: Point(x: 50, y: 50),
        width: 100,
        height: 80,
        fillColor: .blue,
        borderColor: .red,
        borderWidth: 3
    )
    
    #expect(ellipse.type == .ellipse)
    #expect(ellipse.boundRectCenter == ellipse.center)
    
    ellipse.move(to: Point(x: 60, y: 60))
    #expect(ellipse.center.x == 60)
    #expect(ellipse.center.y == 60)
    
    ellipse.setSize(width: 120, height: 90)
    #expect(ellipse.width == 120)
    #expect(ellipse.height == 90)
}

@Test("MyTriangle properties and operations")
func testMyTriangle() {
    let vertices = [
        Point(x: 0, y: 0),
        Point(x: 100, y: 0),
        Point(x: 50, y: 100)
    ]
    
    let triangle = MyTriangle(
        id: UUID(),
        vertices: vertices,
        fillColor: .green,
        borderColor: .black,
        borderWidth: 2
    )
    
    #expect(triangle.type == .triangle)
    #expect(triangle.vertices.count == 3)
    #expect(triangle.width == 100)
    #expect(triangle.height == 100)
    #expect(triangle.center.x == 50)
    #expect(triangle.center.y == 100.0 / 3.0)
    
    let newCenter = Point(x: 100, y: 100)
    triangle.move(to: newCenter)
    #expect(triangle.center.x == 100)
    #expect(triangle.center.y == 100)
    
    
    triangle.setSize(width: 200, height: 150)
    #expect(triangle.width == 200)
    #expect(triangle.height == 150)
}

@Test("MyMedia properties and operations")
func testMyMedia() {
    let tempURL = FileManager.default.temporaryDirectory.appendingPathComponent("test.png")
    
    let media = MyMedia(
        id: UUID(),
        url: tempURL,
        topleft: Point(x: 0, y: 0),
        width: 300,
        height: 200,
        fillColor: nil,
        borderColor: .black,
        borderWidth: 1
    )
    
    #expect(media.type == .media)
    #expect(media.mediaType == .image)
    #expect(media.conreteMediaType == .png)
    #expect(media.center.x == 150)
    #expect(media.center.y == 100)
    #expect(media.fillColor == nil)
    
    media.move(to: Point(x: 50, y: 50))
    #expect(media.topleft.x == 50)
    #expect(media.topleft.y == 50)
    
    media.setSize(width: 400, height: 300)
    #expect(media.width == 400)
    #expect(media.height == 300)
    
    media.setFillColor(.red)
    #expect(media.fillColor == nil)
}
