#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <memory>

#include "../core/MazeEngine.h"

namespace godot {

    class GodotMazeWrapper : public RefCounted {
        GDCLASS(GodotMazeWrapper, RefCounted)

    private:
        std::unique_ptr<MazeEngine> engine;

    protected:
        static void _bind_methods();

    public:
        GodotMazeWrapper();
        ~GodotMazeWrapper();

        void generate_maze(int width, int height, int seed);
        PackedByteArray get_maze_data() const;
    };

}