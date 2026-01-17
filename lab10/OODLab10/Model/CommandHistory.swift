//
//  CommandHistory.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class CommandHistory {
    private let maxCommmnadsCount: Int = 20
    private var undoCommands: [any Command] = []
    private var redoCommands: [any Command] = []
    
    func addAndExecute(_ command: any Command) {
        undoCommands.append(command)
        redoCommands.removeAll()
        
        if undoCommands.count > maxCommmnadsCount {
            undoCommands.removeFirst()
        }
        
        command.execute()
    }
    
    func undo() {
        if undoCommands.isEmpty { return }
        
        let command = undoCommands.popLast()!
        command.unexecute()
        redoCommands.append(command)
    }
    
    func redo() {
        if redoCommands.isEmpty { return }
        
        let command = redoCommands.popLast()!
        command.execute()
        undoCommands.append(command)
    }
}
