#include "../include/app_config.h"
#include <iostream>

using namespace std;

AppInitResult initialize_system(const string& filename) {
  AppInitResult result;
  cout << "Reading file CSV: " << filename << endl;
  result.user_ratings = read_csv(filename, result.max_user_id, result.max_song_id);
  result.total_users = result.user_ratings.size();
  cout << "Total users: " << result.total_users << ", Total songs: " << result.max_song_id << endl;
  return result;
}

void perform_query(const HNSWIndexer& indexer, int query_user_id, int k) {
  try {
    auto neighbors = indexer.query_similar_users(query_user_id, k);
    cout << "Neighbors users of user " << query_user_id << ":\n";
    for (const auto& [id, dist] : neighbors) {
      cout << " - user ID: " << id << ", Distance: " << dist << "\n";
    }
  } catch (const exception& e) {
    cerr << "Query error: " << e.what() << endl;
  }
}
