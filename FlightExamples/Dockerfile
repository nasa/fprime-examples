FROM ubuntu:24.10

ARG USER="fprime-user"

ARG OPENCV_VERSION=4.11.0

# F Prime and generic utilities
RUN apt-get update && apt-get install -y \
    sudo \
    build-essential \
    wget \
    curl \
    tar \
    vim \
    git  \
    gcc \
    g++ \
    gdb \
    make \
    cmake \
    ninja-build \
    python3 \
    python3-pip \ 
    python3-venv
# Required for OpenCV
RUN apt-get install -y \
    python3-numpy \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer1.0-dev

# Build and install OpenCV
RUN mkdir opencv && cd opencv && \
    wget -O opencv-${OPENCV_VERSION}.tar.gz https://github.com/opencv/opencv/archive/refs/tags/${OPENCV_VERSION}.tar.gz && \
    tar -xzf opencv-${OPENCV_VERSION}.tar.gz && rm opencv-${OPENCV_VERSION}.tar.gz && \
    mkdir -p build && cd build && \
    cmake -GNinja ../opencv-${OPENCV_VERSION} \
        -DBUILD_SHARED_LIBS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_PERF_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_opencv_python3=OFF \
        -DBUILD_opencv_python2=OFF \
        -DBUILD_opencv_java=OFF \
        -DBUILD_opencv_apps=OFF \
        -DOPENCV_GENERATE_PKGCONFIG=ON && \
    cmake --build . && \
    cmake --build . --target install

# Create fprime-user and give sudo access
RUN useradd --groups sudo --create-home --shell /bin/bash ${USER} && \
    echo "%sudo ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers && \
    mkdir -p /home/${USER} && \
    chown -R ${USER}:${USER} /home/${USER}
# Set the user to USER (fprime-user)
USER ${USER}
WORKDIR /home/${USER}
