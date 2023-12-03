#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "QuickSort.h"

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

class Playlist {
  private:
    string folderName;
    vector<string>songs;
  public:
    Playlist();
    Playlist(string, vector<string>);
    bool isEmpty();
    int Songs() {return songs.size(); } // # of songs
    string getSongName(const int& index); // if passed in index, checks to see if index in range
    string getSongName(const string&);  // if passed in string, checks to see if string exists, otherwise returns first song in list
    string getFolderName() {return folderName;}
    
    void shuffleSongs();
    void sortSongs();
    void printSongs(ostream&);
    
};

Playlist::Playlist() {
  folderName = "Empty";
}

Playlist::Playlist(string folder, vector<string> song) {
  folderName = folder;
  songs = song;
}

bool Playlist::isEmpty() {
  if(songs.size() == 0) return true;
  return false;
}

string Playlist::getSongName(const int& index) {
  if (index > songs.size()) {
    return songs[0];
  }
  return songs[index];
}

string Playlist::getSongName(const string& songCheck) {
  for (const auto& song : songs) {
    if (song == songCheck) {
      return songCheck;
    }
  }
  return songs[0];  // if we cant find the song in the list of songs by default play first song in list
}

void Playlist::shuffleSongs() {
  //https://www.coderslexicon.com/generating-non-repeating-random-values-in-c/
  vector<int>Random;
  vector<string>shuffledSongs;
  // list of numbers 0 - length of song list
  for (int i = 0; i < songs.size(); i++) {
    Random.push_back(i);
  }
  
  srand(time(0));
  for (int i = 0; i < songs.size(); i++) {
    int randSong1 = (rand() % songs.size() );
    int randSong2 = (rand() % songs.size());
    
    string temp = songs[randSong1];
    songs[randSong1] = songs[randSong2];
    songs[randSong2] = temp;
  }
  
  
  
}

void Playlist::sortSongs() {
  QuickSort(songs, 0, songs.size() - 1);
}


void Playlist::printSongs(ostream& out) {
  for (int i = 0; i < songs.size(); i++) {
    cout << i << ") " << songs[i] << endl;
  }
}
#endif PLAYLIST_H