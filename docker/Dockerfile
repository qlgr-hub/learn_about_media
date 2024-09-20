ARG CUDA_VERSION=12.2.2
FROM nvcr.io/nvidia/cuda:${CUDA_VERSION}-devel-ubuntu22.04
# Required to build Ubuntu 20.04 without user prompts with DLFW container
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Shanghai


# Install cudnn
ENV NV_CUDNN_VERSION 8.9.6.50
ENV NV_CUDNN_PACKAGE_NAME "libcudnn8"
ENV CUDA_VERSION_MAJOR_MINOR=12.2
ENV NV_CUDNN_PACKAGE "libcudnn8=$NV_CUDNN_VERSION-1+cuda${CUDA_VERSION_MAJOR_MINOR}"
ENV NV_CUDNN_PACKAGE_DEV "libcudnn8-dev=$NV_CUDNN_VERSION-1+cuda${CUDA_VERSION_MAJOR_MINOR}"
ENV TRT_VERSION 10.0.1.6
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get install -y --no-install-recommends \
    ${NV_CUDNN_PACKAGE} \
    ${NV_CUDNN_PACKAGE_DEV} \
    && apt-mark hold ${NV_CUDNN_PACKAGE_NAME} \
    && rm -rf /var/lib/apt/lists/*


# Update CUDA signing key
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/3bf863cc.pub


# Install requried libraries
RUN apt-get update && apt-get install -y software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get update && apt-get install -y --no-install-recommends \
    libcurl4-openssl-dev \
    wget \
    git \
    pkg-config \
    sudo \
    ssh \
    libssl-dev \
    pbzip2 \
    pv \
    bzip2 \
    unzip \
    devscripts \
    lintian \
    fakeroot \
    dh-make \
    build-essential \
    net-tools \
    openssh-server \
    aria2 \
    vim \
    make \
    golang \
    nodejs \
    default-jre \
    graphviz \
    clinfo \
    pocl-opencl-icd \
    doxygen


# Install ffmpeg development related packages
RUN apt install -y --no-install-recommends \
                   autoconf automake git-core libass-dev libfreetype6-dev libsdl2-dev libtool libva-dev libvdpau-dev libvorbis-dev \
                   libxcb1-dev libxcb-shm0-dev libxcb-xfixes0-dev texinfo libasound2-dev libgl1-mesa-dev libglew-dev libglm-dev \
                   nasm libx264-dev libx265-dev libvpx-dev libfdk-aac-dev libmp3lame-dev libopus-dev
                                

# Add default non-root sudoer user and start ssh service
RUN groupadd -r -g 1000 george && useradd -rm -d /home/george -s /bin/bash -g george -G sudo -u 1000 george
RUN echo 'george:123456' | chpasswd && echo "george ALL=(ALL) ALL" >> /etc/sudoers
RUN echo "PermitUserEnvironment yes" >> /etc/ssh/sshd_config && service ssh start


# Install python3
RUN apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-dev \
    python3-wheel &&\
    cd /usr/local/bin &&\
    ln -s /usr/bin/python3 python && \
    ln -s /usr/bin/pip3 pip


# my own proxy settings
# ENV http_proxy=http://192.168.3.81:7890
# ENV https_proxy=http://192.168.3.81:7890

USER root


# Install cmake
RUN aria2c https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh && \
    bash cmake-3.30.0-linux-x86_64.sh --skip-license --prefix=/usr/local


# Install PyPI packages
RUN pip3 install --upgrade pip
RUN pip3 install setuptools>=41.0.0


ENV PATH="$PATH:/workspace/opensource/depot_tools"

# Clean up
RUN rm -rf /tmp/*
RUN apt autopurge -y

EXPOSE 22

WORKDIR /home/george/
CMD ["/usr/sbin/sshd" "-D"]
