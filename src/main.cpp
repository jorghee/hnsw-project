#include "../include/app_config.h"
#include <iostream>

using namespace std;

int main() {
  string filename = "data/ratings.csv";
  UserRatingsMap user_ratings;
  int max_user_id = 0, max_song_id = 0;

  int M = 16;
  int ef_construction = 200;
  int ef_search = 50;

  AppInitResult init = initialize_system(filename);

  HNSWIndexer indexer(
    init.max_song_id + 1,
    init.total_users,
    M,
    ef_construction
  );

  indexer.build_index(init.user_ratings, init.max_song_id);

  int query_user_id, k;
  cout << "Ingrese el ID del usuario que desea consultar: ";
  cin >> query_user_id;
  cout << "Ingrese la cantidad de usuarios similares a retornar: ";
  cin >> k;

  perform_query(indexer, query_user_id, k);

  return 0;
}
