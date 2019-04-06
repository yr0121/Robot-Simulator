all: mingfxlib gtestlib 

mingfxlib:
	cd MinGFX; make

gtestlib:
	cd gtest; make

clean:
	cd MinGFX; make clean
	cd gtest; make clean
	rm -rf install

clobber: clean
	cd MinGFX; make clobber
	cd gtest; make clobber
