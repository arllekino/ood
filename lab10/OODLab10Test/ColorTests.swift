//
//  ColorTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import SwiftUI
import Testing
@testable import OODLab10

@Test("MyColor")
func testMyColor() {
    let color = MyColor(red: 255, green: 128, blue: 0, alpha: 200)
    
    #expect(color.red == 255)
    #expect(color.green == 128)
    #expect(color.blue == 0)
    #expect(color.alpha == 200)
    
    #expect(MyColor.black.red == 0)
    #expect(MyColor.black.green == 0)
    #expect(MyColor.black.blue == 0)
    #expect(MyColor.black.blue == 255)
}
