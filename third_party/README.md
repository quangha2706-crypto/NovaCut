# Third-Party Libraries

This directory contains third-party libraries and dependencies.

## Required Libraries

### whisper.cpp
- **Purpose**: Automatic Speech Recognition (ASR)
- **License**: MIT
- **Repository**: https://github.com/ggerganov/whisper.cpp

To integrate:
1. Clone the repository into this directory
2. Follow build instructions from the repository
3. Update CMakeLists.txt to link against whisper.cpp

### ONNX Runtime
- **Purpose**: OCR and TTS inference
- **License**: MIT
- **Website**: https://onnxruntime.ai/

Installation options:
- **vcpkg**: `vcpkg install onnxruntime`
- **Conan**: `conan install onnxruntime`
- **Manual**: Download from https://github.com/microsoft/onnxruntime/releases

## Optional Libraries

### Tesseract OCR
- **Purpose**: Alternative OCR engine
- **License**: Apache 2.0
- **Website**: https://github.com/tesseract-ocr/tesseract

## Notes

- All third-party libraries should maintain their original licenses
- See individual library documentation for build instructions
- Dependencies can be managed through vcpkg or Conan for easier setup
