//
//  MediaStorageTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("MediaStorage operations")
func testMediaStorage() throws {
    let storage = MediaStorage.shared
    
    let tempDir = FileManager.default.temporaryDirectory
    let sourceFile = tempDir.appendingPathComponent("test_image.png")
    let testData = Data("test image data".utf8)
    try testData.write(to: sourceFile)
    
    let storedURL = try storage.store(url: sourceFile, filename: "test_copy")
    #expect(FileManager.default.fileExists(atPath: storedURL.path))
    
    try storage.delete(url: storedURL)
    #expect(!FileManager.default.fileExists(atPath: storedURL.path))
    
    try? FileManager.default.removeItem(at: sourceFile)
}
