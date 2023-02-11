extends Node

signal call_options_menu_save

var _options_call_dict := {}

const _HELP_get_options_list := "Lists the assignable options for the options menu."
func get_options_list() -> String:
	var result : Array[String] = []
	for option_name in _options_call_dict:
		result.append(option_name)
	return "\n" + "\n".join(result)

const _HELP_set_option := "Sets an assignable option in the options menu."
func set_option(option_key : String, option_value = null) -> String:
	if option_key in _options_call_dict:
		return _options_call_dict[option_key].call_setter(option_value)
	return "Option \"%s\" key could not be found" % option_key

class _OptionSetCaller:
	var environment
	var setter_caller : Callable
	func _init(env, setter : Callable):
		environment = env
		setter_caller = setter
	func call_setter(v) -> String:
		var result : String = setter_caller.call(v)
		environment.call_options_menu_save.emit()
		return result

func _set_option_set_caller(option_key : String, option_set_caller : Callable) -> void:
	_options_call_dict[option_key] = _OptionSetCaller.new(self, option_set_caller)
