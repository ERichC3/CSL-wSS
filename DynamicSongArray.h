#ifndef DYNAMICSONGARRAY_H
#define DYNAMICSONGARRAY_H

#include "song.h"
#include <string>

class DynamicSongArray {
private:
    std::string playListName;
    Song* songs; // Pointer to the first element of the dynamic array
    int capacity; // Maximum number of elements in the array
    int numSongs; // Current number of elements in the array

    void resize(); // Private method to resize the array when needed

public:
    DynamicSongArray();
    DynamicSongArray(const DynamicSongArray& other); // Deep copy constructor
    ~DynamicSongArray();
    DynamicSongArray& operator=(const DynamicSongArray& other); 
    bool songExists(int songID) const;
    void addSong(const Song& song);
    void removeSong(int songID);
    void setPlaylistName(std::string str);
    std::string getName() const;
    int getSize() const;
    Song getSong(int index) const;
    Song* findSongById(int songId);
};

#endif // DYNAMICSONGARRAY_H