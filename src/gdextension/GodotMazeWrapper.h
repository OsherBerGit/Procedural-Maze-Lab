#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <vector>
#include <cstdint>

namespace godot {

    class GodotMazeWrapper : public RefCounted {
        GDCLASS(GodotMazeWrapper, RefCounted);

    private:
        std::vector<uint8_t> maze_data;

    protected:
        static void _bind_methods();

    public:
        GodotMazeWrapper() = default;
        ~GodotMazeWrapper() = default;

        void generate_maze(int width, int height, uint32_t seed);
        PackedByteArray get_maze_data() const;
    };

}