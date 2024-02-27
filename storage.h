#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "DynamicSongArray.h"
#include "song.h" // Include the header for the Song class


class Storage {
private:
    DynamicSongArray generalSongLibrary; //This is where songs go that have no playlist -2/24 Kian
    std::unordered_map<int, DynamicSongArray> musicLibrary; 
    void printNotFound(std::string str) const;
    void printSuccessfulOp(std::string str) const;
public:
    Storage(); // Default constructor
    bool addSong(const Song& song); // Adds a song to the library
    bool removeSong(int songID); // Removes a song by ID
    void displayAllSongs() const; // Displays all songs in the library
    bool songExists(int songID) const; // Checks if a song exists by ID
    std::vector<std::string> parseInput(const std::string& input);
    void addPlaylist(int playlistID, const std::string& playlistName); // Adds a new playlist
    bool addSongToPlaylist(int songID, int playlistID);
    void displaySongsInPlaylist(int playlistID) const;
    void removeSongFromPlaylist(int songId,int playlistID);
    void copyPlaylist(int playlistId, int newPlaylistId, const std::string& newPlaylistName);
    void renamePlaylist(int playlistId, const std::string& newPlaylistName);
    void removePlaylist(int playlistId);
    void seeSong(int songId);
    // Additional functions as needed
};

#endif // STORAGE_H