extends Node2D

const SOURCE_ID = 1
const TILE_SIZE = 16
const BLANK_ATLAS_COORD = Vector2i(6, 24)
const WALL_ATLAS_COORD = Vector2i(9, 4)
const PATH_ATLAS_COORD = Vector2i(7, 12)
const START_ATLAS_COORD = Vector2i(1, 14)
const END_ATLAS_COORD = Vector2i(3, 11)
const DEFAULT_MAP_SIZE = 21

@onready var maze_layer = $MazeRenderer
@onready var ui_controller = $CanvasLayer/UI_Root/ControlPanel
@onready var icon_sprite = $IconSprite

var maze_engine: GodotMazeWrapper

func _ready() -> void:
	maze_engine = GodotMazeWrapper.new()
	ui_controller.generate_maze_requested.connect(_generate_new_maze)
	call_deferred("_draw_empty_board", DEFAULT_MAP_SIZE, DEFAULT_MAP_SIZE)

func _generate_new_maze(w: int, h: int, s: int, algo: int) -> void:
	icon_sprite.visible = false
	maze_engine.generate_maze(w, h, s, algo)
	var data = maze_engine.get_maze_data()
	maze_layer.clear()
	
	for y in range(h):
		for x in range(w):
			var index = y * w + x
			var cell_type = data[index]
			var atlas_coord = WALL_ATLAS_COORD
			
			if cell_type == 1: atlas_coord = PATH_ATLAS_COORD
			elif cell_type == 2: atlas_coord = START_ATLAS_COORD
			elif cell_type == 3: atlas_coord = END_ATLAS_COORD
				
			maze_layer.set_cell(Vector2i(x, y), SOURCE_ID, atlas_coord)
			
	_center_maze(w, h)

func _center_maze(w: int, h: int) -> void:
	var maze_pixel_width = w * TILE_SIZE
	var maze_pixel_height = h * TILE_SIZE
	var screen_size = get_window().size
	var center_x = (screen_size.x / 2.0) - (maze_pixel_width / 2.0) - 100
	var center_y = (screen_size.y / 2.0) - (maze_pixel_height / 2.0)
	maze_layer.position = Vector2(center_x, center_y)

func _draw_empty_board(w: int, h: int) -> void:
	maze_layer.clear()
	for y in range(h):
		for x in range(w):
			maze_layer.set_cell(Vector2i(x, y), SOURCE_ID, BLANK_ATLAS_COORD)
	_center_maze(w, h)
	
	var maze_pixel_width = w * TILE_SIZE
	var maze_pixel_height = h * TILE_SIZE
	icon_sprite.visible = true
	icon_sprite.position = maze_layer.position + Vector2(maze_pixel_width / 2.0, maze_pixel_height / 2.0)
