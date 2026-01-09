# NovaCut - AI Video Editor

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![C++20](https://img.shields.io/badge/C++-20-blue)]()
[![Qt](https://img.shields.io/badge/Qt-6-green)]()
[![FFmpeg](https://img.shields.io/badge/FFmpeg-4.4+-orange)]()

## 🚀 Bắt Đầu Nhanh

**[📖 Hướng dẫn chạy dự án (Tiếng Việt)](QUICKSTART_VI.md)** ← Bắt đầu từ đây!

### Cài đặt nhanh:
```bash
# Linux/macOS
./build.sh

# Windows
build.bat
```

Xem thêm:
- [Build Instructions (English)](docs/BUILD.md)
- [Docker Setup](DOCKER.md)
- [Architecture Overview](docs/ARCHITECTURE.md)

---

## C++ AI Video Editor – Technical Specification

### 1. Mục tiêu
Xây dựng một ứng dụng desktop thuần C++, đa nền tảng, có GUI và trải nghiệm người dùng tương tự CapCut, tích hợp các chức năng AI phục vụ chỉnh sửa video và nội dung đa phương tiện.
### 2. Yêu cầu tổng quát
⦁	Ngôn ngữ chính: C++20
⦁	Đa nền tảng: Windows / Linux / macOS
⦁	Kiến trúc module, dễ mở rộng
⦁	Hỗ trợ GPU nếu có (CUDA / Vulkan / Metal)
### 3. Công nghệ chính
#### 3.1 GUI
⦁	Qt 6
⦁	Qt Widgets
⦁	QML (timeline, preview)
⦁	Qt RHI (OpenGL / Vulkan / Metal)
#### 3.2 Video / Audio Core
⦁	FFmpeg
⦁	libavformat
⦁	libavcodec
⦁	libavfilter
⦁	libswscale
⦁	libswresample
#### 3.3 AI Inference (C++)
⦁	whisper.cpp (Speech-to-Text)
⦁	ONNX Runtime
⦁	OCR
⦁	Text To Speech
⦁	Text detection
### 4. Chức năng
#### 4.1 Video Editor
⦁	Import video / audio / image
⦁	Timeline đa track (video, audio, subtitle)
⦁	Cắt, ghép, trim, split
⦁	Preview realtime
⦁	Export H.264 / H.265
#### 4.2 Subtitle tự động
⦁	Extract audio bằng FFmpeg
⦁	ASR bằng whisper.cpp
⦁	Output: SRT, VTT
#### 4.3 Dịch đa ngôn ngữ
⦁	Client-server
⦁	App C++ gọi API dịch
⦁	Backend ngoài phạm vi C++
#### 4.4 Text To Speech
⦁	ONNX Runtime inference
⦁	Output WAV / MP3
⦁	Gắn audio vào timeline
#### 4.5 OCR truyện tranh
⦁	Detect text region (ONNX)
⦁	OCR (Tesseract / ONNX)
⦁	Output text + bounding box
### 5. Kiến trúc
```
UI (Qt Widgets + QML)
|
Application Core
|-- Timeline Engine
|-- Media Engine (FFmpeg)
|-- AI Engine
    |-- ASR (whisper.cpp)
    |-- OCR (ONNX)
    |-- TTS (ONNX)
|-- Export Engine
```

### 6. Cấu trúc thư mục
```
project-root/
⦁	CMakeLists.txt
⦁	third_party/
⦁	src/
⦁	assets/
⦁	models/
⦁	docs/
```

### 7. Build
⦁	CMake
⦁	MSVC / GCC / Clang
⦁	vcpkg hoặc Conan
### 8. Không bao gồm
⦁	Training model
⦁	Backend AI
⦁	Cloud billing
### 9. Mục tiêu cho AI sinh code
⦁	Skeleton C++ + Qt
⦁	FFmpeg decode & preview
⦁	whisper.cpp ASR
⦁	Timeline engine
⦁	UI mẫu
