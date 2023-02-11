extends OptionButton
class_name SettingOptionButton

@export
var section_name : String = "Setting"

@export
var setting_name : String = "SettingOptionMenu"

@export
var default_value : int = 0

func _enter_tree():
	OptionsMenuPankuEnv._set_option_set_caller(
		section_name + "/" + setting_name,
		func(v) -> String:
			if v == null: return get_item_text(selected)
			if v is int or v is String or v is StringName:
				if v is String or v is StringName:
					var is_valid := false
					for index in item_count:
						var test := get_item_text(index)
						if test == v:
							v = index
							is_valid = true
							break

					if not is_valid:
						return "Option \"%s/%s\" expected int or valid setting string, was given \"%s\"" % [section_name, setting_name, v]

				selected = v
				item_selected.emit(selected)
				return get_item_text(selected)
			return "Option \"%s/%s\" expected int or valid setting string, was given \"%s\"" % [section_name, setting_name, v]
	)

func load_setting(file : ConfigFile):
	selected = file.get_value(section_name, setting_name, default_value)
	item_selected.emit(selected)

func save_setting(file : ConfigFile):
	file.set_value(section_name, setting_name, selected)

func reset_setting():
	selected = default_value
	item_selected.emit(selected)
