CC=gcc
CXX=g++

ROOTDIR = $(shell git rev-parse --show-toplevel)
CS3081DIR = $(ROOTDIR)/external/install
-include $(ROOTDIR)/external/etc/env

all: MinGfx

MinGfx: build
	cd build; cmake --build . --target install

build: src
	mkdir -p build
	cd build; CC=$(CC) CXX=$(CXX) cmake -DAUTOBUILD_DEPENDENCIES=ON -DAUTOBUILD_EXECUTE_NOW=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$(CS3081DIR) ../src

src:
	git clone https://github.com/ivlab/MinGfx.git src
	cd src; git checkout csci3081

update-src: src
	cd src; git pull

update: update-src MinGfx

clean:
	rm -rf build

clobber: clean
	rm -rf src

