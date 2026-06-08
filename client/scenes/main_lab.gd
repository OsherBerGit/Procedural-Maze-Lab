extends Node2D

const SOURCE_ID = 1
const WALL_ATLAS_COORD = Vector2i(9, 4)
const PATH_ATLAS_COORD = Vector2i(7, 12)
const STRATEGY_TYPE = 1

@onready var maze_layer = $MazeRenderer

func _ready() -> void:
	var maze_engine = GodotMazeWrapper.new()
	
	var width = 21
	var height = 21
	
	maze_engine.generate_maze(width, height, randi(), STRATEGY_TYPE)
	var data = maze_engine.get_maze_data()
	
	maze_layer.clear()
	
	for y in range(height):
		for x in range(width):
			var index = y * width + x
			var cell_type = data[index]
			var atlas_coord = PATH_ATLAS_COORD if cell_type == 1 else WALL_ATLAS_COORD
			maze_layer.set_cell(Vector2i(x, y), SOURCE_ID, atlas_coord)
