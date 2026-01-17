//
//  SelectionControlsView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 16.01.2026.
//

import SwiftUI

struct SelectionControlsView: View {
    let shape: MyAnyShape
    let canvasSize: CGSize
    let dragOffset: CGSize
    let onResizeEnd: (Point, Size) -> Void
    
    @State private var resizeOffset: CGPoint = .zero
    @State private var resizeOffsetSize: CGSize = .zero
    
    private var currentOverlayPosition: CGPoint {
        let baseCenter = shape.shape.boundRectCenter.asCGPoint
        return baseCenter
            .add(CGPoint(x: dragOffset.width, y: dragOffset.height))
            .add(resizeOffset)
    }
    
    private func clampPosition(_ position: CGPoint, width: CGFloat, height: CGFloat) -> CGPoint {
        let halfWidth = width / 2
        let halfHeight = height / 2
        let minX = halfWidth
        let maxX = canvasSize.width - halfWidth
        let minY = halfHeight
        let maxY = canvasSize.height - halfHeight
        let safeMaxX = max(maxX, minX)
        let safeMaxY = max(maxY, minY)
        return CGPoint(
            x: min(max(position.x, minX), safeMaxX),
            y: min(max(position.y, minY), safeMaxY)
        )
    }
    
    var body: some View {
        ShapeOverlayView(
            overlaySize: CGSize(
                width: max(shape.shape.width + resizeOffsetSize.width, 10),
                height: max(shape.shape.height + resizeOffsetSize.height, 10)
            ),
            currentOverlayPosition: currentOverlayPosition,
            onResize: { deltaPoint, deltaSize in
                if shape.shape.width + resizeOffsetSize.width > 10
                    && shape.shape.height + resizeOffsetSize.height > 10 {
                    resizeOffset = deltaPoint
                    resizeOffsetSize = deltaSize
                }
            },
            onResizeEnd: {
                var finalCenter = Point(
                    x: shape.shape.boundRectCenter.x + resizeOffset.x,
                    y: shape.shape.boundRectCenter.y + resizeOffset.y
                )
                
                let finalSize = Size(
                    width: max(shape.shape.width + resizeOffsetSize.width, 10),
                    height: max(shape.shape.height + resizeOffsetSize.height, 10)
                )
                
                let clampedCenter = clampPosition(
                    finalCenter.asCGPoint,
                    width: finalSize.width,
                    height: finalSize.height
                )
                finalCenter = Point(x: clampedCenter.x, y: clampedCenter.y)
                
                onResizeEnd(finalCenter, finalSize)
                
                resizeOffset = .zero
                resizeOffsetSize = .zero
            }
        )
    }
}
