# Target to build everything
all: main

# Executable depends on all object files
main: main.o song.o storage.o DynamicSongArray.o
	g++ main.o song.o storage.o DynamicSongArray.o -o main

# Each .cpp file is compiled separately into an .o file
main.o: main.cpp
	g++ -c main.cpp

song.o: song.cpp song.h
	g++ -c song.cpp

storage.o: storage.cpp storage.h
	g++ -c storage.cpp

DynamicSongArray.o: DynamicSongArray.cpp DynamicSongArray.h
	g++ -c DynamicSongArray.cpp

# Clean up intermediate files and the executable
clean:
	rm -f *.o main
