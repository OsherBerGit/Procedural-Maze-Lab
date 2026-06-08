#pragma once
#include "IMazeGeneratorStrategy.h"

class DFSMazeStrategy : public IMazeGeneratorStrategy {
private:
    int get_index(int x, int y, int width) const;

public:
    void generate(std::vector<uint8_t>& grid_data, int width, int height, uint32_t seed) override;
};