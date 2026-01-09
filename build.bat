@echo off
REM Build script for NovaCut on Windows

setlocal enabledelayedexpansion

echo ==================================
echo   NovaCut Build Script
echo ==================================
echo.

REM Check if clean build is requested
if "%1"=="clean" (
    echo Cleaning build directory...
    if exist build (
        rmdir /s /q build
        echo [OK] Clean complete
    )
)

REM Create build directory
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

REM Check for CMake
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake not found. Please install CMake 3.20 or later.
    exit /b 1
)

REM Get CMake version
for /f "tokens=3" %%i in ('cmake --version ^| findstr /R "version"') do set CMAKE_VERSION=%%i
echo CMake version: %CMAKE_VERSION%

REM Check for vcpkg toolchain file
if defined VCPKG_ROOT (
    set TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
    echo Found vcpkg at: %VCPKG_ROOT%
) else (
    echo [WARNING] VCPKG_ROOT not set. Trying to find vcpkg...
    
    REM Try common locations
    if exist "C:\vcpkg\scripts\buildsystems\vcpkg.cmake" (
        set TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
        echo Found vcpkg at: C:\vcpkg
    ) else if exist "%USERPROFILE%\vcpkg\scripts\buildsystems\vcpkg.cmake" (
        set TOOLCHAIN_FILE=%USERPROFILE%\vcpkg\scripts\buildsystems\vcpkg.cmake
        echo Found vcpkg at: %USERPROFILE%\vcpkg
    ) else (
        echo [WARNING] vcpkg not found. CMake will try to find dependencies manually.
        set TOOLCHAIN_FILE=
    )
)

REM Configure
echo.
echo Configuring project...

if defined TOOLCHAIN_FILE (
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE%
) else (
    cmake ..
)

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed
    echo.
    echo Make sure you have installed:
    echo   - Qt 6.2 or later
    echo   - FFmpeg 4.4 or later
    echo   - vcpkg ^(recommended for Windows^)
    echo.
    echo To install dependencies with vcpkg:
    echo   vcpkg install qt6-base:x64-windows qt6-multimedia:x64-windows qt6-declarative:x64-windows
    echo   vcpkg install ffmpeg:x64-windows
    exit /b 1
)

REM Build
echo.
echo Building project...
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build failed
    exit /b 1
)

REM Success
echo.
echo ==================================
echo   [OK] Build Successful!
echo ==================================
echo.
echo To run the application:
echo   cd build\Release
echo   NovaCut.exe
echo.

endlocal
