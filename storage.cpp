#include "storage.h"
#include <iostream>
#include "DynamicSongArray.h"

#include <vector>   // For std::vector
#include <string>   // For std::string
#include <sstream> 
using namespace std;


Storage::Storage() {
    // Constructor body can be empty if no initialization is required other than that provided by the member initializers
}

bool Storage::addSong(const Song& song) {
    // Add to generalSongLibrary
    if (generalSongLibrary.songExists(song.getSongID())) {
        cout << "Song with ID " << song.getSongID() << " already exists! It cannot be added." << endl;
        return false;
    }
    
    generalSongLibrary.addSong(song); // Add the song to the general library
    return true;
}

bool Storage::removeSong(int songID) {
    bool found = false;

    if (generalSongLibrary.songExists(songID)) {
        generalSongLibrary.removeSong(songID);
        found = true;
    }

    for (auto& playlist : musicLibrary) {
        if (playlist.second.songExists(songID)) {
            playlist.second.removeSong(songID);
            found = true;
        }
    }

    if (!found)cout << "Song with ID " << songID << " not found." << endl;
    return found;
}

void Storage::displayAllSongs() const {
    if (generalSongLibrary.getSize() == 0) {
        std::cout << "No songs in the library." << std::endl;
        return;
    }

    for (int i = 0; i < generalSongLibrary.getSize(); ++i) {
        const Song& song = generalSongLibrary.getSong(i);
        song.displaySongInfo(); // Assuming Song class has this method to display its details
        std::cout << "-------------------" << std::endl; // Separator for readability
    }
}

bool Storage::songExists(int songID) const {
    return generalSongLibrary.songExists(songID);
}

void Storage::addPlaylist(int playlistID, const std::string& playlistName) {
    // Check if the playlist ID already exists to avoid overwriting
    if (musicLibrary.find(playlistID) != musicLibrary.end()) {
        cout << "Playlist ID " << playlistID << " already exists!" << endl;
        return; // ID found, no need to continue
    }
    
    // Create a new, empty DynamicSongArray for this playlist
    DynamicSongArray newPlaylist;

    // Set the playlist name
    newPlaylist.setPlaylistName(playlistName);

    // Add the new playlist to the musicLibrary using the playlist ID as the key
    musicLibrary[playlistID] = newPlaylist;

    printSuccessfulOp("Playlist addition");
}

bool Storage::addSongToPlaylist(int songID, int playlistID) {
    // Check if the song exists in the general library
    if (!generalSongLibrary.songExists(songID)) {
        printNotFound("SongID");
        return false;
    }

    // Check if the playlist exists
    if (musicLibrary.find(playlistID) == musicLibrary.end()) {
        printNotFound("PlaylistID");
        return false;
    }

    // Add song to the correct playlist
    musicLibrary[playlistID].addSong(generalSongLibrary.getSong(songID));
    printSuccessfulOp("Song addition to playlist");
    return true;
}

void Storage::displaySongsInPlaylist(int playlistID) const {
    // Check if the playlist exists
    auto playlist = musicLibrary.find(playlistID);
    if (playlist == musicLibrary.end()) {
        printNotFound("PlaylistID");
        return;
    }

    // Check if the playlist is empty
    if (playlist->second.getSize() == 0) {
        cout << "Playlist with ID " << playlistID << " is empty." << endl;
        return;
    }

    // Display all songs in the playlist
    cout << "Songs in playlist with ID " << playlistID << ":" << endl;
    for (int i = 0; i < playlist->second.getSize(); ++i) {
        const Song& song = playlist->second.getSong(i);
        cout << "ID: " << song.getSongID() << ", Title: " << song.getTitle()
             << ", Artist: " << song.getArtist() << ", Duration: " << song.getDuration() << endl;
    }
}

void Storage::printNotFound(std::string str) const {
    cout << "Your " << str << " was not found!\nThus your operation failed." << endl;
}

void Storage::printSuccessfulOp(std::string str) const {
    cout<<"Your "<<str<<" operation was a success!"<<endl;
}

/*vector<string> parseInput(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        if (token.front() == '"') { // Start of quoted text
            string quotedToken = token;
            if (token.back() != '"') { // Handle case where quoted text is more than one word
                while (ss >> token) {
                    quotedToken += " " + token;
                    if (token.back() == '"') break;
                }
            }
            // Remove the quotes
            quotedToken = quotedToken.substr(1, quotedToken.size() - 2);
            tokens.push_back(quotedToken);
        } else {
            tokens.push_back(token);
        }
    }
    return tokens;
}*/