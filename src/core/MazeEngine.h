#pragma once
#include <vector>
#include <random>
#include "MazeTypes.h"

class MazeEngine {
private:
    int width;
    int height;

    std::vector<uint8_t> grid_data;
    std::mt19937 rng;

    inline int get_index(int x, int y) const {
        return y * width + x;
    }

public:
    MazeEngine(int w, int h, uint32_t seed = 12345);
    ~MazeEngine() = default;

    void initialize_grid();

    void generate_dfs();

    const std::vector<uint8_t>& get_grid() const { return grid_data; }
    int get_width() const { return width; }
    int get_height() const { return height; }
};