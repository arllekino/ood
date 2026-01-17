//
//  ShapeOverlayView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 19.12.2025.
//

import SwiftUI

fileprivate enum Direction {
    case topLeft
    case top
    case topRight
    case right
    case bottomRight
    case bottom
    case bottomLeft
    case left
}

struct ShapeOverlayView: View {
    let overlaySize: CGSize
    let currentOverlayPosition: CGPoint
    let onResize: (CGPoint, CGSize) -> Void
    let onResizeEnd: () -> Void
    
    private let directions: [Direction] = [
        .topLeft,
        .top,
        .topRight,
        .right,
        .bottomRight,
        .bottom,
        .bottomLeft,
        .left
    ]
    
    var body: some View {
        Group {
            Rectangle()
                .stroke(lineWidth: 2)
                .foregroundColor(Color.accentColor)
                .frame(width: overlaySize.width, height: overlaySize.height)
                .position(
                    x: currentOverlayPosition.x,
                    y: currentOverlayPosition.y
                )
            
            ForEach(directions, id: \.self) { direction in
                ResizePoint(
                    direction: direction,
                    position: dragPointPosition(direction),
                    onResize: { delta in
                        self.resize(for: direction, delta: delta)
                    },
                    onResizeEnd: onResizeEnd
                )
            }
        }
    }
    
    private func dragPointPosition(_ direction: Direction) -> CGPoint {
        switch direction {
        case .topLeft:
            .init(x: currentOverlayPosition.x - overlaySize.width / 2, y: currentOverlayPosition.y - overlaySize.height / 2)
        case .top:
            .init(x: currentOverlayPosition.x, y: currentOverlayPosition.y - overlaySize.height / 2)
        case .topRight:
            .init(x: currentOverlayPosition.x + overlaySize.width / 2, y: currentOverlayPosition.y - overlaySize.height / 2)
        case .right:
            .init(x: currentOverlayPosition.x + overlaySize.width / 2, y: currentOverlayPosition.y)
        case .bottomRight:
            .init(x: currentOverlayPosition.x + overlaySize.width / 2, y: currentOverlayPosition.y + overlaySize.height / 2)
        case .bottom:
            .init(x: currentOverlayPosition.x, y: currentOverlayPosition.y + overlaySize.height / 2)
        case .bottomLeft:
            .init(x: currentOverlayPosition.x - overlaySize.width / 2, y: currentOverlayPosition.y + overlaySize.height / 2)
        case .left:
            .init(x: currentOverlayPosition.x - overlaySize.width / 2, y: currentOverlayPosition.y)
        }
    }
    
    private func resize(for direction: Direction, delta: CGSize) {
        var deltaPos = CGPoint.zero
        var deltaSize = CGSize.zero
        
        switch direction {
        case .topLeft:
            deltaSize = CGSize(width: -delta.width, height: -delta.height)
            deltaPos = CGPoint(x: delta.width / 2, y: delta.height / 2)
        case .top:
            deltaSize = CGSize(width: 0, height: -delta.height)
            deltaPos = CGPoint(x: 0, y: delta.height / 2)
        case .topRight:
            deltaSize = CGSize(width: delta.width, height: -delta.height)
            deltaPos = CGPoint(x: delta.width / 2, y: delta.height / 2)
        case .right:
            deltaSize = CGSize(width: delta.width, height: 0)
            deltaPos = CGPoint(x: delta.width / 2, y: 0)
        case .bottomRight:
            deltaSize = CGSize(width: delta.width, height: delta.height)
            deltaPos = CGPoint(x: delta.width / 2, y: delta.height / 2)
        case .bottom:
            deltaSize = CGSize(width: 0, height: delta.height)
            deltaPos = CGPoint(x: 0, y: delta.height / 2)
        case .bottomLeft:
            deltaSize = CGSize(width: -delta.width, height: delta.height)
            deltaPos = CGPoint(x: delta.width / 2, y: delta.height / 2)
        case .left:
            deltaSize = CGSize(width: -delta.width, height: 0)
            deltaPos = CGPoint(x: delta.width / 2, y: 0)
        }
        
        onResize(deltaPos, deltaSize)
    }
}

fileprivate struct ResizePoint: View {
    let direction: Direction
    let position: CGPoint
    let onResize: (CGSize) -> Void
    let onResizeEnd: () -> Void
    private let dragPointSize: CGFloat = 10
    
    @State private var isDragging: Bool = false
    
    private var canResizeHorizontally: Bool {
        !(direction == .top || direction == .bottom)
    }
    
    private var canResizeVertically: Bool {
        !(direction == .left || direction == .right)
    }
    
    var body: some View {
        Circle()
            .fill(Color.accentColor)
            .frame(alignment: .leading)
            .frame(width: dragPointSize, height: dragPointSize)
            .position(position)
            .gesture(
                DragGesture(minimumDistance: 0)
                    .onChanged { value in
                        var deltaSize: CGSize = .zero
                        if canResizeVertically {
                            deltaSize.height = value.translation.height
                        }
                        if canResizeHorizontally {
                            deltaSize.width = value.translation.width
                        }
                        onResize(deltaSize)
                    }
                    .onEnded { value in
                        onResizeEnd()
                    }
            )
    }
}
