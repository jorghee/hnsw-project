#include "../include/csv_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

UserRatingsMap read_csv(const string& filename, int& max_user_id, int& max_song_id) {
  UserRatingsMap user_ratings;
  ifstream file(filename);
  string line;
  int user_id, song_id;
  float rating;
  string temp;

  max_user_id = 0;
  max_song_id = 0;

  if (!file.is_open()) {
    cerr << "No se pudo abrir el archivo: " << filename << endl;
    return user_ratings;
  }

  while (getline(file, line)) {
    stringstream ss(line);
    string field;

    getline(ss, field, ',');
    user_id = stoi(field);

    getline(ss, field, ',');
    song_id = stoi(field);

    getline(ss, field, ',');
    rating = stof(field);

    // Ignorar el cuarto campo
    getline(ss, temp, ',');

    user_ratings[user_id].emplace_back(song_id, rating);

    if (user_id > max_user_id) max_user_id = user_id;
    if (song_id > max_song_id) max_song_id = song_id;
  }

  return user_ratings;
}
