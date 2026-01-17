//
//  CreateShapeParameters.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

enum CreateShapeParameters {
    case rectangle(CreateRectangleParameters)
    case ellipse(CreateEllipseParameters)
    case triangle(CreateTriangleParameters)
    case media(CreateMediaParameters)
}

struct CreateRectangleParameters {
    let topLeft: Point
    let size: Size
    let fillColor: MyColor?
    let borderColor: MyColor?
    let borderWidth: CGFloat
}

struct CreateEllipseParameters {
    let center: Point
    let size: Size
    let fillColor: MyColor?
    let borderColor: MyColor?
    let borderWidth: CGFloat
}

struct CreateTriangleParameters {
    let vertices: [Point]
    let fillColor: MyColor?
    let borderColor: MyColor?
    let borderWidth: CGFloat
}

struct CreateMediaParameters {
    let url: URL
    let topLeft: Point
    let size: Size
    let borderColor: MyColor?
    let borderWidth: CGFloat
}
