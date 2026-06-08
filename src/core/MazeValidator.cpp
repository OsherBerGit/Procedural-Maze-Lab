#include "MazeValidator.h"
#include <queue>
#include <random>
#include <array>

int MazeValidator::get_index(int x, int y, int width) const { return y * width + x; }

GridCoord MazeValidator::find_valid_point_in_column(const std::vector<uint8_t>& grid, int width, int height, int start_col, int end_col, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist_x(start_col, end_col);
    std::uniform_int_distribution<int> dist_y(1, height - 2);

    while (true) {
        int x = dist_x(rng);
        int y = dist_y(rng);

        if (grid[get_index(x, y, width)] == static_cast<uint8_t>(CellType::PATH))
            return GridCoord{x, y};
    }
}

bool MazeValidator::run_bfs(const std::vector<uint8_t>& grid, int width, int height, GridCoord start, GridCoord end) {
    static const std::array<GridCoord, 4> neighbors = { GridCoord{0, -1}, GridCoord{0, 1}, GridCoord{-1, 0}, GridCoord{1, 0} };
    std::vector<bool> visited(width * height, false);
    std::queue<GridCoord> queue;

    queue.push(start);
    visited[get_index(start.x, start.y, width)] = true;

    while (!queue.empty()) {
        GridCoord current = queue.front();
        queue.pop();

        if (current.x == end.x && current.y == end.y)
            return true;

        for (const auto& dir : neighbors) {
            int nx = current.x + dir.x;
            int ny = current.y + dir.y;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                int idx = get_index(nx, ny, width);
                if (!visited[idx] && grid[idx] == static_cast<uint8_t>(CellType::PATH)) {
                    visited[idx] = true;
                    queue.push({nx, ny});
                }
            }
        }
    }

    return false;
}

bool MazeValidator::validate_and_place_points(std::vector<uint8_t>& grid, int width, int height, uint32_t seed) {
    const int attempts = 20;
    std::mt19937 rng(seed);

    for (int i = 0; i < attempts; ++i) {
        GridCoord start = find_valid_point_in_column(grid, width, height, 1, 2, rng);
        GridCoord end = find_valid_point_in_column(grid, width, height, width - 3, width - 2, rng);

        if (run_bfs(grid, width, height, start, end)) {
            grid[get_index(start.x, start.y, width)] = static_cast<uint8_t>(CellType::START);
            grid[get_index(end.x, end.y, width)] = static_cast<uint8_t>(CellType::END);

            start_point = start;
            end_point = end;

            return true;
        }
    }

    return false;
}
