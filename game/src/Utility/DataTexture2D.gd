extends Texture2D
#class_name DataTexture2D

@export
var texture : Texture2D:
	get: return texture
	set(v):
		print(v)
		texture = v
		reset_override_texture()
		emit_changed()

@export
var texture_basename : String = "":
	get:
		if texture_basename == null and texture_basename.is_empty():
			return RenderingServer.texture_get_path(texture.get_rid()).get_basename().replace("res://", "")
		return texture_basename
	set(v):
		print(v)
		texture_basename = v
		reset_override_texture()
		emit_changed()

@export
var override_texture : Texture2D = null:
	get: return override_texture
	set(v):
		print(v)
		override_texture = v
		emit_changed()

func reset_override_texture():
	print("try reset")
	var data_path := ProjectSettings.get_setting("openvic2/mod/data_path") as String
	data_path = data_path.replace("res://", "")
	var texture_search := ".".path_join(data_path).path_join(texture_basename)
	var dir := DirAccess.open(texture_search.get_base_dir())
	print("texture search %s" % texture_search)
	print(texture)
	print(texture_basename)
	if dir == null: return
	print(dir.get_current_dir())

	var filename := texture_basename.get_file()
	var extension_start := filename.rfind(".")
	if extension_start != -1:
		filename = filename.substr(0, extension_start)
	for file in dir.get_files():
		if file.get_basename() == filename:
			var img := Image.load_from_file(texture_search.get_base_dir().path_join(file))
			override_texture = ImageTexture.create_from_image(img)

func _draw(to_canvas_item: RID, pos: Vector2, modulate: Color, transpose: bool) -> void:
	print("draw")
	if override_texture != null:
		override_texture.draw(to_canvas_item, pos, modulate, transpose)
	texture.draw(to_canvas_item, pos, modulate, transpose)

func _draw_rect(to_canvas_item: RID, rect: Rect2, tile: bool, modulate: Color, transpose: bool) -> void:
	print("drect")
	if override_texture != null:
		override_texture.draw_rect(to_canvas_item, rect, tile, modulate, transpose)
		return
	texture.draw_rect(to_canvas_item, rect, tile, modulate, transpose)

func _draw_rect_region(to_canvas_item: RID, rect: Rect2, src_rect: Rect2, modulate: Color, transpose: bool, clip_uv: bool) -> void:
	print("print drregion")
	if override_texture != null:
		override_texture.draw_rect_region(to_canvas_item, rect, src_rect, modulate, transpose, clip_uv)
		return
	texture.draw_rect_region(to_canvas_item, rect, src_rect, modulate, transpose, clip_uv)

func _get_height() -> int:
	print("height")
	if override_texture != null:
		return override_texture.get_height()
	return texture.get_height()

func _get_width() -> int:
	print("width")
	if override_texture != null:
		return override_texture.get_width()
	return texture._get_width()

func _has_alpha() -> bool:
	print("alpha")
	if override_texture != null:
		return override_texture.has_alpha()
	return texture.has_alpha()

func _is_pixel_opaque(x: int, y: int) -> bool:
	print("pixel_opaque")
	if override_texture != null:
		return override_texture.is_pixel_opaque(x, y)
	return texture.is_pixel_opaque(x, y)
