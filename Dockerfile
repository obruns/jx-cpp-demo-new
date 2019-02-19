FROM debian:buster

MAINTAINER Oliver Bruns <obruns@gmail.com>

RUN apt update && \
    apt install --assume-yes \
        build-essential \
        clang \
        clang-format \
        clang-tidy \
        cmake \
        libboost-all-dev \
        ninja-build
