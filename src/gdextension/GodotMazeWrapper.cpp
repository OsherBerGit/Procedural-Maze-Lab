#include "GodotMazeWrapper.h"
#include <cstring>

using namespace godot;

void GodotMazeWrapper::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_maze", "width", "height", "seed"), &GodotMazeWrapper::generate_maze);
    ClassDB::bind_method(D_METHOD("get_maze_data"), &GodotMazeWrapper::get_maze_data);
}

GodotMazeWrapper::GodotMazeWrapper() { }

GodotMazeWrapper::~GodotMazeWrapper() { }

void GodotMazeWrapper::generate_maze(int width, int height, int seed) {
    engine = std::make_unique<MazeEngine>(width, height, seed);

    engine->initialize_grid();
    engine->generate_dfs();
}

PackedByteArray GodotMazeWrapper::get_maze_data() const {
    PackedByteArray arr;

    if (!engine)
        return arr;

    const auto& grid = engine->get_grid();
    arr.resize(grid.size());

    std::memcpy(arr.ptrw(), grid.data(), grid.size());

    return arr;
}