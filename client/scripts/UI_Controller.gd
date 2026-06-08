extends Control

signal generate_maze_requested(width, height, seed, algorithm)

@onready var seed_input = $VBoxContainer/SeedInput
@onready var width_input = $VBoxContainer/WidthInput
@onready var height_input = $VBoxContainer/HeightInput
@onready var algo_selector = $VBoxContainer/AlgoSelector
@onready var generate_button = $VBoxContainer/GenerateButton

const DEFAULT_SIZE = 21
const MIN_SIZE = 5

func _ready() -> void:
	generate_button.pressed.connect(_on_generate_button_pressed)

func _on_generate_button_pressed() -> void:
	var width = int(width_input.value) if width_input.value >= MIN_SIZE else DEFAULT_SIZE
	var height = int(height_input.value) if height_input.value >= MIN_SIZE else DEFAULT_SIZE
	var seed = int(seed_input.text) if seed_input.text != "" else randi()
	var algorithm = algo_selector.selected
	
	generate_maze_requested.emit(width, height, seed, algorithm)
