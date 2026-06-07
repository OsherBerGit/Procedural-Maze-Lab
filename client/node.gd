extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var maze = GodotMazeWrapper.new()
	maze.generate_maze(21, 21, 12345)
	print(maze.get_maze_data())


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
