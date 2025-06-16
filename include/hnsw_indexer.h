#ifndef HNSW_INDEXER_H
#define HNSW_INDEXER_H

#include <unordered_map>
#include <vector>
#include "hnswlib/hnswlib/hnswlib.h"
#include "csv_reader.h"

class HNSWIndexer {
public:
  HNSWIndexer(int dim, int max_elements, int M = 16, int ef_construction = 200);
  void build_index(const UserRatingsMap& user_ratings, int max_song_id);
  std::vector<std::pair<int, float>> query_similar_users(int user_id, int k) const;

private:
  int dim_;
  hnswlib::L2Space space_;
  std::unique_ptr<hnswlib::HierarchicalNSW<float>> appr_alg_;
  std::unordered_map<int, std::vector<float>> user_vectors_;  // user_id -> vector

  std::vector<float> build_vector(const std::vector<std::pair<int, float>>& ratings, int vector_size) const;
};

#endif
