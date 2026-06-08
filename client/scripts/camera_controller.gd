extends Camera2D

var is_panning: bool = false
var zoom_min: Vector2 = Vector2(0.5, 0.5)
var zoom_max: Vector2 = Vector2(4.0, 4.0)
var zoom_speed: Vector2 = Vector2(0.15, 0.15)

func _ready() -> void:
	make_current()
	position_smoothing_enabled = true
	position_smoothing_speed = 10.0

func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_RIGHT or event.button_index == MOUSE_BUTTON_MIDDLE:
			is_panning = event.is_pressed()
		
		if event.is_pressed():
			var target_zoom = zoom
			if event.button_index == MOUSE_BUTTON_WHEEL_UP:
				target_zoom += zoom_speed
			elif event.button_index == MOUSE_BUTTON_WHEEL_DOWN:
				target_zoom -= zoom_speed
				
			zoom = target_zoom.clamp(zoom_min, zoom_max)

	elif event is InputEventMouseMotion and is_panning:
		position -= event.relative / zoom

func center_on_target(target_width: float, target_height: float) -> void:
	position = Vector2(target_width / 2.0, target_height / 2.0)
	zoom = Vector2(1.0, 1.0)
