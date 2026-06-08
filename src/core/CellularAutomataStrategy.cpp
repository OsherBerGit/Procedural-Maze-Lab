#include <random>
#include "CellularAutomataStrategy.h"

int CellularAutomataStrategy::get_index(int x, int y, int width) const { return y * width + x; }

int CellularAutomataStrategy::count_alive_neighbors(const std::vector<uint8_t>& grid, int x, int y, int width, int height) const {
    int count = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                count++;
            else
                if (grid[get_index(nx, ny, width)] == static_cast<uint8_t>(CellType::WALL))
                    count++;
        }
    }

    return count;
}

void CellularAutomataStrategy::generate(std::vector<uint8_t>& grid_data, int width, int height, uint32_t seed) {
    const int fill_probability = 45;
    const int smooth_iterations = 5;
    const int wall_threshold = 4;

    std::mt19937 rng(seed);

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            grid_data[get_index(x, y, width)] = rng() % 100 < fill_probability ? static_cast<uint8_t>(CellType::WALL) : static_cast<uint8_t>(CellType::PATH);

    for (int i = 0; i < smooth_iterations; ++i) {
        std::vector<uint8_t> new_grid = grid_data;

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                int count = count_alive_neighbors(grid_data, x, y, width, height);

                if (count > wall_threshold)
                    new_grid[get_index(x, y, width)] = static_cast<uint8_t>(CellType::WALL);
                else if (count < wall_threshold)
                    new_grid[get_index(x, y, width)] = static_cast<uint8_t>(CellType::PATH);
            }
        }

        grid_data = new_grid;
    }
}