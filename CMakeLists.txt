cmake_minimum_required(VERSION 3.20)
project(NovaCut VERSION 1.0.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Qml Quick Multimedia)

# Find FFmpeg (requires FFmpeg to be installed)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED
    libavformat
    libavcodec
    libavfilter
    libavutil
    libswscale
    libswresample
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party
    ${FFMPEG_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/main.cpp
    src/core/Application.cpp
    src/core/Project.cpp
    src/timeline/Timeline.cpp
    src/timeline/Track.cpp
    src/timeline/Clip.cpp
    src/media/MediaEngine.cpp
    src/media/Decoder.cpp
    src/media/Encoder.cpp
    src/ai/AIEngine.cpp
    src/ai/asr/WhisperASR.cpp
    src/ai/ocr/OCREngine.cpp
    src/ai/tts/TTSEngine.cpp
    src/export/ExportEngine.cpp
    src/ui/MainWindow.cpp
    src/ui/widgets/TimelineWidget.cpp
    src/ui/widgets/PreviewWidget.cpp
)

# Header files
set(HEADERS
    src/core/Application.h
    src/core/Project.h
    src/timeline/Timeline.h
    src/timeline/Track.h
    src/timeline/Clip.h
    src/media/MediaEngine.h
    src/media/Decoder.h
    src/media/Encoder.h
    src/ai/AIEngine.h
    src/ai/asr/WhisperASR.h
    src/ai/ocr/OCREngine.h
    src/ai/tts/TTSEngine.h
    src/export/ExportEngine.h
    src/ui/MainWindow.h
    src/ui/widgets/TimelineWidget.h
    src/ui/widgets/PreviewWidget.h
)

# QML resources
qt6_add_resources(QML_RESOURCES src/ui/qml/qml.qrc)

# Create executable
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}
    ${QML_RESOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Qml
    Qt6::Quick
    Qt6::Multimedia
    ${FFMPEG_LIBRARIES}
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    # macOS-specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
endif()

# Install target
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

# Install resources
install(DIRECTORY assets/ DESTINATION share/novacut/assets)
install(DIRECTORY models/ DESTINATION share/novacut/models)
