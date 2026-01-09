#!/bin/bash
# Build script for NovaCut on Linux/macOS

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}==================================${NC}"
echo -e "${GREEN}  NovaCut Build Script${NC}"
echo -e "${GREEN}==================================${NC}"
echo ""

# Check if clean build is requested
if [ "$1" == "clean" ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf build
    echo -e "${GREEN}✓ Clean complete${NC}"
fi

# Create build directory
if [ ! -d "build" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir build
fi

cd build

# Detect OS
OS="$(uname -s)"
case "${OS}" in
    Linux*)     
        echo -e "${GREEN}Detected: Linux${NC}"
        ;;
    Darwin*)    
        echo -e "${GREEN}Detected: macOS${NC}"
        # Try to find Qt6 from Homebrew
        if command -v brew &> /dev/null; then
            QT_PATH=$(brew --prefix qt6 2>/dev/null || echo "")
            if [ -n "$QT_PATH" ]; then
                echo -e "${GREEN}Found Qt6 at: $QT_PATH${NC}"
                CMAKE_ARGS="-DCMAKE_PREFIX_PATH=$QT_PATH"
            fi
        fi
        ;;
    *)          
        echo -e "${RED}Unknown OS: ${OS}${NC}"
        exit 1
        ;;
esac

# Check for CMake
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}✗ CMake not found. Please install CMake 3.20 or later.${NC}"
    exit 1
fi

# Check CMake version
CMAKE_VERSION=$(cmake --version | head -n1 | cut -d' ' -f3)
echo -e "${GREEN}CMake version: $CMAKE_VERSION${NC}"

# Configure
echo ""
echo -e "${YELLOW}Configuring project...${NC}"
if ! cmake .. $CMAKE_ARGS; then
    echo -e "${RED}✗ CMake configuration failed${NC}"
    echo -e "${YELLOW}Make sure you have installed:${NC}"
    echo -e "  - Qt 6.2 or later"
    echo -e "  - FFmpeg 4.4 or later"
    echo -e "  - pkg-config"
    exit 1
fi

# Build
echo ""
echo -e "${YELLOW}Building project...${NC}"

# Detect number of cores
if [ "$OS" == "Darwin" ]; then
    CORES=$(sysctl -n hw.ncpu)
else
    CORES=$(nproc)
fi

if ! cmake --build . -j$CORES; then
    echo -e "${RED}✗ Build failed${NC}"
    exit 1
fi

# Success
echo ""
echo -e "${GREEN}==================================${NC}"
echo -e "${GREEN}  ✓ Build Successful!${NC}"
echo -e "${GREEN}==================================${NC}"
echo ""
echo -e "${YELLOW}To run the application:${NC}"
if [ "$OS" == "Darwin" ]; then
    echo -e "  cd build && ./NovaCut"
    echo -e "  or: cd build && open NovaCut.app"
else
    echo -e "  cd build && ./NovaCut"
fi
echo ""
