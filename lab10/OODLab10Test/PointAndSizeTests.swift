//
//  PointAndSizeTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("Point operations")
func testPointOperations() {
    let point1 = Point(x: 10, y: 20)
    let point2 = Point(x: 5, y: 10)
    let result = point1 + point2
    
    #expect(result.x == 15)
    #expect(result.y == 30)
    #expect(point1.asCGPoint.x == 10)
    #expect(point1.asCGPoint.y == 20)
}

@Test("Size operations")
func testSizeOperations() {
    let size1 = Size(width: 100, height: 200)
    let size2 = Size(width: 50, height: 100)
    let result = size1 + size2
    
    #expect(result.width == 150)
    #expect(result.height == 300)
    #expect(size1.asCGSize.width == 100)
    #expect(size1.asCGSize.height == 200)
}

@Test("Array Point extensions")
func testPointArrayExtensions() {
    let points = [
        Point(x: 10, y: 20),
        Point(x: 30, y: 5),
        Point(x: 15, y: 40)
    ]
    
    #expect(points.minX == 10)
    #expect(points.maxX == 30)
    #expect(points.minY == 5)
    #expect(points.maxY == 40)
}
