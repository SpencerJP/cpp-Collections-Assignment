
cpp_draughts:
#runs cmake on the program
	cmake -H. -Bbuild
	cmake --build build -- -j3
	
all:
#runs cmake on the program
	cmake -H. -Bbuild
	cmake --build build -- -j3
