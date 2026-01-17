//
//  Changable.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 12.12.2025.
//

import Foundation

// https://habr.com/ru/companies/hh/articles/511636/

protocol Changeable {
    init(copy: ChangeableWrapper<Self>)
}

extension Changeable {
    func changing(_ change: (inout ChangeableWrapper<Self>) -> Void) -> Self {
        var copy = ChangeableWrapper<Self>(self)
        change(&copy)
        return Self(copy: copy)
    }
}

@dynamicMemberLookup
struct ChangeableWrapper<Wrapped> {
    private let wrapped: Wrapped
    private var changes: [PartialKeyPath<Wrapped>: Any] = [:]

    init(_ wrapped: Wrapped) {
        self.wrapped = wrapped
    }

    subscript<T>(dynamicMember keyPath: KeyPath<Wrapped, T>) -> T {
        get {
            changes[keyPath].flatMap { $0 as? T } ?? wrapped[keyPath: keyPath]
        }
        set {
            changes[keyPath] = newValue
        }
    }
    
    subscript<T: Changeable>(
        dynamicMember keyPath: KeyPath<Wrapped, T>
    ) -> ChangeableWrapper<T> {
        get {
            ChangeableWrapper<T>(self[dynamicMember: keyPath])
        }
        set {
            self[dynamicMember: keyPath] = T(copy: newValue)
        }
    }
}
