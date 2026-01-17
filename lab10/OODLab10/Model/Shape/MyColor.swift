//
//  MyColor.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import SwiftUI

struct MyColor: Hashable {
    var red: UInt8
    var green: UInt8
    var blue: UInt8
    var alpha: UInt8
    
    var asSwiftUI: Color {
        Color(
            red: CGFloat(self.red) / 255.0,
            green: CGFloat(self.green) / 255.0,
            blue: CGFloat(self.blue) / 255.0
        )
        .opacity(CGFloat(self.alpha) / 255.0)
    }
   
    init(red: UInt8, green: UInt8, blue: UInt8, alpha: UInt8 = 255) {
        self.red = red
        self.green = green
        self.blue = blue
        self.alpha = alpha
    }
    
    static let clear = MyColor(red: 0, green: 0, blue: 0, alpha: 0)
    static let black = MyColor(red: 0, green: 0, blue: 0)
    static let white = MyColor(red: 255, green: 255, blue: 255)
    static let gray = MyColor(red: 128, green: 128, blue: 128)
    static let lightGray = MyColor(red: 192, green: 192, blue: 192)
    static let darkGray = MyColor(red: 64, green: 64, blue: 64)
    
    static let red = MyColor(red: 255, green: 0, blue: 0)
    static let green = MyColor(red: 0, green: 255, blue: 0)
    static let blue = MyColor(red: 0, green: 0, blue: 255)
    
    static let yellow = MyColor(red: 255, green: 255, blue: 0)
    static let magenta = MyColor(red: 255, green: 0, blue: 255)
    static let cyan = MyColor(red: 0, green: 255, blue: 255)
    
    static let orange = MyColor(red: 255, green: 165, blue: 0)
    static let purple = MyColor(red: 128, green: 0, blue: 128)
    static let pink = MyColor(red: 255, green: 192, blue: 203)
    static let brown = MyColor(red: 139, green: 69, blue: 19)
    static let teal = MyColor(red: 0, green: 128, blue: 128)
    static let indigo = MyColor(red: 75, green: 0, blue: 130)
}
