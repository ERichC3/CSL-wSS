#include "DynamicSongArray.h"
#include <algorithm> // For std::copy
#include <stdexcept> // For std::out_of_range
#include <string>
#include <iostream>

using namespace std;

//All this class should do is act as the second has map. 
//Basically it should be able to add songs, removesongs, return 

DynamicSongArray::DynamicSongArray() : songs(nullptr), capacity(0), numSongs(0) {

}

DynamicSongArray::~DynamicSongArray() {
    delete[] songs;
}

DynamicSongArray::DynamicSongArray(const DynamicSongArray& other) : playListName(other.playListName), capacity(other.capacity), numSongs(other.numSongs) {
    songs = new Song[capacity];

    copy(other.songs, other.songs + numSongs, songs);
}

DynamicSongArray& DynamicSongArray::operator=(const DynamicSongArray& other) {
    if (this != &other) {
        playListName = other.playListName;
        capacity = other.capacity;
        numSongs = other.numSongs;
        
        delete[] songs;

        songs = new Song[capacity];
        copy(other.songs, other.songs + numSongs, songs);
    }

    return *this;
}

void DynamicSongArray::resize() {
    int newCapacity = capacity == 0 ? 1 : capacity * 2;
    Song* newSongs = new Song[newCapacity];

    copy(songs, songs + numSongs, newSongs);

    delete[] songs;

    songs = newSongs;
    capacity = newCapacity;
}

void DynamicSongArray::addSong(const Song& song) {
    if(numSongs==capacity) {
        resize();
    }

    songs[numSongs++]=song;
    //debug text: cout<<"Sucessful Add"<<endl;
}

void DynamicSongArray::removeSong(int songID) {
    cout << "removing song " << songID << endl;

    for (int i = 0; i < numSongs; ++i) {
        if (songs[i].getSongID() == songID) {
            //song ID,, TITLE by ARTIST removed
            cout << "song " << songID << ", " << songs[i].getTitle() << " by " << songs[i].getArtist() << ", removed" << endl;
            for (int j = i; j < numSongs - 1; ++j) {
                songs[j] = songs[j + 1];
            }
            --numSongs;
            return;
        }
    }
}

int DynamicSongArray::getSize() const {
    return numSongs;
}

Song DynamicSongArray::getSong(int index) const {
    if (index < 0 ) { //think about this more || index > numSongs
        throw out_of_range("Index out of range. from getSong() in DynamicSongArray.cpp");
    }

    return songs[index];
}

int DynamicSongArray::getIndex(int songID) const {
    for (int i = 0; i < numSongs; ++i) {
        if (songs[i].getSongID() == songID) {
            //cout << "oh we got an index" << endl;
            return i;
        }
    }
    //cout << "getindex failed somehow lmao" << endl;
    return -1;

}

bool DynamicSongArray::songExists(int songID) const {
    //cout << "song does exist maybe" << endl;
    for (int i = 0; i < numSongs; ++i) {
        if (songs[i].getSongID() == songID) {
            return true;
        }
    }
    return false;
};


Song* DynamicSongArray::findSongById(int songId) {
    Song* songsarr=songs;

    for (size_t i = 0; i < numSongs; ++i) {
        if (songsarr[i].getSongID() == songId) {
            return &songsarr[i];
        }
    }
    return nullptr; //Song not found
};

// Setter method for playlist name
void DynamicSongArray::setPlaylistName(std::string str) {
    playListName = str;
}

// Getter method for playlist name
std::string DynamicSongArray::getName() const {
    return playListName;
}