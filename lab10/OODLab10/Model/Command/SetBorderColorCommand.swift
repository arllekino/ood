//
//  SetBorderColor.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class SetBorderColorCommand: Command {
    let prevColor: MyColor?
    let newColor: MyColor?
    let setColor: (MyColor?) -> Void
    
    init(prevColor: MyColor?, newColor: MyColor?, setColor: @escaping (MyColor?) -> Void)  {
        self.prevColor = prevColor
        self.newColor = newColor
        self.setColor = setColor
    }
    
    func execute() {
        setColor(newColor)
    }
    
    func unexecute() {
        setColor(prevColor)
    }
}
