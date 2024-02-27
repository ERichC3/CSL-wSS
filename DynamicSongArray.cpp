#include "DynamicSongArray.h"
#include <algorithm> // For std::copy
#include <stdexcept> // For std::out_of_range
#include <string>
#include <iostream>

using namespace std;

//All this class should do is act as the second has map. 
//Basically it should be able to add songs, removesongs, return 

DynamicSongArray::DynamicSongArray() : songs(nullptr), capacity(0), numSongs(0) {}

DynamicSongArray::~DynamicSongArray() {
    delete[] songs;
}

DynamicSongArray::DynamicSongArray(const DynamicSongArray& other) : playListName(other.playListName), capacity(other.capacity), numSongs(other.numSongs) {
    songs = new Song[capacity];
    std::copy(other.songs, other.songs + numSongs, songs);
}//He might want this done another way -2/26 Kian

DynamicSongArray& DynamicSongArray::operator=(const DynamicSongArray& other) {
    if (this != &other) {
        playListName = other.playListName;
        capacity = other.capacity;
        numSongs = other.numSongs;
        
        delete[] songs;
        songs = new Song[capacity];
        std::copy(other.songs, other.songs + numSongs, songs);
    }
    return *this;
}//He might want this done another way -2/26 Kian

void DynamicSongArray::resize() {
    int newCapacity = capacity == 0 ? 1 : capacity * 2;
    Song* newSongs = new Song[newCapacity];
    std::copy(songs, songs + numSongs, newSongs);
    delete[] songs;
    songs = newSongs;
    capacity = newCapacity;
}

void DynamicSongArray::addSong(const Song& song) {
    if(numSongs==capacity)resize();
    cout<<"Sucessful Add"<<endl;
    songs[numSongs++]=song;
}

void DynamicSongArray::removeSong(int songID) {
    for (int i = 0; i < numSongs; ++i) {
        if (songs[i].getSongID() == songID) {
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
    if (index < 0 || index > numSongs) {
        throw std::out_of_range("Index out of range. This error is inside getSong() from DynamicSongArray.");
    }
    return songs[index];
}

bool DynamicSongArray::songExists(int songID) const {
    //cout<<"here"<<endl;
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
    return nullptr; // Song not found
};

// Setter method for playlist name
void DynamicSongArray::setPlaylistName(std::string str) {
    playListName = str;
}

// Getter method for playlist name
std::string DynamicSongArray::getName() const {
    return playListName;
}