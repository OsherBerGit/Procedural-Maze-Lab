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

var maze_engine = null
var task_id: int = -1
var is_building: bool = false
var generation_history: PackedInt32Array
var current_step_index: int = 0

var steps_per_frame: int = 1
var time_passed: float = 0.0

func _ready() -> void:
	if ClassDB.class_exists("GodotMazeWrapper"):
		maze_engine = ClassDB.instantiate("GodotMazeWrapper")
		
	ui_controller.generate_maze_requested.connect(_generate_new_maze)
	call_deferred("_setup_initial_screen")

func _process(delta: float) -> void:
	if task_id != -1 and WorkerThreadPool.is_task_completed(task_id):
		WorkerThreadPool.wait_for_task_completion(task_id)
		task_id = -1
		
		generation_history = maze_engine.get_generation_history()
		current_step_index = 0
		is_building = true
		time_passed = 0.0

	if is_building:
		var dynamic_delay = ui_controller.current_animation_delay
		
		if dynamic_delay == 0.0:
			while current_step_index < generation_history.size():
				_animate_build_steps()
		else:
			time_passed += delta
			if time_passed >= dynamic_delay:
				time_passed -= dynamic_delay
				_animate_build_steps()

func _generate_new_maze(w: int, h: int, s: int, algo: int) -> void:
	if is_building or task_id != -1: return
		
	if icon_sprite:
		icon_sprite.visible = false
		
	_draw_solid_walls(w, h)
	task_id = WorkerThreadPool.add_task(_thread_generate.bind(w, h, s, algo), true)

func _thread_generate(w: int, h: int, s: int, algo: int) -> void:
	maze_engine.generate_maze(w, h, s, algo)

func _animate_build_steps() -> void:
	var steps_taken = 0
	
	while steps_taken < steps_per_frame and current_step_index < generation_history.size():
		var x = generation_history[current_step_index]
		var y = generation_history[current_step_index + 1]
		var cell_type = generation_history[current_step_index + 2]
		var atlas_coord = WALL_ATLAS_COORD
		
		if cell_type == 1: atlas_coord = PATH_ATLAS_COORD
		elif cell_type == 2: atlas_coord = START_ATLAS_COORD
		elif cell_type == 3: atlas_coord = END_ATLAS_COORD
		
		maze_layer.set_cell(Vector2i(x, y), SOURCE_ID, atlas_coord)
		
		current_step_index += 3
		steps_taken += 1
		
	if current_step_index >= generation_history.size():
		is_building = false

func _center_maze(w: int, h: int) -> void:
	var maze_pixel_width = w * TILE_SIZE
	var maze_pixel_height = h * TILE_SIZE
	var screen_size = get_window().size
	var center_x = (screen_size.x / 2.0) - (maze_pixel_width / 2.0) - 100
	var center_y = (screen_size.y / 2.0) - (maze_pixel_height / 2.0)
	maze_layer.position = Vector2(center_x, center_y)

func _draw_solid_walls(w: int, h: int) -> void:
	maze_layer.clear()
	for y in range(h):
		for x in range(w):
			maze_layer.set_cell(Vector2i(x, y), SOURCE_ID, WALL_ATLAS_COORD)
	_center_maze(w, h)

func _setup_initial_screen() -> void:
	var w = DEFAULT_MAP_SIZE
	var h = DEFAULT_MAP_SIZE
	maze_layer.clear()
	for y in range(h):
		for x in range(w):
			maze_layer.set_cell(Vector2i(x, y), SOURCE_ID, BLANK_ATLAS_COORD)
	_center_maze(w, h)
	
	if icon_sprite:
		icon_sprite.visible = true
		var maze_pixel_width = w * TILE_SIZE
		var maze_pixel_height = h * TILE_SIZE
		icon_sprite.position = maze_layer.position + Vector2(maze_pixel_width / 2.0, maze_pixel_height / 2.0)
