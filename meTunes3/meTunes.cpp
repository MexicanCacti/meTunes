#include "GetFiles.h"
#include "Playlist.h"
#include "MusicPlayer.h"
int main() {
  vector<Playlist>Playlists;
  
  cout << "Looking for folders in: " << fs::current_path() << endl;
  getFolders(Playlists);
  if (Playlists.size() == 0) {
    cout << "No folder containing mp3s found. Please make sure folders with mp3 are located at:\n" << fs::current_path() << endl;
    return 0;
  }
  
  string command; // user input
  int songNumber; // to store song selection from displaySongs
  int playlistIndex; // to store playlist selection from displayPlayLists
  int volume = 100;   // if the user changes volume, want to keep track of changes, by default max volume is 100
  
  playlistIndex = displayPlaylists(Playlists, cout);
  while (true) {
    cout << "Playlist: " << Playlists[playlistIndex].getFolderName() << endl;
    Playlists[playlistIndex].printSongs(cout);
    cout << "\nCOMMANDS" << endl;
    cout << "[0] - Play a Song" << endl;
    cout << "[1] - Play Playlist" << endl;
    cout << "[2] - Shuffle & Play Playlist" << endl;
    cout << "[3] - Sort & Play Playlist" << endl;
    cout << "[4] - Return to Playlist selection" << endl;
    cout << "[5] - Sort Playlist" << endl;
    cout << "[6] - Shuffle Playlist" << endl;
    cout << "[Q] - Quit" << endl;
    getline(cin, command);  // could change to be a switch statement by making command char and putting needed checks
    cout << endl;
    if (command == "0") {
      songNumber = displaySongs(Playlists[playlistIndex], cout);
      playSong(Playlists[playlistIndex], Playlists[playlistIndex].getSongName(songNumber), volume, cout);
    }
    else if (command == "1") {
      playPlaylist(Playlists[playlistIndex], volume, cout);
    }
    else if (command == "2") {
      Playlists[playlistIndex].shuffleSongs();
      playPlaylist(Playlists[playlistIndex], volume, cout);
    }
    else if (command == "3") {
      Playlists[playlistIndex].sortSongs();
      playPlaylist(Playlists[playlistIndex], volume, cout);
    }
    else if (command == "4") {
      playlistIndex = displayPlaylists(Playlists, cout);
    }
    else if (command == "5") {
      Playlists[playlistIndex].sortSongs();
    }
    else if (command == "6") {
      Playlists[playlistIndex].shuffleSongs();
    }
    else if (command == "Q" || command == "q") {
      break;
    }
  }
  return 0;
}