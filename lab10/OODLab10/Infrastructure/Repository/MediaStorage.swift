//
//  MediaStorage.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 31.12.2025.
//

import Foundation

class MediaStorage {
    static let shared = MediaStorage()
    
    private let fileManager = FileManager.default
    private let storageDirectory: URL
    
    init() {
        storageDirectory = fileManager
            .urls(for: .cachesDirectory, in: .userDomainMask)[0]
            .appendingPathComponent("ShapeEditor", isDirectory: true)
        
        try? fileManager.createDirectory(at: storageDirectory, withIntermediateDirectories: true)
    }
    
    func store(url: URL, filename: String) throws -> URL {
        let destDir = getDirectory(for: filename)
        let destFile = makeFilePath(for: filename, url: url)

        if fileManager.fileExists(atPath: destDir.path()) {
            try delete(url: destDir)
        }
        
        try fileManager.createDirectory(at: destDir, withIntermediateDirectories: true)
        try fileManager.copyItem(at: url, to: destFile)
        
        return destFile
    }
    
    func delete(url: URL) throws {
        if fileManager.fileExists(atPath: url.path) {
            try fileManager.removeItem(at: url)
        }
    }
    
    private func getDirectory(for key: String) -> URL {
        storageDirectory.appendingPathComponent(key, isDirectory: true)
    }
    
    private func makeFilePath(for key: String, url: URL) -> URL {
        let destDir = getDirectory(for: key)
        return destDir.appendingPathComponent(url.lastPathComponent, isDirectory: false)
    }
}
