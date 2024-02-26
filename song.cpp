#include <iostream>
#include <string>
#include <sstream> 
#include "song.h"

using namespace std;

// Default constructor
Song::Song() : songid(0), artist("Unknown"), duration("0:00"), title("Untitled") {
    //cout << "New song created with default values." << endl;
}

// Parameterized constructor with output statement
Song::Song(int id, string artistName, int songDurationSeconds, string songTitle)
: songid(id), artist(artistName), title(songTitle) {
    // Convert seconds to minutes:seconds format and assign to duration
    int minutes = songDurationSeconds / 60;
    int seconds = songDurationSeconds % 60;
    
    stringstream ss;
    ss << minutes << ":"; 
    if(seconds < 10) ss << "0"; // Leading zero for seconds less than 10
    ss << seconds; 
    
    duration = ss.str(); 
    
    cout << "new song " << songid << " " << title << " by " << artist << " " << duration << endl;
}

Song::Song(const Song& source)
: songid(source.songid), artist(source.artist), duration(source.duration), title(source.title) {
    // All member variables are individually copied so 
    // This is essentially what the default copy constructor would do.
}

Song& Song::operator=(const Song& source) {
    if (this != &source) { // Check for self-assignment -2/26 Kian
        songid = source.songid;
        artist = source.artist;
        duration = source.duration;
        title = source.title;
    }
    return *this;
}

Song::~Song() {
}

// Setters
void Song::setSongID(int id) {
    songid = id;
}

void Song::setArtist(string artistName) {
    artist = artistName;
}

void Song::setDuration(int seconds) {
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    
    stringstream ss;
    ss << minutes << ":";
    if(remainingSeconds < 10) ss << "0"; // Leading zero for seconds less than 10
    ss << remainingSeconds; 
    
    duration = ss.str(); // Assign the formatted string to duration
}

void Song::setTitle(string songTitle) {
    title = songTitle;
}

// Getters
int Song::getSongID() const {
    return songid;
}

string Song::getArtist() const {
    return artist;
}

string Song::getDuration() const {
    return duration;
}

string Song::getTitle() const {
    return title;
}

// Method to display song details
void Song::displaySongInfo() const {
    cout << "Song ID: " << songid << endl;
    cout << "Artist: " << artist << endl;
    cout << "Duration: " << duration << " minutes" << endl;
    cout << "Title: " << title << endl;
}