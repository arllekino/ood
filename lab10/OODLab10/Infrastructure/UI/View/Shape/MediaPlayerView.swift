//
//  MediaPlayerView.swift
//  OODLab10
//
//  Created by Miroslav Aktuganov on 16.01.2026.
//

import AVKit
import AVFoundation
import SwiftUI

struct MediaPlayerView: View {
    let url: URL
    
    @State private var player: AVPlayer?
    
    var body: some View {
        VideoPlayer(player: player)
            .onAppear {
                if player == nil {
                    player = AVPlayer(url: url)
                }
            }
            .onDisappear {
                player?.pause()
            }
    }
}
