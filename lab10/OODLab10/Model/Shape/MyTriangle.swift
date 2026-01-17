//
//  MyTriangle.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 13.12.2025.
//

import Foundation

class MyTriangle: Shape {
    let id: UUID
    private(set) var vertices: [Point]
    private(set) var fillColor: MyColor?
    private(set) var borderColor: MyColor?
    private(set) var borderWidth: CGFloat
    
    var type: ShapeType { .triangle }
    var width: CGFloat {
        let minX = vertices.map { $0.x }.min() ?? 0
        let maxX = vertices.map { $0.x }.max() ?? 0
        return maxX - minX
    }
    
    var height: CGFloat {
        let minY = vertices.map { $0.y }.min() ?? 0
        let maxY = vertices.map { $0.y }.max() ?? 0
        return maxY - minY
    }
    
    var center: Point {
        let avgX = vertices.map { $0.x }.reduce(0, +) / CGFloat(vertices.count)
        let avgY = vertices.map { $0.y }.reduce(0, +) / CGFloat(vertices.count)
        return Point(x: avgX, y: avgY)
    }
    
    var boundRectCenter: Point {
        let x = (vertices.minX + vertices.maxX) / 2
        let y = (vertices.minY + vertices.maxY ) / 2
        return Point(x: x, y: y)
    }
    
    init(id: UUID, vertices: [Point], fillColor: MyColor?, borderColor: MyColor?, borderWidth: CGFloat) {
        if vertices.count != 3 {
            assert(false)
            self.id = id
            self.vertices = [.init(x: 0, y: 0), .init(x: 0, y: 0), .init(x: 0, y: 0)]
            self.fillColor = fillColor
            self.borderColor = borderColor
            self.borderWidth = borderWidth
            return
//            fatalError("Triangle must have exactly 3 vertices")
        }
        self.id = id
        self.vertices = vertices
        self.fillColor = fillColor
        self.borderColor = borderColor
        self.borderWidth = borderWidth
    }
    
    func move(to point: Point) {
        let currentCenter = center
        let offsetX = point.x - currentCenter.x
        let offsetY = point.y - currentCenter.y
        
        vertices = vertices.map { vertex in
            Point(x: vertex.x + offsetX, y: vertex.y + offsetY)
        }
    }
    
    func setSize(width: CGFloat, height: CGFloat) {
        guard width > 0 && height > 0 else { return }
        
        let currentWidth = self.width
        let currentHeight = self.height
        
        guard currentWidth > 0 && currentHeight > 0 else { return }
        
        let currentCenter = center
        
        let minX = vertices.map { $0.x }.min() ?? 0
        let minY = vertices.map { $0.y }.min() ?? 0
        
        let scaleX = width / currentWidth
        let scaleY = height / currentHeight
        
        var newVertices: [Point] = []
        
        for vertex in vertices {
            let relativeX = vertex.x - minX
            let relativeY = vertex.y - minY
            
            let scaledX = relativeX * scaleX
            let scaledY = relativeY * scaleY
            
            let newX = minX + scaledX
            let newY = minY + scaledY
            
            newVertices.append(Point(x: newX, y: newY))
        }
        
        let newCenter = {
            let avgX = newVertices.map { $0.x }.reduce(0, +) / CGFloat(newVertices.count)
            let avgY = newVertices.map { $0.y }.reduce(0, +) / CGFloat(newVertices.count)
            return Point(x: avgX, y: avgY)
        }()
        
        let offsetX = currentCenter.x - newCenter.x
        let offsetY = currentCenter.y - newCenter.y
        
        vertices = newVertices.map { vertex in
            Point(x: vertex.x + offsetX, y: vertex.y + offsetY)
        }
    }
    
    func setFillColor(_ color: MyColor?) {
        self.fillColor = color
    }
    
    func setBorderColor(_ color: MyColor?) {
        self.borderColor = color
    }
    
    func setBorderWidth(_ width: CGFloat) {
        self.borderWidth = max(0, width)
    }
}


extension [Point] {
    var minX: CGFloat {
        self.min(by: { $0.x < $1.x })!.x
    }
    
    var maxX: CGFloat {
        self.max(by: { $0.x < $1.x })!.x
    }
    
    var minY: CGFloat {
        self.min(by: { $0.y < $1.y })!.y
    }
    
    var maxY: CGFloat {
        self.max(by: { $0.y < $1.y })!.y
    }
}
