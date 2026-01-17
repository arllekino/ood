//
//  MyEllipse.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 13.12.2025.
//

import Foundation

class MyEllipse: Shape {
    let id: UUID
    
    private(set) var center: Point
    private(set) var width: CGFloat
    private(set) var height: CGFloat
    private(set) var fillColor: MyColor?
    private(set) var borderColor: MyColor?
    private(set) var borderWidth: CGFloat
    
    var type: ShapeType { .ellipse }
    
    var boundRectCenter: Point { center }
    
    init(id: UUID, center: Point, width: CGFloat, height: CGFloat, fillColor: MyColor?, borderColor: MyColor?, borderWidth: CGFloat) {
        self.id = id
        self.center = center
        self.width = width
        self.height = height
        self.fillColor = fillColor
        self.borderColor = borderColor
        self.borderWidth = borderWidth
    }
    
    func move(to point: Point) {
        center = point
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
