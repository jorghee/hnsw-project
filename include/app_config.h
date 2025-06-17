#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <string>
#include "csv_reader.h"
#include "hnsw_indexer.h"
#include <string>

struct AppInitResult {
  UserRatingsMap user_ratings;
  int max_user_id;
  int max_song_id;
  int total_users;
};

AppInitResult initialize_system(const std::string& filename);
void perform_query(const HNSWIndexer& indexer, int query_user_id, int k);

#endif
