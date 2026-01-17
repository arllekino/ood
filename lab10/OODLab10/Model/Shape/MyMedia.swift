//
//  MyMedia.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 31.12.2025.
//

import Foundation

class MyMedia: Shape {
    enum MediaType {
        case video
        case image
    }
    
    enum ConcreteMediaType {
        case mp4
        case mov
        case png
        case jpg
        case jpeg
    }
    
    let id: UUID
    let url: URL
    
    private(set) var topleft: Point
    private(set) var width: CGFloat
    private(set) var height: CGFloat
    private(set) var fillColor: MyColor? = nil
    private(set) var borderColor: MyColor?
    private(set) var borderWidth: CGFloat
    
    var type: ShapeType { .media }
    var center: Point {
        Point(
            x: topleft.x + width / 2,
            y: topleft.y + height / 2
        )
    }
    
    var boundRectCenter: Point { center }
    
    var mediaType: MediaType {
        let pathExtension = url.pathExtension.lowercased()
        
        if pathExtension == "mp4" || pathExtension == "mov" {
            return .video
        }
        if pathExtension == "jpg" || pathExtension == "png" || pathExtension == "jpeg" {
            return .image
        }
        assert(false)
        return .image
    }
    
    var conreteMediaType: ConcreteMediaType {
        let pathExtension = url.pathExtension.lowercased()
        
        if pathExtension == "mp4" {
            return .mp4
        }
        if pathExtension == "mov" {
            return .mov
        }
        if pathExtension == "jpg" {
            return .jpg
        }
        if pathExtension == "png" {
            return .png
        }
        if pathExtension == "jpeg" {
            return .jpeg
        }
        assert(false)
        return .jpeg
    }
    
    init(id: UUID, url: URL, topleft: Point, width: CGFloat, height: CGFloat, fillColor: MyColor? = nil, borderColor: MyColor?, borderWidth: CGFloat) {
        self.id = id
        self.url = url
        self.topleft = topleft
        self.width = width
        self.height = height
        self.fillColor = fillColor
        self.borderColor = borderColor
        self.borderWidth = borderWidth
    }
    
    func move(to point: Point) {
        topleft = point
    }
    
    func setSize(width: CGFloat, height: CGFloat) {
        self.width = width
        self.height = height
    }
    
    func setFillColor(_ color: MyColor?) {
//        self.fillColor = color
    }
    
    func setBorderColor(_ color: MyColor?) {
        self.borderColor = color
    }
    
    func setBorderWidth(_ width: CGFloat) {
        self.borderWidth = max(0, width)
    }
}
