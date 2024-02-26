#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
private:
    int songid;
    std::string artist;
    std::string duration; // Duration in minutes
    std::string title;

public:
    Song(); 
    Song(int id, std::string artistName, int songDurationSeconds, std::string songTitle); 
    Song(const Song& other); // Copy constructor
    Song& operator=(const Song& other); // Copy assignment operator
    ~Song(); 

    // Declare setters
    void setSongID(int id);
    void setArtist(std::string artistName);
    void setDuration(int seconds);
    void setTitle(std::string songTitle);

    // Declare getters
    int getSongID() const;
    std::string getArtist() const;
    std::string getDuration() const;
    std::string getTitle() const;

    // Declare other member functions
    void displaySongInfo() const;
};

#endif // SONG_H