//
//  CanvasView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import SwiftUI

struct CanvasView: View {
    let shapes: [MyAnyShape]
    let selectedShapeId: UUID?
    let onSelectShape: (UUID?) -> Void
    let onShapeDragUpdate: (UUID, Point) -> Void
    let onShapeDragEnd: () -> Void
    let onResizeEnd: (Point, Size) -> Void
    
    @State private var globalDragOffset: CGSize = .zero
    
    var body: some View {
        GeometryReader { geometry in
            ZStack(alignment: .topLeading) {
                ForEach(shapes) { anyShape in
                    ShapeView(
                        shape: anyShape,
                        selectedShapeId: selectedShapeId,
                        canvasSize: geometry.size,
                        dragOffset: $globalDragOffset,
                        onSelectShape: onSelectShape,
                        onShapeDragUpdate: { id, point in
                            onShapeDragUpdate(id, point)
                            globalDragOffset = .zero
                        },
                        onShapeDragEnd: onShapeDragEnd
                    )
                }
                
                if let selectedId = selectedShapeId,
                   let selectedShape = shapes.first(where: { $0.id == selectedId }) {
                    
                    SelectionControlsView(
                        shape: selectedShape,
                        canvasSize: geometry.size,
                        dragOffset: globalDragOffset,
                        onResizeEnd: onResizeEnd
                    )
                }
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .background(Color.gray.opacity(0.1))
            .contentShape(Rectangle())
            .onTapGesture {
                onSelectShape(nil)
            }
        }
    }
}
