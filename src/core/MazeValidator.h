#pragma once
#include <vector>
#include <cstdint>
#include <random>
#include "MazeTypes.h"

class MazeValidator {
private:
    GridCoord find_valid_point_in_column(const std::vector<uint8_t>& grid, int width, int height, int start_col, int end_col, std::mt19937& rng);
    bool run_bfs(const std::vector<uint8_t>& grid, int width, int height, GridCoord start, GridCoord end);
    int get_index(int x, int y, int width) const;

public:
    bool validate_and_place_points(std::vector<uint8_t>& grid, int width, int height, uint32_t seed);
};