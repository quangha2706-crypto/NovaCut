# AI Models

This directory contains AI model files for various features.

## Required Models

### Whisper Models (Speech-to-Text)
Download from: https://github.com/ggerganov/whisper.cpp/tree/master/models

Recommended models:
- `ggml-base.bin` - Good balance of speed and accuracy
- `ggml-small.bin` - Better accuracy, slower
- `ggml-medium.bin` - High accuracy for production use

Place downloaded models in this directory.

### OCR Models (Text Detection and Recognition)
Required for comic book OCR feature.

Options:
- ONNX models from PaddleOCR: https://github.com/PaddlePaddle/PaddleOCR
- CRAFT text detection model
- CRNN text recognition model

### TTS Models (Text-to-Speech)
Required for voice synthesis feature.

Options:
- VITS models
- Tacotron2 + WaveGlow
- FastSpeech2

## Model Directory Structure

```
models/
├── whisper/
│   ├── ggml-base.bin
│   ├── ggml-small.bin
│   └── ggml-medium.bin
├── ocr/
│   ├── text_detection.onnx
│   └── text_recognition.onnx
└── tts/
    ├── vits_model.onnx
    └── vocoder.onnx
```

## Notes

- Model files are large and should not be committed to the repository
- Add model files to .gitignore
- Users should download models separately
- Consider providing download scripts for convenience
