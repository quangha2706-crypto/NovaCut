# Docker Instructions for NovaCut

## Build Docker Image

```bash
docker build -t novacut .
```

## Run with X11 (Linux)

```bash
# Allow Docker to access X server
xhost +local:docker

# Run container
docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    novacut

# Cleanup
xhost -local:docker
```

## Run with XQuartz (macOS)

```bash
# Install XQuartz first
brew install --cask xquartz

# Start XQuartz and allow connections
open -a XQuartz
# In XQuartz preferences, enable "Allow connections from network clients"

# Get IP address
IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')

# Allow X11 forwarding
xhost + $IP

# Run container
docker run -it --rm \
    -e DISPLAY=$IP:0 \
    novacut
```

## Development Mode (Mount source code)

```bash
docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $(pwd):/app \
    --entrypoint /bin/bash \
    novacut
```

Then inside the container:
```bash
cd /app/build
cmake .. && cmake --build . -j$(nproc)
./NovaCut
```

## Notes

- Windows users should use WSL2 with an X server like VcXsrv or X410
- The Docker image is primarily for testing and development
- For production use, native installation is recommended for better performance
