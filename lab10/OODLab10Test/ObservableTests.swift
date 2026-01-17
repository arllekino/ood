//
//  ObservableTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("ShapeObservable notifications")
func testShapeObservable() {
    let observable = ShapeObservable()
    
    class MockReceiver: ShapeNotifiable {
        let id = UUID()
        var notificationCount = 0
        
        func notify(_ shapes: [MyAnyShape]) {
            notificationCount += 1
        }
    }
    
    let receiver1 = MockReceiver()
    let receiver2 = MockReceiver()
    
    observable.addReciever(receiver1)
    observable.addReciever(receiver2)
    
    let modelState = EditorModel.State(shapes: [])
    observable.notifyRecievers(state: modelState)
    
    #expect(receiver1.notificationCount == 1)
    #expect(receiver2.notificationCount == 1)
    
    observable.removeReciever(receiver1)
    observable.notifyRecievers(state: modelState)
    
    #expect(receiver1.notificationCount == 1)
    #expect(receiver2.notificationCount == 2)
}
