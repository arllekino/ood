//
//  Point.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import Foundation

struct Point: Equatable {
    let x: CGFloat
    let y: CGFloat
    
    var asCGPoint: CGPoint {
        CGPoint(x: x, y: y)
    }
    
    static func +(lhs: Point, rhs: Point) -> Point {
        Point(x: lhs.x + rhs.x, y: lhs.y + rhs.y)
    }
}
