#include "GodotMazeWrapper.h"
#include "../core/IMazeGeneratorStrategy.h"
#include "../core/DFSMazeStrategy.h"
#include "../core/CellularAutomataStrategy.h"
#include "../core/MazeValidator.h"
#include <memory>

namespace godot {

    void GodotMazeWrapper::_bind_methods() {
        ClassDB::bind_method(D_METHOD("generate_maze", "width", "height", "seed", "strategy_type"), &GodotMazeWrapper::generate_maze);
        ClassDB::bind_method(D_METHOD("get_maze_data"), &GodotMazeWrapper::get_maze_data);
        ClassDB::bind_method(D_METHOD("get_generation_history"), &GodotMazeWrapper::get_generation_history);
    }

    void GodotMazeWrapper::generate_maze(int width, int height, uint32_t seed, int strategy_type) {
        maze_data.resize(width * height);
        generation_history.clear();

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
            generation_history.clear();
            strategy->generate(maze_data, width, height, current_seed, generation_history);

            if (validator.validate_and_place_points(maze_data, width, height, current_seed)) {
                generation_history.push_back({validator.get_start_point().x, validator.get_start_point().y, 2});
                generation_history.push_back({validator.get_end_point().x, validator.get_end_point().y, 3});
                is_valid = true;
                break;
            }
            current_seed++;
        }

        if (!is_valid) {
            generation_history.clear();
            auto fallback = std::make_unique<DFSMazeStrategy>();
            fallback->generate(maze_data, width, height, seed, generation_history);
            validator.validate_and_place_points(maze_data, width, height, seed);
            generation_history.push_back({validator.get_start_point().x, validator.get_start_point().y, 2});
            generation_history.push_back({validator.get_end_point().x, validator.get_end_point().y, 3});
        }
    }

    PackedByteArray GodotMazeWrapper::get_maze_data() const {
        PackedInt32Array arr;
        arr.resize(generation_history.size() * 3);
        int idx = 0;
        for (const auto& step : generation_history) {
            arr[idx++] = step.x;
            arr[idx++] = step.y;
            arr[idx++] = step.type;
        }
        return arr;
    }

}