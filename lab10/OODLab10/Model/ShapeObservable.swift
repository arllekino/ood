//
//  ShapeObservable.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 20.12.2025.
//

import Foundation

class ShapeObservable {
    private var recievers: [any ShapeNotifiable] = []
    
    func addReciever(_ reciever: any ShapeNotifiable) {
        recievers.append(reciever)
    }
    
    func removeReciever(_ reciever: any ShapeNotifiable) {
        recievers.removeAll(where: { $0.id == reciever.id })
    }
    
    func notifyRecievers(state: EditorModel.State) {
        recievers.forEach { reciever in
            reciever.notify(state.shapes)
        }
    }
}
