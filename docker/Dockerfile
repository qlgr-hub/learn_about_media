FROM ubuntu:22.04
ARG DEBIAN_FRONTEND=nointeractive
ENV TZ=Asia/Shanghai


# Change mirror.
# RUN ls /
# RUN sed -i 's/archive\.ubuntu\./mirrors\.cloud\.tencent\./g' /etc/apt/sources.list && \
#     sed -i 's/security\.ubuntu\./mirrors\.cloud\.tencent\./g' /etc/apt/sources.list


# Install basic packages
RUN apt clean && apt update
RUN apt install -y --no-install-recommends \
                   lsb-release build-essential vim wget make gdb sudo git aria2 net-tools binutils strace ninja-build pkg-config \
                   libjpeg-dev libpng-dev libtiff-dev zlib1g-dev libedit-dev libxml2-dev software-properties-common dnsutils doxygen \
                   openssh-server openssl libssl-dev golang nodejs default-jre zip unzip python3 python3-dev python3-pip graphviz

# Install ffmpeg development related packages
RUN apt install -y --no-install-recommends \
                   autoconf automake git-core libass-dev libfreetype6-dev libsdl2-dev libtool libva-dev libvdpau-dev libvorbis-dev \
                   libxcb1-dev libxcb-shm0-dev libxcb-xfixes0-dev texinfo libasound2-dev libgl1-mesa-dev libglew-dev libglm-dev \
                   nasm libx264-dev libx265-dev libvpx-dev libfdk-aac-dev libmp3lame-dev libopus-dev
                                

# Add default non-root sudoer user and start ssh service
RUN groupadd -r -g 1000 qlgr && useradd -rm -d /home/qlgr -s /bin/bash -g qlgr -G sudo -u 1000 qlgr
RUN echo 'qlgr:123456' | chpasswd && echo "qlgr ALL=(ALL) ALL" >> /etc/sudoers
RUN echo "PermitUserEnvironment yes" >> /etc/ssh/sshd_config && service ssh start


ENV http_proxy=http://192.168.3.81:7890
ENV https_proxy=http://192.168.3.81:7890
USER root


# Install llvm
WORKDIR /tmp
RUN aria2c https://apt.llvm.org/llvm.sh  && chmod +x llvm.sh && ./llvm.sh 18
# ENV CC=clang-18
# ENV CXX=clang++-18


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

WORKDIR /home/qlgr/
CMD ["/usr/sbin/sshd" "-D"]
