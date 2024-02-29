# FINAL FILE NAME
all: main

# WE EXICUTE
main: main.o song.o storage.o DynamicSongArray.o
	g++ main.o song.o storage.o DynamicSongArray.o -o main

# MAKE DA Os
main.o: main.cpp
	g++ -c main.cpp

song.o: song.cpp song.h
	g++ -c song.cpp

storage.o: storage.cpp storage.h
	g++ -c storage.cpp

DynamicSongArray.o: DynamicSongArray.cpp DynamicSongArray.h
	g++ -c DynamicSongArray.cpp

# SPRING CLEANING
clean:
	rm -f *.o main
