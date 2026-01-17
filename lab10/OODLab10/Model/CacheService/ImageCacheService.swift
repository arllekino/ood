//
//  ImageCacheService.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 16.01.2026.
//

import Foundation
import AppKit

protocol ImageCaching {
    func image(for url: URL) -> NSImage?
    func save(_ image: NSImage, for url: URL)
    func delete(for url: URL)
}

class ImageCacheService: ImageCaching {
    static let shared = ImageCacheService()
    
    private let cache = NSCache<NSURL, NSImage>()
    private let queue = DispatchQueue(label: "com.app.imagecache", attributes: .concurrent)
    
    private init() {
        cache.countLimit = 100
    }
    
    func image(for url: URL) -> NSImage? {
        queue.sync {
            cache.object(forKey: url as NSURL)
        }
    }

    func save(_ image: NSImage, for url: URL) {
        queue.async(flags: .barrier) {
            self.cache.setObject(image, forKey: url as NSURL)
        }
    }

    func delete(for url: URL) {
        queue.async(flags: .barrier) {
            self.cache.removeObject(forKey: url as NSURL)
        }
    }
}
