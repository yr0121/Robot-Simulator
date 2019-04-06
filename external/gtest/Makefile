CC=gcc
CXX=g++

ROOTDIR = $(shell git rev-parse --show-toplevel)
CS3081DIR = $(ROOTDIR)/external/install
-include $(ROOTDIR)/external/etc/env

all: gtest

gtest: build
	cd build; cmake --build . --target install

build: src
	mkdir -p build
	cd build; CC=$(CC) CXX=$(CXX) cmake ../src -DCMAKE_INSTALL_PREFIX=$(CS3081DIR)

src:
	git clone https://github.com/google/googletest.git src

clean:
	rm -rf build

clobber: clean
	rm -rf src
