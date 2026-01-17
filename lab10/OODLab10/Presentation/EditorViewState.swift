//
//  EditorViewState.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import Foundation

struct EditorViewState: Equatable {
    let selectedShapeId: UUID?
    let shapes: [MyAnyShape]
    
    static var defaultState: Self {
        .init(
            selectedShapeId: nil,
            shapes: []
        )
    }
}

extension EditorViewState: Changeable {
    init(copy: ChangeableWrapper<EditorViewState>) {
        self.selectedShapeId = copy.selectedShapeId
        self.shapes = copy.shapes
    }
}
