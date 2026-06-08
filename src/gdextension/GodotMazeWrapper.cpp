#include "GodotMazeWrapper.h"
#include "../core/IMazeGeneratorStrategy.h"
#include "../core/DFSMazeStrategy.h"
#include "../core/CellularAutomataStrategy.h"
#include <memory>

namespace godot {

    void GodotMazeWrapper::_bind_methods() {
        ClassDB::bind_method(D_METHOD("generate_maze", "width", "height", "seed", "strategy_type"), &GodotMazeWrapper::generate_maze);
        ClassDB::bind_method(D_METHOD("get_maze_data"), &GodotMazeWrapper::get_maze_data);
    }

    void GodotMazeWrapper::generate_maze(int width, int height, uint32_t seed, int strategy_type) {
        maze_data.resize(width * height);

        std::unique_ptr<IMazeGeneratorStrategy> strategy;
        MazeAlgorithm algo = static_cast<MazeAlgorithm>(strategy_type);

        switch (algo) {
            case MazeAlgorithm::DFS:
                strategy = std::make_unique<DFSMazeStrategy>();
                break;
            case MazeAlgorithm::CELLULAR_AUTOMATA:
                strategy = std::make_unique<CellularAutomataStrategy>();
                break;
            default:
                strategy = std::make_unique<DFSMazeStrategy>();
                break;
        }

        MazeValidator validator;
        uint32_t current_seed = seed;
        bool is_valid = false;

        for (int i = 0; i < 10; ++i) {
            strategy->generate(maze_data, width, height, current_seed);

            if (validator.validate_and_place_points(maze_data, width, height, current_seed)) {
                is_valid = true;
                break;
            }
            current_seed++;
        }

        if (!is_valid) {
            auto fallback = std::make_unique<DFSMazeStrategy>();
            fallback->generate(maze_data, width, height, seed);
            validator.validate_and_place_points(maze_data, width, height, seed);
        }

        strategy->generate(maze_data, width, height, seed);
    }

    PackedByteArray GodotMazeWrapper::get_maze_data() const {
        PackedByteArray arr;
        arr.resize(maze_data.size());
        for (size_t i = 0; i < maze_data.size(); ++i)
            arr[i] = maze_data[i];
        return arr;
    }

}