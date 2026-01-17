//
//  Command.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

protocol Command {
    func execute()
    func unexecute()
}
