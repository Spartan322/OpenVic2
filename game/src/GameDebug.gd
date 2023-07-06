extends RefCounted
class_name GameDebug

static func set_debug_mode(value : bool) -> void:
	ArgumentParser.set_argument(&"game-debug", value)
	print("Set debug mode to: ", value)

static func is_debug_mode() -> bool:
	return ArgumentParser.get_argument(&"game-debug", false)
