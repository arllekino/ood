//
//  MyRectangle.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 13.12.2025.
//

import Foundation

class MyRectangle: Shape {
    let id: UUID
    
    private(set) var topleft: Point
    private(set) var width: CGFloat
    private(set) var height: CGFloat
    private(set) var fillColor: MyColor?
    private(set) var borderColor: MyColor?
    private(set) var borderWidth: CGFloat
    
    var type: ShapeType { .rectangle }
    var center: Point {
        Point(
            x: topleft.x + width / 2,
            y: topleft.y + height / 2
        )
    }
    
    var boundRectCenter: Point { center }
    
    init(
        id: UUID,
        topleft: Point,
        width: CGFloat,
        height: CGFloat,
        fillColor: MyColor?,
        borderColor: MyColor?,
        borderWidth: CGFloat
    ) {
        self.id = id
        self.topleft = topleft
        self.width = width
        self.height = height
        self.fillColor = fillColor
        self.borderColor = borderColor
        self.borderWidth = borderWidth
    }
    
    func move(to point: Point) {
        topleft = point
    }
    
    func setSize(width: CGFloat, height: CGFloat) {
        self.width = width
        self.height = height
    }
    
    func setFillColor(_ color: MyColor?) {
        self.fillColor = color
    }
    
    func setBorderColor(_ color: MyColor?) {
        self.borderColor = color
    }
    
    func setBorderWidth(_ width: CGFloat) {
        self.borderWidth = max(0, width)
    }
}
