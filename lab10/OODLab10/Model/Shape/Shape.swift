//
//  Shape.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import Foundation

protocol Shape: Identifiable, Equatable {
    var id: UUID { get }
    var fillColor: MyColor? { get }
    var borderColor: MyColor? { get }
    var borderWidth: CGFloat { get }
    
    var type: ShapeType { get }
    var center: Point { get }
    var width: CGFloat { get }
    var height: CGFloat { get }
    var boundRectCenter: Point { get }
    
    func move(to point: Point)
    func setSize(width: CGFloat, height: CGFloat)
    func setFillColor(_ color: MyColor?)
    func setBorderColor(_ color: MyColor?)
    func setBorderWidth(_ width: CGFloat)
}

enum ShapeType {
    case rectangle
    case ellipse
    case triangle
    case media
    
    var description: String {
        switch self {
        case .rectangle:
            return "Rectangle"
        case .ellipse:
            return "Ellipse"
        case .triangle:
            return "Triangle"
        case .media:
            return "Media"
        }
    }
}

extension Shape {
    static func == (lhs: Self, rhs: Self) -> Bool {
        lhs.id == rhs.id
    }
}

enum MyAnyShape: Identifiable, Equatable {
    case rectangle(MyRectangle)
    case ellipse(MyEllipse)
    case triangle(MyTriangle)
    case media(MyMedia)
    
    var shape: any Shape {
        switch self {
        case .rectangle(let rectangle):
            return rectangle
        case .ellipse(let ellipse):
            return ellipse
        case .triangle(let triangle):
            return triangle
        case .media(let media):
            return media
        }
    }
    
    var id: UUID {
        shape.id
    }
    
    var type: ShapeType {
        shape.type
    }
    
    static func == (lhs: MyAnyShape, rhs: MyAnyShape) -> Bool {
        lhs.id == rhs.id
    }
}
