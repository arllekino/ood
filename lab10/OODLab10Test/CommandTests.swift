//
//  CommandTests.swift
//  OODLab10Test
//
//  Created by Miroslav Aktuganov on 11.01.2026.
//

import Foundation
import Testing
@testable import OODLab10

@Test("CommandHistory operations")
func testCommandHistory() {
    let history = CommandHistory()
    
    class MockCommand: Command {
        var executeCount = 0
        var unexecuteCount = 0
        
        func execute() {
            executeCount += 1
        }
        
        func unexecute() {
            unexecuteCount += 1
        }
    }
    
    let command1 = MockCommand()
    let command2 = MockCommand()
    
    history.addAndExecute(command1)
    #expect(command1.executeCount == 1)
    #expect(command1.unexecuteCount == 0)
    
    history.addAndExecute(command2)
    #expect(command2.executeCount == 1)
    
    history.undo()
    #expect(command2.unexecuteCount == 1)
    
    history.redo()
    #expect(command2.executeCount == 2)
    
    history.undo()
    history.undo()
    #expect(command1.unexecuteCount == 1)
}

struct CommandTests {
    class MockReceiver {
        var shapes: [MyAnyShape] = []
        var disposedURLs: [URL] = []
        var deletedURLs: [URL] = []
        
        func createShape(_ shape: MyAnyShape) {
            shapes.append(shape)
        }
        
        func deleteShape(_ id: UUID) {
            shapes.removeAll { $0.id == id }
        }
        
        func onCommandDispose(_ url: URL) {
            disposedURLs.append(url)
        }
        
        func onCommandDelete(_ url: URL) {
            deletedURLs.append(url)
        }
    }
    
    let testRect = MyRectangle(
        id: UUID(),
        topleft: Point(x: 0, y: 0),
        width: 100,
        height: 100,
        fillColor: .cyan,
        borderColor: nil,
        borderWidth: 0
    )
    
    let testMedia = MyMedia(
        id: UUID(),
        url: URL(fileURLWithPath: "/tmp/video.mp4"),
        topleft: Point(x: 0, y: 0),
        width: 100,
        height: 100,
        fillColor: nil,
        borderColor: nil,
        borderWidth: 0
    )
    
    @Test("CreateShapeCommand: Execute добавляет фигуру, Unexecute удаляет")
    func testCreateShapeLogic() {
        let mock = MockReceiver()
        let command = CreateShapeCommand(
            shape: .rectangle(testRect),
            createShape: mock.createShape,
            deleteShape: mock.deleteShape,
            onCommandDispose: mock.onCommandDispose
        )
        
        command.execute()
        #expect(mock.shapes.count == 1)
        #expect(mock.shapes.first?.id == testRect.id)
        
        command.unexecute()
        #expect(mock.shapes.isEmpty)
    }
    
    @Test("CreateShapeCommand: Deinit удаляет файл, если создание отменено (Undo)")
    func testCreateShapeDeinit_Undo() {
        let mock = MockReceiver()
        
        var command: CreateShapeCommand? = CreateShapeCommand(
            shape: .media(testMedia),
            createShape: mock.createShape,
            deleteShape: mock.deleteShape,
            onCommandDispose: mock.onCommandDispose
        )
        
        command?.execute()
        command?.unexecute()
        command = nil
        
        #expect(mock.disposedURLs.count == 1)
        #expect(mock.disposedURLs.first == testMedia.url)
    }
    
    @Test("CreateShapeCommand: Deinit НЕ удаляет файл, если команда выполнена")
    func testCreateShapeDeinit_Executed() {
        let mock = MockReceiver()
        var command: CreateShapeCommand? = CreateShapeCommand(
            shape: .media(testMedia),
            createShape: mock.createShape,
            deleteShape: mock.deleteShape,
            onCommandDispose: mock.onCommandDispose
        )
        
        command?.execute()
        command = nil
        
        #expect(mock.disposedURLs.isEmpty)
    }
    
    @Test("DeleteShapeCommand: Execute удаляет фигуру, Unexecute возвращает")
    func testDeleteShapeLogic() {
        let mock = MockReceiver()
        mock.shapes.append(.rectangle(testRect))
        
        let command = DeleteShapeCommand(
            shape: .rectangle(testRect),
            createShape: mock.createShape,
            deleteShape: mock.deleteShape,
            onCommandDelete: mock.onCommandDelete
        )
        
        command.execute()
        #expect(mock.shapes.isEmpty)
        
        command.unexecute()
        #expect(mock.shapes.count == 1)
        #expect(mock.shapes.first?.id == testRect.id)
    }
    
    @Test("DeleteShapeCommand: Deinit удаляет файл окончательно, если фигура удалена")
    func testDeleteShapeDeinit_Executed() {
        let mock = MockReceiver()
        var command: DeleteShapeCommand? = DeleteShapeCommand(
            shape: .media(testMedia),
            createShape: mock.createShape,
            deleteShape: mock.deleteShape,
            onCommandDelete: mock.onCommandDelete
        )
        
        command?.execute()
        command = nil
        
        #expect(mock.deletedURLs.count == 1)
        #expect(mock.deletedURLs.first == testMedia.url)
    }
    
    @Test("DeleteShapeCommand: Deinit не удаляет файл, если удаление отменено")
    func testDeleteShapeDeinit_Undo() {
        let mock = MockReceiver()
        var command: DeleteShapeCommand? = DeleteShapeCommand(
            shape: .media(testMedia),
            createShape: mock.createShape,
            deleteShape: mock.deleteShape,
            onCommandDelete: mock.onCommandDelete
        )
        
        command?.execute()
        command?.unexecute()
        command = nil
        
        #expect(mock.deletedURLs.isEmpty)
    }
    
    @Test("MoveShapeCommand: меняет координаты")
    func testMoveShape() {
        var currentPoint = Point(x: 0, y: 0)
        let start = Point(x: 10, y: 10)
        let end = Point(x: 50, y: 50)
        
        let command = MoveShapeCommand(
            prevPoint: start,
            newPoint: end,
            moveShape: { pt in currentPoint = pt }
        )
        
        command.execute()
        #expect(currentPoint.x == 50)
        #expect(currentPoint.y == 50)
        
        command.unexecute()
        #expect(currentPoint.x == 10)
        #expect(currentPoint.y == 10)
    }
    
    @Test("ResizeShapeCommand: меняет размер и позицию")
    func testResizeShape() {
        var currentState: ShapeState?
        let oldState = ShapeState(position: Point(x: 0, y: 0), size: Size(width: 10, height: 10))
        let newState = ShapeState(position: Point(x: 5, y: 5), size: Size(width: 20, height: 20))
        
        let command = ResizeShapeCommand(
            id: UUID(),
            oldState: oldState,
            newState: newState,
            resizeShape: { _, state in currentState = state }
        )
        
        command.execute()
        #expect(currentState?.size.width == 20)
        #expect(currentState?.position.x == 5)
        
        command.unexecute()
        #expect(currentState?.size.width == 10)
        #expect(currentState?.position.x == 0)
    }
    
    @Test("SetFillColorCommand")
    func testSetFillColor() {
        var capturedColor: MyColor?
        let red = MyColor(red: 255, green: 0, blue: 0, alpha: 255)
        let blue = MyColor(red: 0, green: 0, blue: 255, alpha: 255)
        
        let command = SetFillColorCommand(
            prevColor: red,
            newColor: blue,
            setColor: { color in capturedColor = color }
        )
        
        command.execute()
        #expect(capturedColor?.blue == 255)
        
        command.unexecute()
        #expect(capturedColor?.red == 255)
    }
    
    @Test("SetBorderWidthCommand")
    func testSetBorderWidth() {
        var width: CGFloat = 0
        let command = SetBorderWidthCommand(
            prevBorderWidth: 1.0,
            newBorderWidth: 5.0,
            setBorderWidth: { w in width = w }
        )
        
        command.execute()
        #expect(width == 5.0)
        
        command.unexecute()
        #expect(width == 1.0)
    }
}
