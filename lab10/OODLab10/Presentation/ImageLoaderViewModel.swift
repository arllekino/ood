//
//  ImageLoaderViewModel.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 16.01.2026.
//

import SwiftUI
import Combine

class ImageLoaderViewModel: ObservableObject {
    @Published var image: Image?
    
    private let url: URL
    private let cacheService: ImageCaching
    
    init(url: URL, cacheService: ImageCaching = ImageCacheService.shared) {
        self.url = url
        self.cacheService = cacheService
        
        if let cachedImage = cacheService.image(for: url) {
            self.image = Image(nsImage: cachedImage)
        }
    }
    
    deinit {
        cacheService.delete(for: url)
    }
    
    func load() async {
        if image != nil { return }
        
        if let cachedImage = cacheService.image(for: url) {
            await MainActor.run {
                self.image = Image(nsImage: cachedImage)
            }
            return
        }
        
        do {
            let (data, _) = try await URLSession.shared.data(from: url)
            if let nsImage = NSImage(data: data) {
                cacheService.save(nsImage, for: url)
                
                await MainActor.run {
                    self.image = Image(nsImage: nsImage)
                }
            }
        } catch {
            print("Error loading image: \(error)")
        }
    }
}
