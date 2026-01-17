//
//  CGSize+Extension.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 19.12.2025.
//

import Foundation

extension CGPoint {
    func add(_ point: Self) -> Self {
        .init(x: x + point.x, y: y + point.y)
    }
}

extension CGSize {
    func add(_ point: Self) -> Self {
        .init(width: width + point.width, height: height + point.height)
    }
}
