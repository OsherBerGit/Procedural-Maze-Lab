#include "GodotMazeWrapper.h"
#include "../core/DFSMazeStrategy.h"

namespace godot {

    void GodotMazeWrapper::_bind_methods() {
        ClassDB::bind_method(D_METHOD("generate_maze", "width", "height", "seed"), &GodotMazeWrapper::generate_maze);
        ClassDB::bind_method(D_METHOD("get_maze_data"), &GodotMazeWrapper::get_maze_data);
    }

    void GodotMazeWrapper::generate_maze(int width, int height, uint32_t seed) {
        maze_data.resize(width * height);
        DFSMazeStrategy strategy;
        strategy.generate(maze_data, width, height, seed);
    }

    PackedByteArray GodotMazeWrapper::get_maze_data() const {
        PackedByteArray arr;
        arr.resize(maze_data.size());
        for (size_t i = 0; i < maze_data.size(); ++i)
            arr[i] = maze_data[i];
        return arr;
    }

}