# NovaCut - AI Video Editor

## Building from Source

### Prerequisites

- CMake 3.20 or later
- C++20 compatible compiler (MSVC 2019+, GCC 10+, or Clang 11+)
- Qt 6.2 or later
- FFmpeg 4.4 or later
- vcpkg or Conan (for dependency management)

### Dependencies

#### Required
- Qt6 (Core, Widgets, Qml, Quick, Multimedia)
- FFmpeg (libavformat, libavcodec, libavfilter, libavutil, libswscale, libswresample)

#### Optional
- whisper.cpp (for ASR/Speech-to-Text)
- ONNX Runtime (for OCR and TTS)

### Build Instructions

#### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install qt6-base-dev qt6-multimedia-dev \
    libavcodec-dev libavformat-dev libavfilter-dev \
    libavutil-dev libswscale-dev libswresample-dev

# Build
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)

# Run
./NovaCut
```

#### Windows

```bash
# Using vcpkg
vcpkg install qt6 ffmpeg

# Build
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg_root]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release

# Run
Release\NovaCut.exe
```

#### macOS

```bash
# Install dependencies with Homebrew
brew install qt6 ffmpeg cmake

# Build
mkdir build && cd build
cmake ..
cmake --build . -j$(sysctl -n hw.ncpu)

# Run
./NovaCut.app/Contents/MacOS/NovaCut
```

## Project Structure

```
NovaCut/
├── CMakeLists.txt          # Main CMake configuration
├── README.md               # Project overview (Vietnamese)
├── docs/
│   └── BUILD.md            # Build instructions (this file)
├── src/
│   ├── main.cpp            # Application entry point
│   ├── core/               # Core application logic
│   ├── timeline/           # Timeline engine
│   ├── media/              # Media processing (FFmpeg)
│   ├── ai/                 # AI components
│   │   ├── asr/            # Speech-to-Text (Whisper)
│   │   ├── ocr/            # OCR (ONNX)
│   │   └── tts/            # Text-to-Speech (ONNX)
│   ├── export/             # Export engine
│   └── ui/                 # User interface
│       ├── widgets/        # Qt Widgets
│       └── qml/            # QML components
├── third_party/            # Third-party libraries
├── assets/                 # Application resources
└── models/                 # AI model files
```

## Features

### Implemented
- ✅ Project management (create, load, save)
- ✅ Timeline with multiple tracks
- ✅ Media engine with FFmpeg integration
- ✅ Basic UI with Qt Widgets
- ✅ QML-based timeline and preview
- ✅ Export engine for video encoding

### In Progress
- 🚧 Video decoding and preview
- 🚧 Audio waveform visualization
- 🚧 Speech-to-Text with whisper.cpp
- 🚧 OCR for comic books
- 🚧 Text-to-Speech synthesis

### Planned
- 📋 Effects and transitions
- 📋 Color grading
- 📋 Audio mixing
- 📋 Subtitle editor
- 📋 Multi-language translation API

## Contributing

Contributions are welcome! Please follow the existing code style and structure.

## License

See LICENSE file for details.
