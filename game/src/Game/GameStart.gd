extends Control

const LoadingScreen := preload("res://src/Game/LoadingScreen.gd")
const SoundTabScene := preload("res://src/Game/Menu/OptionMenu/SoundTab.tscn")
const GameMenuScene := preload("res://src/Game/GameMenu.tscn")

@export_subgroup("Nodes")
@export var loading_screen : LoadingScreen

@export_subgroup("")
@export var section_name : String = "general"
@export var setting_name : String = "base_defines_path"
var _settings_base_path : String = ""

func _ready() -> void:
	if ArgumentParser.get_argument(&"help"):
		ArgumentParser._print_help()
		# For some reason this doesn't get freed properly
		# Godot will always quit before it frees the active StreamPlayback resource
		# This hack fixes that
		MusicConductor.queue_free()
		get_tree().quit()
		return

	# Hack to ensure Sound Options load
	var sound_tab := SoundTabScene.instantiate()
	sound_tab.visible = false
	add_child(sound_tab)
	Events.Options.load_settings.connect(_load_setting)
	Events.Options.save_settings.connect(_save_setting)
	Events.Options.load_settings_from_file()
	sound_tab.queue_free()

	loading_screen.start_loading_screen(_initialize_game)

func _load_setting(file : ConfigFile) -> void:
	if file == null: return
	_settings_base_path = file.get_value(section_name, setting_name, "")

func _save_setting(file : ConfigFile) -> void:
	if file == null: return
	file.set_value(section_name, setting_name, _settings_base_path)

func _load_compatibility_mode() -> void:
	# Set this to your Vic2 install dir or a mod's dir to enable compatibility mode
	# (this won't work for mods which rely on vanilla map assets, copy missing assets
	# into the mod's dir for a temporary fix)
	# Usage: OpenVic --compatibility-mode <path>

	var arg_base_path : String = ArgumentParser.get_argument(&"base-path", "")
	var arg_search_path : String = ArgumentParser.get_argument(&"search-path", "")

	var actual_base_path : String = ""

	if arg_base_path:
		if arg_search_path:
			push_warning("Exact base path and search base path arguments both used:\nBase: ", arg_base_path, "\nSearch: ", arg_search_path)
		actual_base_path = arg_base_path
	elif arg_search_path:
		# This will also search for a Steam install if the hint doesn't help
		actual_base_path = GameSingleton.search_for_game_path(arg_search_path)
		if not actual_base_path:
			push_warning("Failed to find assets using search hint: ", arg_search_path)

	if not actual_base_path:
		if _settings_base_path:
			actual_base_path = _settings_base_path
		else:
			# Check if the program is being run from inside the install directory,
			# and if not also search for a Steam install
			actual_base_path = GameSingleton.search_for_game_path("..")
		if not actual_base_path:
			var title : String = "Failed to find game asset path!"
			var msg : String = "The path can be specified with the \"base-path\" command line option."
			OS.alert(msg, title)
			get_tree().quit()
			return

	if not _settings_base_path:
		_settings_base_path = actual_base_path
		# Save the path found in the search
		Events.Options.save_settings_to_file()

	var paths : PackedStringArray = [actual_base_path]

	# Add mod paths
	var settings_mod_names : PackedStringArray = ArgumentParser.get_argument(&"mod", "")
	for mod_name : String in settings_mod_names:
		paths.push_back(actual_base_path + "/mod/" + mod_name)

	if GameSingleton.load_defines_compatibility_mode(paths) != OK:
		push_error("Errors loading game defines!")

# REQUIREMENTS
# * FS-333, FS-334, FS-335, FS-341
func _initialize_game() -> void:
	var start := Time.get_ticks_usec()
	loading_screen.try_update_loading_screen(0)
	GameSingleton.setup_logger()

	Localisation.initialize()
	loading_screen.try_update_loading_screen(15, true)

	_load_compatibility_mode()
	loading_screen.try_update_loading_screen(75, true)

	loading_screen.try_update_loading_screen(100)

	var end := Time.get_ticks_usec()
	print("Loading took ", float(end - start) / 1000000, " seconds")

	# change scene in a thread-safe way
	get_tree().change_scene_to_packed.call_deferred(GameMenuScene)

func _on_splash_container_splash_end() -> void:
	loading_screen.show()
