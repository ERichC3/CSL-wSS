#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <regex>
#include <map>
#include <vector>
#include "song.h"
#include "storage.h"

using namespace std;

vector<string> parseInput(const string& input) {
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
}

enum Command {
    CMD_SONG,
    CMD_REMOVE,
    CMD_PLAYLIST,
    CMD_ADD,
    CMD_DROP,
    CMD_SEESONG,
    CMD_SEEPLAYLIST,
    CMD_QUIT,
    CMD_DELETEPLAYLIST,
    CMD_COPYPLAYLIST,
    CMD_RENAMEPLAYLIST,
    CMD_UNKNOWN // Always a good idea to have an unknown/fallback command
};

map<string, Command> commandMap = {
    {"song", CMD_SONG},
    {"remove", CMD_REMOVE},
    {"playlist", CMD_PLAYLIST},
    {"add", CMD_ADD},
    {"drop", CMD_DROP},
    {"seesong", CMD_SEESONG},
    {"seeplaylist", CMD_SEEPLAYLIST},
    {"quit", CMD_QUIT},
    {"deleteplaylist", CMD_DELETEPLAYLIST},
    {"copyplaylist", CMD_COPYPLAYLIST},
    {"renameplaylist", CMD_RENAMEPLAYLIST}
};

void printInvalidSize(int size){
    cout << "Invalid input:"<<size<< " is Insufficent amount of arguments for this command!" << endl;
};

bool argTesting(int size,std::vector<string> vec){
    if(vec.size()!=size)printInvalidSize(vec.size());
    return vec.size()==size;  
    //goto restartLoop;
};

int parseID(string strId){
    int id=-1234;
    try {
        int id = stoi(strId);
        return id;
    } catch (const invalid_argument& e) {
       cout << "Invalid input: " << e.what() << endl;
       cout << "Invalid Input: Song Id cannot be " << strId<< endl;
    }
    return id;
}

Storage store;

void Input() { 
  string text;
  cout << "Enter Command: ";
  getline(cin, text);
  
  int flag=1;
  vector<string> stringList=/*store1.*/parseInput(text);
  if(stringList.size()>5){
     cout << "Invalid input: Excess arguments" << endl;
     Input();
  }
  Command cmd = commandMap.count(stringList[0]) ? commandMap[stringList[0]] : CMD_UNKNOWN;

    //This is where we add songs. We can have white space in song and artisit name but then they will be in """"- Kian
   switch (cmd) {
        case CMD_SONG:
            try {
                if(!argTesting(5,stringList))break;
                int time = stoi(stringList[3]);
                flag = 0;
                int id = stoi(stringList[1]); // This should get the songID -Kian
                Song mySong(id, stringList[2], time, stringList[4]);
                store.addSong(mySong);//Has built in duplicate ID checking -2/25/24 Kian
                //Need to add songs to playlist once adding playlists is done.-2/25/24 Kian 
            } catch (const invalid_argument& e) {
                cout << "Invalid input: " << e.what() << endl;
                if (flag == 0) cout << "Invalid Input: SongId cannot be " << stringList[1] << endl;
                else cout << "Invalid Input: time cannot be " << stringList[3] << endl;
            }
            break;
        case CMD_REMOVE://Before I can verify this, I need to get add to playlist working -2/26 Kian
            if(!argTesting(2,stringList))break;
            else if(parseID(stringList[1])==-1234)break;
            else store.removeSong(parseID(stringList[1]));
            break;
        case CMD_PLAYLIST://Working on this-Kian 2/24
            if(!argTesting(3,stringList))break;
            else if(parseID(stringList[1])==-1234)break;
            else store.addPlaylist(parseID(stringList[1]),stringList[2]);
            break;
        case CMD_ADD:
            if(argTesting(3,stringList)){
                int id1=parseID(stringList[1]);
                int id2=parseID(stringList[2]);
                if(id1==-1234||id2==-1234)break;
                else store.addSongToPlaylist(id1,id2);
                break;
            }
            break;
        case CMD_DROP:
            if(argTesting(3,stringList)){
                int id1=parseID(stringList[1]);
                int id2=parseID(stringList[2]);
                if(id1==-1234||id2==-1234)break;  
                else store.removeSongFromPlaylist(id1,id2);
                break;
            }
            break;
        case CMD_SEESONG:
            if(!argTesting(2,stringList))break;
            else if(parseID(stringList[1])==-1234)break;
            else store.seeSong(parseID(stringList[1]));
            break;
        case CMD_SEEPLAYLIST:
            if(!argTesting(2,stringList))break;
            else if(parseID(stringList[1])==-1234)break;
            else store.displaySongsInPlaylist(parseID(stringList[1]));
            break;
        case CMD_DELETEPLAYLIST:
            if(!argTesting(2,stringList))break;
            else if(parseID(stringList[1])==-1234)break;
            else store.removePlaylist(parseID(stringList[1]));
            break;
        case CMD_COPYPLAYLIST:
            if(argTesting(4,stringList)){
                int id1=parseID(stringList[1]);
                int id2=parseID(stringList[2]);
                if(id1==-1234||id2==-1234)break;  
                else store.copyPlaylist(id1,id2,stringList[3]);
                break;
            }
           // cout << "Copying playlist " << stringList[1] << " to " << stringList[2] << endl;
            break;
        case CMD_RENAMEPLAYLIST:
            if(!argTesting(3,stringList))break;
            else if(parseID(stringList[1])==-1234)break;
            else store.renamePlaylist(parseID(stringList[1]),stringList[2]);
            break;
           // cout << "Renaming playlist " << stringList[1] << " to " << stringList[2] << endl;
        case CMD_QUIT:
            exit(0);
            break;
        default:
            cout << "Command not recognized. Please try again." << endl;
            break;
    }
    restartLoop:
            Input();
}
    
int main() {
    Input();
}