#pragma once
#include "IMazeGeneratorStrategy.h"

class CellularAutomataStrategy : public IMazeGeneratorStrategy {
private:
    int get_index(int x, int y, int width) const;
    int count_alive_neighbors(const std::vector<uint8_t>& grid, int x, int y, int width, int height) const;

public:
    void generate(std::vector<uint8_t>& grid_data, int width, int height, uint32_t seed) override;
};