//
//  ShapeFactory.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import Foundation

class ShapeFactory {
    func createShape(parameters: CreateShapeParameters) -> MyAnyShape {
        switch parameters {
        case .rectangle(let params):
            .rectangle(
                .init(
                    id: UUID(),
                    topleft: params.topLeft,
                    width: params.size.width,
                    height: params.size.height,
                    fillColor: params.fillColor,
                    borderColor: params.borderColor,
                    borderWidth: params.borderWidth
                )
            )
        case .ellipse(let params):
            .ellipse(
                .init(
                    id: UUID(),
                    center: params.center,
                    width: params.size.width,
                    height: params.size.height,
                    fillColor: params.fillColor,
                    borderColor: params.borderColor,
                    borderWidth: params.borderWidth
                )
            )
        case .triangle(let params):
            .triangle(
                .init(
                    id: UUID(),
                    vertices: params.vertices,
                    fillColor: params.fillColor,
                    borderColor: params.borderColor,
                    borderWidth: params.borderWidth
                )
            )
        case .media(let params):
            .media(
                .init(
                    id: UUID(),
                    url: params.url,
                    topleft: params.topLeft,
                    width: params.size.width,
                    height: params.size.height,
                    borderColor: params.borderColor,
                    borderWidth: params.borderWidth
                )
            )
        }
    }
}
