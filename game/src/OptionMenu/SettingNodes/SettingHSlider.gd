extends HSlider
class_name SettingHSlider

@export
var section_name : String = "Setting"

@export
var setting_name : String = "SettingHSlider"

@export
var default_value : float = 0

func _enter_tree():
	OptionsMenuPankuEnv._set_option_set_caller(
		section_name + "/" + setting_name,
		func(v) -> String:
			if v == null: return str(value)
			if v is float or v is int:
				value = v
				return str(value)
			return "Option \"%s/%s\" expected float or int, was given \"%s\"" % [section_name, setting_name, v]
	)

func load_setting(file : ConfigFile):
	value = file.get_value(section_name, setting_name, default_value)

func save_setting(file : ConfigFile):
	file.set_value(section_name, setting_name, value)

func reset_setting():
	value = default_value
