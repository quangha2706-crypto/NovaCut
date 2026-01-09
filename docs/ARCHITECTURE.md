# NovaCut Architecture

## Overview

NovaCut is a cross-platform desktop video editor built with C++20 and Qt 6, featuring AI-powered capabilities for automatic subtitles, OCR, and text-to-speech.

## Architecture Diagram

```
┌─────────────────────────────────────────────────────────┐
│                    UI Layer (Qt 6)                      │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐ │
│  │ Main Window  │  │   Timeline   │  │   Preview    │ │
│  │  (Widgets)   │  │    (QML)     │  │    (QML)     │ │
│  └──────────────┘  └──────────────┘  └──────────────┘ │
└─────────────────────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────┐
│                  Application Core                        │
│  ┌──────────────┐  ┌──────────────┐                    │
│  │ Application  │  │   Project    │                    │
│  │   Manager    │  │   Manager    │                    │
│  └──────────────┘  └──────────────┘                    │
└─────────────────────────────────────────────────────────┘
                          │
          ┌───────────────┼───────────────┬───────────┐
          ▼               ▼               ▼           ▼
┌──────────────┐  ┌──────────────┐  ┌─────────┐  ┌─────────┐
│   Timeline   │  │    Media     │  │   AI    │  │ Export  │
│    Engine    │  │   Engine     │  │ Engine  │  │ Engine  │
├──────────────┤  ├──────────────┤  ├─────────┤  ├─────────┤
│ • Tracks     │  │ • Decoder    │  │ • ASR   │  │ • H.264 │
│ • Clips      │  │ • Encoder    │  │ • OCR   │  │ • H.265 │
│ • Effects    │  │ • FFmpeg     │  │ • TTS   │  │ • VP9   │
└──────────────┘  └──────────────┘  └─────────┘  └─────────┘
                          │               │
                          ▼               ▼
                  ┌──────────────┐  ┌──────────────┐
                  │   FFmpeg     │  │ ONNX Runtime │
                  │   Libraries  │  │ whisper.cpp  │
                  └──────────────┘  └──────────────┘
```

## Components

### 1. UI Layer

#### Main Window (Qt Widgets)
- Menu bar with File, Edit, View, Help menus
- Toolbars for common actions
- Dock widgets for media library, effects, properties
- Integrates Timeline and Preview widgets

#### Timeline (Qt Widgets + QML)
- Multi-track timeline for video, audio, and subtitles
- Drag-and-drop support
- Clip trimming and splitting
- Zoom and scroll controls
- Real-time playback preview

#### Preview (Qt Widgets + QML)
- Video frame display
- Playback controls
- Real-time rendering
- Waveform visualization

### 2. Application Core

#### Application Manager
- Lifecycle management
- Settings and configuration
- Plugin system (future)

#### Project Manager
- Create, load, save projects
- Project settings (resolution, frame rate)
- Undo/redo system

### 3. Timeline Engine

#### Timeline
- Manages multiple tracks
- Playback state management
- Time synchronization

#### Track
- Video, audio, or subtitle track
- Clip container
- Track-level effects

#### Clip
- Represents media segment on timeline
- Trim and duration control
- Clip-level effects

### 4. Media Engine

#### Decoder
- FFmpeg-based video/audio decoding
- Frame-by-frame access
- Seek support

#### Encoder
- FFmpeg-based video/audio encoding
- Multiple codec support (H.264, H.265, VP9)
- Quality and bitrate control

#### Media Info
- Extract metadata from media files
- Duration, resolution, codec information

### 5. AI Engine

#### Automatic Speech Recognition (ASR)
- whisper.cpp integration
- Multi-language support
- SRT/VTT subtitle export
- Real-time transcription

#### Optical Character Recognition (OCR)
- ONNX Runtime integration
- Text detection and recognition
- Comic book panel detection
- Bounding box extraction

#### Text-to-Speech (TTS)
- ONNX Runtime integration
- Multiple voice options
- WAV/MP3 output
- Speed and pitch control

### 6. Export Engine

#### Export Manager
- Project rendering pipeline
- Multi-format support
- Quality presets
- Progress tracking
- Cancellation support

## Data Flow

### Video Playback Flow
```
Timeline → Decoder → Frame Buffer → Preview Widget → Display
```

### Export Flow
```
Timeline → Render → Encoder → Output File
         ↓
    AI Processing (Subtitles, Effects)
```

### ASR Flow
```
Audio Clip → FFmpeg Extract → whisper.cpp → Segments → SRT/VTT
```

### OCR Flow
```
Image/Frame → ONNX Model → Text Regions → Extracted Text
```

## Threading Model

- **Main Thread**: UI and event handling
- **Decoder Thread**: Video/audio decoding
- **Encoder Thread**: Video rendering and encoding
- **AI Thread Pool**: Parallel AI inference tasks

## File Formats

### Project File (.ncp)
JSON format containing:
- Project metadata
- Timeline structure
- Clip references
- Effect parameters

### Supported Media Formats
- **Video**: MP4, AVI, MOV, MKV, WEBM
- **Audio**: MP3, WAV, AAC, OGG
- **Images**: PNG, JPG, BMP
- **Subtitles**: SRT, VTT

## Dependencies

### Core
- Qt 6.2+ (Core, Widgets, Qml, Quick, Multimedia)
- C++20 standard library

### Media Processing
- FFmpeg 4.4+ (avformat, avcodec, avfilter, avutil, swscale, swresample)

### AI
- whisper.cpp (ASR)
- ONNX Runtime (OCR, TTS)

### Optional
- Tesseract (alternative OCR)

## Build System

CMake 3.20+ with:
- Automatic dependency detection
- Cross-platform configuration
- Optional component building
- Installation targets

## Platform Support

- **Windows**: Windows 10/11, MSVC 2019+
- **Linux**: Ubuntu 20.04+, GCC 10+
- **macOS**: macOS 11+, Clang 11+

## Future Enhancements

1. GPU acceleration (CUDA, Vulkan, Metal)
2. Cloud rendering support
3. Plugin system for effects
4. Real-time collaboration
5. Mobile companion app
6. Advanced color grading
7. Motion tracking
8. 3D title editor
