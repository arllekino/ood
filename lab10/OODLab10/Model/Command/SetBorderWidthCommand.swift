//
//  SetBorderWidthCommand.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class SetBorderWidthCommand: Command {
    let prevBorderWidth: CGFloat
    let newBorderWidth: CGFloat
    let setBorderWidth: (CGFloat) -> Void
    
    init(prevBorderWidth: CGFloat, newBorderWidth: CGFloat, setBorderWidth: @escaping (CGFloat) -> Void) {
        self.prevBorderWidth = prevBorderWidth
        self.newBorderWidth = newBorderWidth
        self.setBorderWidth = setBorderWidth
    }
    
    func execute() {
        setBorderWidth(newBorderWidth)
    }
    
    func unexecute() {
        setBorderWidth(prevBorderWidth)
    }
}
