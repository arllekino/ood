//
//  Size.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

struct Size: Equatable {
    let width: CGFloat
    let height: CGFloat
    
    var asCGSize: CGSize {
        CGSize(width: width, height: height)
    }
    
    static func +(lhs: Size, rhs: Size) -> Size {
        Size(width: lhs.width + rhs.width, height: lhs.height + rhs.height)
    }
}
