#include "../include/hnsw_indexer.h"
#include <stdexcept>

using namespace std;

HNSWIndexer::HNSWIndexer(int dim, int max_elements, int M, int ef_construction)
    : dim_(dim),
      space_(dim),
      appr_alg_(make_unique<hnswlib::HierarchicalNSW<float>>(&space_, max_elements)) {
  appr_alg_->ef_construction_ = ef_construction;
  appr_alg_->setEf(50);
  appr_alg_->maxM_ = M;
}

void HNSWIndexer::build_index(const UserRatingsMap& user_ratings, int max_song_id) {
  for (const auto& [user_id, ratings] : user_ratings) {
    vector<float> vec = build_vector(ratings, max_song_id);
    user_vectors_[user_id] = vec;
    appr_alg_->addPoint(vec.data(), user_id);
  }
}

vector<float> HNSWIndexer::build_vector(const vector<pair<int, float>>& ratings, int vector_size) const {
  vector<float> vec(vector_size + 1, 0.0f);
  for (const auto& [song_id, score] : ratings) {
    if (song_id >= 1 && song_id <= vector_size) {
      vec[song_id] = score;
    }
  }
  return vec;
}

vector<pair<int, float>> HNSWIndexer::query_similar_users(int user_id, int k) const {
  auto it = user_vectors_.find(user_id);
  if (it == user_vectors_.end()) {
    throw runtime_error("User ID not found in index.");
  }

  const vector<float>& query_vec = it->second;

  auto result = appr_alg_->searchKnn(query_vec.data(), k + 1);

  vector<pair<int, float>> neighbors;
  while (!result.empty()) {
    auto [dist, label] = result.top();
    result.pop();
    if (label != user_id) {
      neighbors.emplace_back(label, dist);
    }
  }
  return neighbors;
}
