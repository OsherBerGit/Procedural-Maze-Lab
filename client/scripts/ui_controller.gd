extends Control

signal generate_maze_requested(width: int, height: int, seed_val: int, algo: int)

@onready var seed_input = $VBoxContainer/SeedInput
@onready var width_input = $VBoxContainer/WidthInput
@onready var height_input = $VBoxContainer/HeightInput
@onready var algo_selector = $VBoxContainer/AlgoSelector
@onready var generate_button = $VBoxContainer/GenerateButton

@onready var speed_label = $VBoxContainer/SpeedLabel
@onready var speed_slider = $VBoxContainer/SpeedSlider

var current_animation_delay: float = 0.02

const DEFAULT_SIZE = 21
const MIN_SIZE = 5

func _ready() -> void:
	generate_button.pressed.connect(_on_generate_button_pressed)
	speed_slider.value_changed.connect(_on_speed_slider_changed)
	_setup_algorithm_options()
	
func _setup_algorithm_options() -> void:
	algo_selector.clear()
	algo_selector.add_item("DFS (Randomized)", 0)
	algo_selector.add_item("Cellular Automata", 1)

func _on_generate_button_pressed() -> void:
	var width = int(width_input.value) if width_input.value >= MIN_SIZE else DEFAULT_SIZE
	var height = int(height_input.value) if height_input.value >= MIN_SIZE else DEFAULT_SIZE
	var seed = int(seed_input.text) if seed_input.text != "" else randi()
	var algorithm = algo_selector.selected
	
	generate_maze_requested.emit(width, height, seed, algorithm)
	
func _on_speed_slider_changed(value: float) -> void:
	current_animation_delay = value
	if value == 0.0:
		speed_label.text = "Animation Delay: Instant!"
	else:
		speed_label.text = "Animation Delay (sec): " + str(value)
