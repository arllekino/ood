//
//  OODLab10App.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import SwiftUI

@main
struct OODLab10App: App {
    let redactorModel = EditorModel()
    
    var body: some Scene {
        WindowGroup {
            ContentView(
                viewModel: EditorViewModel(
                    redactorModel: redactorModel
                )
            )
        }
        Window("Detail", id: "detail") {
            ContentView(
                viewModel: EditorViewModel(
                    redactorModel: redactorModel
                )
            )
        }
    }
}

// поправить вылет приложени, запущенное не при xcode, при добавлении картинки
