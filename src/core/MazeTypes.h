#pragma once
#include <cstdint>

enum class CellType : uint8_t { WALL, PATH, START, END };

enum class MazeAlgorithm : uint8_t {
    DFS = 0,
    CELLULAR_AUTOMATA = 1
};

struct GridCoord {
    int x;
    int y;
};