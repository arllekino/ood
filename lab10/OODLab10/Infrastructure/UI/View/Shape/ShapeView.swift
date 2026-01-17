//
//  ShapeView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 19.12.2025.
//

import SwiftUI

struct ShapeView: View {
    let shape: MyAnyShape
    let selectedShapeId: UUID?
    let canvasSize: CGSize
    
    @Binding var dragOffset: CGSize
    
    let onSelectShape: (UUID?) -> Void
    let onShapeDragUpdate: (UUID, Point) -> Void
    let onShapeDragEnd: () -> Void
    
    @State private var isDragging = false
    @State private var dragStartPosition: CGPoint = .zero
    
    @State private var currentDragTranslation: CGSize = .zero
    
    private var currentPosition: CGPoint {
        shape.shape.center.asCGPoint
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
        Group {
            switch shape {
            case .rectangle(let rectangle):
                rectangleView(rectangle)
            case .ellipse(let ellipse):
                ellipseView(ellipse)
            case .triangle(let triangle):
                triangleView(triangle)
            case .media(let media):
                mediaView(media)
            }
        }
        .id(shape.id)
        .gesture(
            DragGesture(minimumDistance: 0)
                .onChanged { value in
                    if !isDragging {
                        isDragging = true
                        dragStartPosition = currentPosition
                        if shape.id != selectedShapeId {
                            onSelectShape(shape.id)
                        }
                    }
                    
                    let proposedX = dragStartPosition.x + value.translation.width
                    let proposedY = dragStartPosition.y + value.translation.height
                    
                    let clamped = clampPosition(
                        CGPoint(x: proposedX, y: proposedY),
                        width: shape.shape.width,
                        height: shape.shape.height
                    )
                    
                    let newTranslation = CGSize(
                        width: clamped.x - dragStartPosition.x,
                        height: clamped.y - dragStartPosition.y
                    )
                    
                    currentDragTranslation = newTranslation
                    
                    if shape.id == selectedShapeId {
                        dragOffset = newTranslation
                    }
                }
                .onEnded { value in
                    isDragging = false
                    
                    let finalProposed = CGPoint(
                        x: dragStartPosition.x + currentDragTranslation.width,
                        y: dragStartPosition.y + currentDragTranslation.height
                    )
                    
                    let clampedFinal = clampPosition(
                        finalProposed,
                        width: shape.shape.width,
                        height: shape.shape.height
                    )
                    
                    onShapeDragUpdate(shape.id, Point(x: clampedFinal.x, y: clampedFinal.y))
                    onShapeDragEnd()
                    
                    currentDragTranslation = .zero
                    dragStartPosition = .zero
                }
        )
        .highPriorityGesture(
            TapGesture()
                .onEnded {
                    onSelectShape(shape.id)
                }
        )
    }
    
    @ViewBuilder private func rectangleView(_ rectangle: MyRectangle) -> some View {
        Rectangle()
            .if(rectangle.fillColor != nil) { view in
                view.fill(rectangle.fillColor!.asSwiftUI)
            }
            .if(rectangle.borderColor != nil && rectangle.borderWidth > 0) { view in
                view.overlay(
                    Rectangle()
                        .stroke(
                            rectangle.borderColor!.asSwiftUI,
                            lineWidth: rectangle.borderWidth
                        )
                )
            }
            .frame(width: rectangle.width, height: rectangle.height)
            .position(
                x: currentPosition.x + currentDragTranslation.width,
                y: currentPosition.y + currentDragTranslation.height
            )
    }
    
    @ViewBuilder private func ellipseView(_ ellipse: MyEllipse) -> some View {
        Ellipse()
            .if(ellipse.fillColor != nil) { view in
                view.fill(ellipse.fillColor!.asSwiftUI)
            }
            .if(ellipse.borderColor != nil && ellipse.borderWidth > 0) { view in
                view.overlay(
                    Ellipse()
                        .stroke(
                            ellipse.borderColor!.asSwiftUI,
                            lineWidth: ellipse.borderWidth
                        )
                )
            }
            .frame(width: ellipse.width, height: ellipse.height)
            .position(
                x: currentPosition.x + currentDragTranslation.width,
                y: currentPosition.y + currentDragTranslation.height
            )
    }
    
    @ViewBuilder private func triangleView(_ triangle: MyTriangle) -> some View {
        let vertices = triangle.vertices.map { vertex -> CGPoint in
            let v = vertex.asCGPoint
            return CGPoint(
                x: v.x + currentDragTranslation.width,
                y: v.y + currentDragTranslation.height
            )
        }
        
        let path = Path { path in
            guard !vertices.isEmpty else { return }
            path.move(to: vertices[0])
            for i in 1..<vertices.count {
                path.addLine(to: vertices[i])
            }
            path.closeSubpath()
        }
        
        path
            .if(triangle.fillColor != nil) { $0.fill(triangle.fillColor!.asSwiftUI) }
            .if(triangle.borderColor != nil && triangle.borderWidth > 0) {
                $0.overlay(path.stroke(triangle.borderColor!.asSwiftUI, lineWidth: triangle.borderWidth))
            }
            .contentShape(path)
    }
    
    @ViewBuilder private func mediaView(_ media: MyMedia) -> some View {
        Group {
            switch media.mediaType {
            case .video:
                MediaPlayerView(url: media.url)
            case .image:
                StableImageView(url: media.url)
            }
        }
        .clipped()
        .if(media.borderColor != nil && media.borderWidth > 0) { view in
            view.overlay(
                Rectangle()
                    .stroke(
                        media.borderColor!.asSwiftUI,
                        lineWidth: media.borderWidth
                    )
            )
        }
        .frame(width: media.width, height: media.height)
        .position(
            x: currentPosition.x + currentDragTranslation.width,
            y: currentPosition.y + currentDragTranslation.height
        )
    }
}
