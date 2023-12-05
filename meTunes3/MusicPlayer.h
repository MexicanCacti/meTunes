/*
https://learn.microsoft.com/en-us/windows/win32/multimedia/mci-reference
*/
#pragma once
#pragma comment(lib, "Winmm.lib")

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //allows the use of filesystem to get directory path
#include <experimental/filesystem> 
#include "Playlist.h"
#include "msTimer.h"
#include <windows.h>
#include <string>
#include <iomanip> // used for console formatting
namespace fs = std::experimental::filesystem;
using namespace std;

void convertTime(int, ostream&);  // converts ms to a H :: M :: S format, pass in milliseconds/seconds, true = in ms, false = in seconds

int displayPlaylists(vector<Playlist>&, ostream&); // list of all playlists, iostream

int displaySongs(Playlist&, ostream&); // playlist, iostream

void playSong(Playlist&, const string&, int&, ostream&); // playlist, song name, iostream

void playPlaylist(Playlist&, int&, ostream&); // playlist to play, iostream

void convertTime(int time, ostream& out) {
  int seconds = 0;
  int minutes = 0;
  int hours = 0;
  seconds = (time / 1000) % 60;
  minutes = (time / (1000 * 60)) % 60;
  hours = (time / (1000 * 60 * 60)) % 24;

  out << setfill('0') << setw(2) << hours << " :: " << setw(2) << minutes << " :: " << setw(2) << seconds << endl;
}

int displayPlaylists(vector<Playlist>& Playlists, ostream& out) {
  string choice;
  int num;

  cout << endl;
  for (int i = 0; i < Playlists.size(); i++) {
    out << i << ") " << Playlists[i].getFolderName() << endl;
  }

  while (true) {
    out << "\nSelect Folder by Name or by Index: ";
    getline(cin, choice);
    out << endl;

    if (choice == "q" || choice == "Q") return -1;
    num = atoi(choice.c_str());
    if (num <= Playlists.size() - 1 && num >= 0) { // user inputted a valid choice
      return num;
    }
    for (int i = 0; i < Playlists.size(); i++) {
      if (Playlists[i].getFolderName() == choice) return i;
    }
    out << " Invalid input.";
  }
}

int displaySongs(Playlist& Playlist, ostream& out) {
  string choice;
  int num;
  Playlist.printSongs(out);

  while (true) {
    out << "\n Input song by name or by index: ";
    getline(cin, choice);
    out << endl;

    if (choice == "q" || choice == "Q") return -1;
    num = atoi(choice.c_str());
    if (num <= Playlist.Songs() - 1 && num >= 0) { // user inputted a valid choice
      return num;
    }
    for (int i = 0; i < Playlist.Songs(); i++) {
      if (Playlist.getSongName(choice) == choice) return i;
    }
    out << " Invalid input.";
  }
}

void playSong(Playlist& playlist, const string& song, int& volume, ostream& out) {
  string command;
  string message;
  string songLocation = ("open \"" + fs::current_path().string() + "\\" + playlist.getFolderName() + "\\" + playlist.getSongName(song) + ".mp3" + "\" type mpegvideo alias song"); // for the mcisendstring function, song can now be referenced using the alias song

  LPSTR length = new char[100];
  int trackTime = 0;
  int currentTime = 0;
  Timer timer;

  mciSendStringA(songLocation.c_str(), nullptr, 0, 0);
  mciSendStringA("play song", nullptr, 0, 0); //play song is the command to play the alias "song" 
  message = "setaudio song volume to " + to_string(volume);
  mciSendStringA(message.c_str(), nullptr, 0, 0);
  out << "\nNow playing selected song " << endl;
  out << "\nAVAILABLE COMMANDS" << endl;
  out << "[P] - Pause Song" << endl;
  out << "[V] - Change Volume (" << volume << ")" << endl;
  out << "[Q] - Stop Song & Return Back to Song/Playlist selection" << endl;
  out << "Track Length: ";
  mciSendStringA("status song length", length, 100, 0); // gives track time in MS
  trackTime = atoi(length);
  convertTime(trackTime, out);
  timer.Start();
  getline(cin, command);
  while ((command != "Q" || command != "q") && timer.Convert() < trackTime) {
    if (command == "P" || command == "p") {
      cout << "Current Track Time: ";
      timer.Pause();
      // then here pause the timer and start after resume song
      convertTime(timer.Convert(), out);
      mciSendStringA("pause song", nullptr, 0, 0);
      cout << "Press any button to resume song...\n";
      getline(cin, command);
      timer.Resume();
      mciSendStringA("resume song", nullptr, 0, 0);
    }
    else if (command == "V" || command == "v") {
      cout << "Change volume to: ";
      getline(cin, command);
      volume = atoi(command.c_str());
      if (volume > 1000) {
        volume = 1000;
      }
      cout << "Volume set to " << volume << "." << endl;
      message = "setaudio song volume to " + to_string(volume);
      mciSendStringA(message.c_str(), nullptr, 0, 0);
    }
    else if (command == "Q" || command == "q") {
      break;
    }
    getline(cin, command);
  }
  cout << endl;
  mciSendStringA("close song", 0, 0, 0);
}

void playPlaylist(Playlist& playlist, int& volume, ostream& out) {
  string message;
  string command;
  string songLocation;
  LPSTR length = new char[100];
  int trackTime;
  Timer timer;

  out << "\nNow playing playlist " << playlist.getFolderName() << endl;
  playlist.printSongs(out);
  for (int song = 0; song < playlist.Songs(); song++) {
    out << "\nPlaying Song: " << playlist.getSongName(song) << endl;
    out << "\nAVAILABLE COMMANDS" << endl;
    out << "[P] - Pause Current Song" << endl;
    out << "[S] - Skip Current Song" << endl;
    out << "[V] - Change Volume (" << volume << ")" << endl;
    out << "[Q] - Stop Playlist & Return Back to Song/Playlist selection" << endl;
    songLocation = ("open \"" + fs::current_path().string() + "\\" + playlist.getFolderName() + "\\" + playlist.getSongName(song) + ".mp3" + "\" type mpegvideo alias song"); // for the mcisendstring function, song can now be referenced using the alias song
    mciSendStringA(songLocation.c_str(), nullptr, 0, 0);
    mciSendStringA("play song", nullptr, 0, 0); //play song is the command to play the alias "song"
    message = "setaudio song volume to " + to_string(volume);
    mciSendStringA(message.c_str(), nullptr, 0, 0);
    out << "Track Length: ";
    mciSendStringA("status song length", length, 100, 0); // gives track time in MS
    trackTime = atoi(length);
    convertTime(trackTime, out);
    timer.Start();
    getline(cin, command);
    while ((command != "Q" || command != "q") && timer.Convert() < trackTime) {
      if (command == "P" || command == "p") {
        out << "Current Track Length: ";
        timer.Pause();
        // then here pause the timer and start after resume song
        convertTime(timer.Convert(), out);
        mciSendStringA("pause song", nullptr, 0, 0);
        cout << "Press any button to resume song...\n";
        getline(cin, command);
        timer.Resume();
        mciSendStringA("resume song", nullptr, 0, 0);
      }
      else if (command == "S" || command == "s") {
        break;
      }
      else if (command == "V" || command == "v") {
        out << "Change volume to: ";
        getline(cin, command);
        volume = atoi(command.c_str());
        if (volume > 1000) {
          volume = 1000;
        }
        out << "Volume set to " << volume << "." << endl;
        message = "setaudio song volume to " + to_string(volume);
        mciSendStringA(message.c_str(), nullptr, 0, 0);
      }
      else if (command == "Q" || command == "q") {
        out << endl;
        mciSendStringA("close song", 0, 0, 0);
        return;
      }
      getline(cin, command);
    }
    mciSendStringA("close song", 0, 0, 0);
  }
}