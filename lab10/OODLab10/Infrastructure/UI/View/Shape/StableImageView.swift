//
//  StableImageView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 16.01.2026.
//

import SwiftUI

struct StableImageView: View {
    @StateObject private var viewModel: ImageLoaderViewModel
    
    init(url: URL) {
        _viewModel = StateObject(wrappedValue: ImageLoaderViewModel(url: url))
    }
    
    var body: some View {
        Group {
            if let image = viewModel.image {
                image
                    .resizable()
            } else {
                ProgressView()
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                    .task {
                        await viewModel.load()
                    }
            }
        }
    }
}
