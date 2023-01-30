extends Node

func _ready():
	print("From GDScript")
	TestSingleton.hello_singleton()


func _on_ui_root_ready():
	$UIRoot.add_message_to_list("Hello OpenVic2")
