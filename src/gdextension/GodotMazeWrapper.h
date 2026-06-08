#pragma once
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <vector>
#include "../core/MazeTypes.h"

namespace godot {

    class GodotMazeWrapper : public Node2D {
        GDCLASS(GodotMazeWrapper, Node2D);

    private:
        std::vector<uint8_t> maze_data;
        std::vector<MazeStep> generation_history;

    protected:
        static void _bind_methods();

    public:
        GodotMazeWrapper() = default;
        ~GodotMazeWrapper() = default;

        void generate_maze(int width, int height, uint32_t seed, int strategy_type);
        PackedByteArray get_maze_data() const;
        PackedInt32Array get_generation_history() const;
    };

}