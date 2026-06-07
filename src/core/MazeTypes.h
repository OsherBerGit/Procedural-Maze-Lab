#pragma once
#include <cstdint>

enum class CellType : uint8_t { WALL, PATH, START, END };

struct GridCoord {
    int x;
    int y;
};