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
    // Adds to generalSongLibrary
    if (generalSongLibrary.songExists(song.getSongID())) {
        //cout << "Song with ID " << song.getSongID() << " already exists! It cannot be added." << endl;
        int thisIndex = generalSongLibrary.getIndex(song.getSongID());
        cout << "song id " << song.getSongID() << " is already used for " << generalSongLibrary.getSong(thisIndex).getTitle() << " by "
        << generalSongLibrary.getSong(thisIndex).getArtist() << endl;
        //song id ID is already used for TITLE by ARTIST
        return false;
    }
    //debug line: cout << "Adding song "<< endl;
    generalSongLibrary.addSong(song); // Adds the song to the general library
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

    if (!found) {
        cout << "song  " << songID << " not found." << endl;
    }

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
    if (musicLibrary.count(playlistID) > 0){
        cout << "Playlist ID " << playlistID << " already exists!" << endl;
        return; // ID found, no need to continue
    }
    // Create a new, empty DynamicSongArray for this playlist
    DynamicSongArray newPlaylist;
    // Set the playlist name
    newPlaylist.setPlaylistName(playlistName);
    // Add the new playlist to the musicLibrary using the playlist ID as the key
    musicLibrary[playlistID] = newPlaylist;
    //debug line: printSuccessfulOp("Playlist addition");
    cout << "new playlist " << playlistID << " called " << playlistName << endl;
}

bool Storage::addSongToPlaylist(int songID, int playlistID) {
    cout << "add song " << songID << " to playlist " << playlistID << endl;
    // Check if the song exists in the general library
    if (!generalSongLibrary.songExists(songID)) {
        cout << "song " << songID << " does not exist" << endl;
        //debug line: printNotFound("SongID");
        return false;
    }
     //cout<<"here2"<<endl;
    // Check if the playlist exists
    if (musicLibrary.find(playlistID) == musicLibrary.end()) {
        cout << "playlist " << playlistID << " does not exist" << endl;
        //debug line: printNotFound("PlaylistID");
        return false;
    }
    if(musicLibrary[playlistID].songExists(songID)) {
        cout << "song " << songID << " is already in playlist " << playlistID << endl;
        return false;
    }
    //cout<<"here3"<<endl;
    // Add song to the correct playlist
    musicLibrary[playlistID].addSong(*generalSongLibrary.findSongById(songID));
    cout << "song " << songID << " successfully added to playlist " << playlistID << endl;
    //debug line: printSuccessfulOp("Song addition to playlist");
    return true;
}

void Storage::displaySongsInPlaylist(int playlistID) const {
    // Check if the playlist exists
    auto playlist = musicLibrary.find(playlistID);
    if (playlist == musicLibrary.end()) {
        cout << "playlist " << playlistID << " does not exist" << endl;
        //debug line: printNotFound("PlaylistID");
        return;
    }

    // Check if the playlist is empty
    if (playlist->second.getSize() == 0) {
        cout << "Playlist with ID " << playlistID << " is empty." << endl;
        return;
    }

    // Display all songs in the playlist
    cout << "Songs in playlist " << playlistID << " "  << endl; //<< musicLibrary[playlistID].getName()
    for (int i = 0; i < playlist->second.getSize(); ++i) {
        const Song& song = playlist->second.getSong(i);
        
        cout << "song " << song.getSongID() << " " << song.getTitle() << " by " << song.getArtist() << endl;
        
    }
}

void Storage::copyPlaylist(int playlistId, int newPlaylistId, const std::string& newPlaylistName) {
    if (musicLibrary.count(playlistId)) {
        DynamicSongArray copiedPlaylist(musicLibrary[playlistId]); // Using copy constructor
        musicLibrary[newPlaylistId] = copiedPlaylist;
        cout << "playlist " << playlistId << " successfully copied to playlist " << newPlaylistId << " " << newPlaylistName << endl;
        //debug line: std::cout << "Playlist copied successfully to new playlist with ID " << newPlaylistId << std::endl;
    } 
    
    else {
        std::cout << "Playlist " << playlistId << " not found." << std::endl;
    }
};

void Storage::removeSongFromPlaylist(int songId, int playlistId) {
    // Check if the playlist exist
    cout << "remove song " << songId << " from playlist " << playlistId << endl;
    //debug text: cout<<musicLibrary.count(playlistId)<<endl;
    if (musicLibrary.count(playlistId)) {
        // If playlist exists, remove the song from it
        if(musicLibrary[playlistId].songExists(songId)){
            //check if song exists
            if(generalSongLibrary.songExists(songId)) {
                musicLibrary[playlistId].removeSong(songId);
            cout << "song " << songId << " successully dropped from playlist " << playlistId << endl;
            //debug line: printSuccessfulOp("Song removal from playlist");
            }
            else {
                cout << "song " << songId << " does not exist" << endl;
            }
            
        } else {
            cout << "song " << songId << " is not in playlist " << playlistId << endl;
            //debug line: printNotFound("PlaylistID");
        }
        
    } 
    
    else {
        // If playlist doesn't exist, print an error message
        printNotFound("PlaylistID");
    }
}

void Storage::removePlaylist(int playlistId) {
    if (musicLibrary.count(playlistId)) {
        musicLibrary.erase(playlistId);
        std::cout << "Playlist " << playlistId << " successfully deleted" << std::endl;
    } 
    
    else {
        std::cout << "Playlist " << playlistId << " not found." << std::endl;
    }
}

void Storage::renamePlaylist(int playlistId, const std::string& newPlaylistName) {
    if (musicLibrary.count(playlistId)) {
        musicLibrary[playlistId].setPlaylistName(newPlaylistName);
        std::cout << "Playlist " << playlistId << " name successfully changed to " << newPlaylistName << std::endl;
    } 
    
    else {
        std::cout << "Playlist " << playlistId << " not found." << std::endl;
    }
}

void Storage::seeSong(int songId) { 
    cout << "song " << songId << endl;
    /*idea:
    get song index by using songID
    use gotten index to getSong with index instead of songID
    get proper title with the correct song gotten from array*/
    //cout << "we entered see song though" << endl;
    int thisIndex = generalSongLibrary.getIndex(songId);
    if (generalSongLibrary.songExists(songId)) {
        cout << "song " << songId << " " << generalSongLibrary.getSong(thisIndex).getTitle() << " by " 
        << generalSongLibrary.getSong(thisIndex).getArtist() << endl;
    } 
    else {cout << "song " << songId << " does not exist" << endl;}
    
    //cout << "we exited though..." << endl;
}



void Storage::printNotFound(std::string str) const {
    cout << "Your " << str << " was not found!\nThus your operation failed." << endl;
}

void Storage::printSuccessfulOp(std::string str) const {
    cout<<"Your "<<str<<" operation was a success!"<<endl;
}

