#!/usr/bin/env bash

set -e
# set -u

# debug build
./configure \
  --prefix="/usr/local" \
  --extra-cflags="-I/usr/local/include" \
  --extra-ldflags="-L/usr/local/lib" \
  --extra-libs="-lpthread -lm" \
  --bindir="/usr/local/bin" \
  --enable-static \
  --enable-gpl \
  --enable-libass \
  --enable-libfdk-aac \
  --enable-libfreetype \
  --enable-libmp3lame \
  --enable-libopus \
  --enable-libvorbis \
  --enable-libvpx \
  --enable-libx264 \
  --enable-libx265 \
  --enable-pic \
  --enable-shared   \
  --enable-nonfree \
  --enable-debug=3 \
  --disable-optimizations \
  --disable-asm \
  --disable-stripping && \

make && \
sudo make install && \
hash -r
