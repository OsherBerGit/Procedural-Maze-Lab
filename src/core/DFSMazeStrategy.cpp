#include "DFSMazeStrategy.h"
#include <stack>
#include <algorithm>
#include <array>
#include <random>

int DFSMazeStrategy::get_index(int x, int y, int width) const { return y * width + x; }

void DFSMazeStrategy::generate(std::vector<uint8_t>& grid_data, int width, int height, uint32_t seed) {
    static const std::array<GridCoord, 4> master_dirs = { GridCoord{0, -2}, GridCoord{0, 2}, GridCoord{-2, 0}, GridCoord{2, 0} };
    std::mt19937 rng(seed);
    std::stack<GridCoord> stack;

    grid_data.assign(width * height, static_cast<uint8_t>(CellType::WALL));

    grid_data[get_index(1, 1, width)] = static_cast<uint8_t>(CellType::PATH);
    stack.push({1, 1});

    while (!stack.empty()) {
        GridCoord current = stack.top();

        auto neighbors = master_dirs;
        std::shuffle(neighbors.begin(), neighbors.end(), rng);
        bool found_neighbor = false;

        for (const auto& dir : neighbors) {
            int nx = current.x + dir.x;
            int ny = current.y + dir.y;

            if (nx >= 0 && nx < width - 1 && ny >= 0 && ny < height - 1) {
                if (grid_data[get_index(nx, ny, width)] == static_cast<uint8_t>(CellType::WALL)) {
                    int wall_x = current.x + dir.x / 2;
                    int wall_y = current.y + dir.y / 2;

                    grid_data[get_index(wall_x, wall_y, width)] = static_cast<uint8_t>(CellType::PATH);
                    grid_data[get_index(nx, ny, width)] = static_cast<uint8_t>(CellType::PATH);

                    stack.push({nx, ny});
                    found_neighbor = true;
                    break;
                }
            }
        }

        if (!found_neighbor)
            stack.pop();
    }
}