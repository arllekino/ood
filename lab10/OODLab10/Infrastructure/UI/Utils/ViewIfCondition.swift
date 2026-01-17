//
//  ViewIfCondition.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import SwiftUI

extension View {
    @ViewBuilder func `if`<Content: View>(_ condition: @autoclosure () -> Bool, transform: (Self) -> Content) -> some View {
        if condition() {
            transform(self)
        } else {
            self
        }
    }
}
