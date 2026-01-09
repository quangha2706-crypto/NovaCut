# Hướng Dẫn Nhanh - NovaCut Video Editor

Tài liệu này hướng dẫn cách chạy dự án NovaCut trên máy tính của bạn.

## Yêu Cầu Hệ Thống

### Tất Cả Các Nền Tảng
- **CMake**: Phiên bản 3.20 trở lên
- **Compiler hỗ trợ C++20**:
  - Windows: Visual Studio 2019 trở lên
  - Linux: GCC 10+ hoặc Clang 11+
  - macOS: Xcode 12+ hoặc Clang 11+

### Thư Viện Bắt Buộc
- **Qt 6**: Phiên bản 6.2 trở lên (Core, Widgets, Qml, Quick, Multimedia)
- **FFmpeg**: Phiên bản 4.4 trở lên

## Hướng Dẫn Theo Hệ Điều Hành

### 🐧 Linux (Ubuntu/Debian)

#### Bước 1: Cài đặt các thư viện cần thiết
```bash
# Cập nhật package list
sudo apt-get update

# Cài đặt các công cụ build
sudo apt-get install -y build-essential cmake git pkg-config

# Cài đặt Qt 6
sudo apt-get install -y qt6-base-dev qt6-multimedia-dev qt6-declarative-dev

# Cài đặt FFmpeg
sudo apt-get install -y libavcodec-dev libavformat-dev libavfilter-dev \
    libavutil-dev libswscale-dev libswresample-dev
```

#### Bước 2: Build dự án
```bash
# Tạo thư mục build
mkdir build
cd build

# Cấu hình với CMake
cmake ..

# Build (sử dụng tất cả các cores)
cmake --build . -j$(nproc)
```

#### Bước 3: Chạy ứng dụng
```bash
# Từ thư mục build
./NovaCut
```

### 🪟 Windows

#### Bước 1: Cài đặt công cụ cần thiết
1. **Visual Studio 2019 hoặc mới hơn** với C++ Desktop Development
2. **CMake**: Tải từ https://cmake.org/download/
3. **vcpkg** (để quản lý thư viện):
```cmd
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

#### Bước 2: Cài đặt Qt và FFmpeg qua vcpkg
```cmd
# Cài đặt Qt6
vcpkg install qt6-base:x64-windows qt6-multimedia:x64-windows qt6-declarative:x64-windows

# Cài đặt FFmpeg
vcpkg install ffmpeg:x64-windows

# Tích hợp vcpkg với Visual Studio
vcpkg integrate install
```

#### Bước 3: Build dự án
```cmd
# Tạo thư mục build
mkdir build
cd build

# Cấu hình với CMake (thay [vcpkg_path] bằng đường dẫn thực tế)
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg_path]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build . --config Release
```

#### Bước 4: Chạy ứng dụng
```cmd
# Từ thư mục build
Release\NovaCut.exe
```

### 🍎 macOS

#### Bước 1: Cài đặt Homebrew (nếu chưa có)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### Bước 2: Cài đặt các thư viện cần thiết
```bash
# Cài đặt các công cụ build
brew install cmake pkg-config

# Cài đặt Qt 6
brew install qt6

# Cài đặt FFmpeg
brew install ffmpeg
```

#### Bước 3: Build dự án
```bash
# Tạo thư mục build
mkdir build
cd build

# Cấu hình với CMake (Qt từ Homebrew)
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt6)

# Build
cmake --build . -j$(sysctl -n hw.ncpu)
```

#### Bước 4: Chạy ứng dụng
```bash
# Từ thư mục build
./NovaCut
# Hoặc
open NovaCut.app
```

## Scripts Tự Động

Dự án cung cấp các script để tự động hóa quá trình build:

### Linux/macOS:
```bash
# Build dự án
./build.sh

# Clean và rebuild
./build.sh clean
```

### Windows:
```cmd
# Build dự án
build.bat

# Clean và rebuild
build.bat clean
```

## Xử Lý Lỗi Thường Gặp

### Lỗi: "Qt6 not found"
**Giải pháp**: Chỉ định đường dẫn Qt khi chạy cmake:
```bash
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6
```

### Lỗi: "FFmpeg libraries not found"
**Giải pháp Linux**: Cài đặt pkg-config
```bash
sudo apt-get install pkg-config
```

**Giải pháp Windows**: Đảm bảo vcpkg đã được tích hợp đúng

**Giải pháp macOS**: Cài đặt pkg-config
```bash
brew install pkg-config
```

### Lỗi: "Compiler does not support C++20"
**Giải pháp**: Cập nhật compiler lên phiên bản mới hơn:
- Linux: `sudo apt-get install gcc-10 g++-10`
- macOS: Cập nhật Xcode Command Line Tools
- Windows: Cài đặt Visual Studio 2019 hoặc mới hơn

## Chạy Ứng Dụng Lần Đầu

Khi chạy ứng dụng lần đầu, bạn sẽ thấy:
- **Main Window**: Cửa sổ chính với menu bar và toolbars
- **Preview Area**: Vùng xem trước video (phía trên)
- **Timeline**: Timeline để chỉnh sửa (phía dưới)

### Các Chức Năng Cơ Bản:
- **File → New Project**: Tạo project mới
- **File → Import Media**: Import video/audio/hình ảnh
- **Space**: Play/Pause
- **Mouse wheel trên timeline**: Zoom in/out

## Tài Liệu Bổ Sung

- **Chi tiết về build**: Xem `docs/BUILD.md`
- **Kiến trúc hệ thống**: Xem `docs/ARCHITECTURE.md`
- **Tổng quan code**: Xem `docs/CODE_SUMMARY.md`

## Lưu Ý Quan Trọng

⚠️ **Đây là phiên bản skeleton/beta**: Một số tính năng AI (ASR, OCR, TTS) chưa được tích hợp đầy đủ và cần thêm các thư viện bổ sung:
- **whisper.cpp** cho Speech-to-Text
- **ONNX Runtime** cho OCR và TTS

Xem `third_party/README.md` và `models/README.md` để biết cách tích hợp các tính năng này.

## Hỗ Trợ

Nếu gặp vấn đề, vui lòng:
1. Kiểm tra phiên bản của Qt và FFmpeg
2. Đảm bảo tất cả dependencies đã được cài đặt đúng
3. Xem log lỗi từ CMake hoặc compiler
4. Tham khảo `docs/BUILD.md` cho hướng dẫn chi tiết hơn
