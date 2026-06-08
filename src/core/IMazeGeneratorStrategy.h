#pragma once
#include <vector>
#include <cstdint>
#include "MazeTypes.h"

class IMazeGeneratorStrategy {
public:
    virtual ~IMazeGeneratorStrategy() = default;
    virtual void generate(std::vector<uint8_t>& grid_data, int width, int height, uint32_t seed) = 0;
};