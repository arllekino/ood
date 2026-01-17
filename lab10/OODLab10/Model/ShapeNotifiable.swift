//
//  ShapeNotifiable.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 13.12.2025.
//

import Foundation

protocol ShapeNotifiable {
    var id: UUID { get }
    func notify(_ shapes: [MyAnyShape])
}
