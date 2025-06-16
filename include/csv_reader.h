#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <unordered_map>
#include <vector>

using UserRatingsMap = std::unordered_map<int, std::vector<std::pair<int, float>>>;

UserRatingsMap read_csv(const std::string& filename, int& max_user_id, int& max_song_id);

#endif
