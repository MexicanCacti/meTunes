/*https://en.cppreference.com/w/cpp/filesystem*/
//************ DOCUMENTATION FOR THE FILESYSTEM LIBRARY ***********

#pragma once
#include"MusicPlayer.h"
#include <string>
#include <vector>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //allows the use of filesystem to get directory path
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;

void getFolders(vector<Playlist>&);

void getSongs(const string&, vector<string>&);


void getFolders(std::vector<Playlist>& Playlists) {
  string path = fs::current_path().string(); // want to look in project directory
  vector<string>folderNames;  // list of all folders in project directory
  vector<string>songList; // list of all songs inside a folder
  
  for (const auto& file : fs::directory_iterator(path)) {
    if(fs::is_regular_file(file)) continue; // want to grab all folder file paths... dont care about other files
    folderNames.push_back(file.path().string().substr(path.length() + 1));
  }
  for (const auto& folder : folderNames) {
    getSongs(folder, songList);
    if(songList.empty()) continue;
    Playlists.push_back(Playlist(folder, songList));
    songList.clear();
  }
}

void getSongs(const string& folder, vector<string>& songList) {
  vector<fs::path> songPaths; // vector of every file contained in folder we are exploring.
  const char* const file_ext_mp3 = ".mp3"; // file extension of music files looking for
  string path = fs::current_path().string() + "\\" + folder + "\\"; // path of folder to look in
  string temp;
  
  for (const auto& entry : fs::directory_iterator(path)) {
    if (fs::is_regular_file(entry)) {
      songPaths.push_back(entry);
    }
  }
  
  for (auto& song : songPaths) {
    temp = song.string();
    if (temp.substr(temp.length() - 4) == file_ext_mp3) { // checks to see if file has file_ext we are looking for (final 4 characters)
      temp.erase(temp.find(path), path.length()); // gets rid of the path directory to single out the song name
      temp.erase(temp.find(file_ext_mp3));  // gets rid of file_ext at end
      songList.push_back(temp);
    }
  }
}