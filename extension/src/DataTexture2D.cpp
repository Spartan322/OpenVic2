
#include "DataTexture2D.hpp"
#include "godot_cpp/classes/rendering_server.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/callable.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;
using namespace OpenVic2;

DataTexture2D::DataTexture2D() {
    reset_override_texture();
}

DataTexture2D::~DataTexture2D() {
}

void DataTexture2D::reset_override_texture() {
    // var data_path := ProjectSettings.get_setting("openvic2/mod/data_path") as String
    // data_path = data_path.replace("res://", "")
    // var texture_search := ".".path_join(data_path).path_join(texture_basename)
    // var dir := DirAccess.open(texture_search.get_base_dir())
    // print("texture search %s" % texture_search)
    // print(texture)
    // print(texture_basename)
    // if dir == null: return
    // print(dir.get_current_dir())

    // var filename := texture_basename.get_file()
    // var extension_start := filename.rfind(".")
    // if extension_start != -1:
    //  filename = filename.substr(0, extension_start)
    // for file in dir.get_files():
    //  if file.get_basename() == filename:
    //      var img := Image.load_from_file(texture_search.get_base_dir().path_join(file))
    //      override_texture = ImageTexture.create_from_image(img)



}

Ref<Texture2D> DataTexture2D::get_texture() const {
    return _texture;
}

Ref<Texture2D> DataTexture2D::get_override_texture() const {
    return _override_texture;
}

String DataTexture2D::get_texture_basename() const {
    if(_texture_basename.is_empty() && _texture.is_valid()) {
        return RenderingServer::get_singleton()->texture_get_path(_texture->get_rid()).get_basename().replace("res://", "");
    }
    return _texture_basename;
}

void DataTexture2D::set_texture(const Ref<Texture2D> &p_texture) {
    ERR_FAIL_COND(p_texture == this);
    if(p_texture == _texture) {
        return;
    }
    if(_texture.is_valid()) {
        _texture->disconnect("changed", Callable(this, "emit_changed"));
    }
    _texture = p_texture;
    if(_texture.is_valid()) {
        _texture->connect("changed", Callable(this, "emit_changed"));
    }
    reset_override_texture();
    emit_changed();
}

void DataTexture2D::set_override_texture(const Ref<Texture2D> &p_override) {
    ERR_FAIL_COND(p_override == this);
    if(p_override == _override_texture) {
        return;
    }
    if(_override_texture.is_valid()) {
        _override_texture->disconnect("changed", Callable(this, "emit_changed"));
    }
    _override_texture = p_override;
    if(_texture.is_valid()) {
        _override_texture->connect("changed", Callable(this, "emit_changed"));
    }
    reset_override_texture();
    emit_changed();
}

void DataTexture2D::set_texture_basename(String p_basename) {
    _texture_basename = p_basename;
    reset_override_texture();
    emit_changed();
}

int32_t DataTexture2D::_get_width() const {
    if(_override_texture.is_valid()) {
        return _override_texture->_get_width();
    }
    return _texture->_get_width();
}

int32_t DataTexture2D::_get_height() const {
    if(_override_texture.is_valid()) {
        return _override_texture->_get_height();
    }
    return _texture->_get_height();
}

bool DataTexture2D::_is_pixel_opaque(int32_t p_x, int32_t p_y) const {
    if(_override_texture.is_valid()) {
        return _override_texture->_is_pixel_opaque(p_x, p_y);
    }
    return _texture->_is_pixel_opaque(p_x, p_y);
}

bool DataTexture2D::_has_alpha() const {
    if(_override_texture.is_valid()) {
        return _override_texture->_has_alpha();
    }
    return _texture->_has_alpha();
}

void DataTexture2D::_draw(const RID &p_to_canvas_item, const Vector2 &p_pos, const Color &p_modulate, bool p_transpose) const {
    if(_override_texture.is_valid()) {
        _override_texture->_draw(p_to_canvas_item, p_pos, p_modulate, p_transpose);
        return;
    }
    return _texture->_draw(p_to_canvas_item, p_pos, p_modulate, p_transpose);
}

void DataTexture2D::_draw_rect(const RID &p_to_canvas_item, const Rect2 &p_rect, bool p_tile, const Color &p_modulate, bool p_transpose) const {
    if(_override_texture.is_valid()) {
        _override_texture->_draw_rect(p_to_canvas_item, p_rect, p_tile, p_modulate, p_transpose);
        return;
    }
    return _texture->_draw_rect(p_to_canvas_item, p_rect, p_tile, p_modulate, p_transpose);
}

void DataTexture2D::_draw_rect_region(
    const RID &p_to_canvas_item,
    const Rect2 &p_rect,
    const Rect2 &p_src_rect,
    const Color &p_modulate,
    bool p_transpose,
    bool p_clip_uv
) const {
    if(_override_texture.is_valid()) {
        _override_texture->_draw_rect_region(p_to_canvas_item, p_rect, p_src_rect, p_modulate, p_transpose, p_clip_uv);
        return;
    }
    return _texture->_draw_rect_region(p_to_canvas_item, p_rect, p_src_rect, p_modulate, p_transpose, p_clip_uv);
}

void DataTexture2D::_bind_methods() {

    ClassDB::bind_method(D_METHOD("reset_override_texture"), &DataTexture2D::reset_override_texture);

    ClassDB::bind_method(D_METHOD("get_texture"), &DataTexture2D::get_texture);
    ClassDB::bind_method(D_METHOD("get_override_texture"), &DataTexture2D::get_override_texture);
    ClassDB::bind_method(D_METHOD("get_texture_basename"), &DataTexture2D::get_texture_basename);

    ClassDB::bind_method(D_METHOD("set_texture", "texture"), &DataTexture2D::set_texture);
    ClassDB::bind_method(D_METHOD("set_override_texture", "override"), &DataTexture2D::set_override_texture);
    ClassDB::bind_method(D_METHOD("set_texture_basename", "basename"), &DataTexture2D::set_texture_basename);

    ADD_PROPERTY(PropertyInfo(Variant::Type::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");
    ADD_PROPERTY(PropertyInfo(Variant::Type::OBJECT, "override_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_override_texture", "get_override_texture");
    ADD_PROPERTY(PropertyInfo(Variant::Type::STRING, "texture_basename"), "set_texture_basename", "get_texture_basename");

    // ClassDB::bind_method(D_METHOD("_get_width"), &DataTexture2D::_get_width);
    // ClassDB::bind_method(D_METHOD("_get_height"), &DataTexture2D::_get_height);
    // ClassDB::bind_method(D_METHOD("_is_pixel_opaque", "x", "y"), &DataTexture2D::_is_pixel_opaque);
    // ClassDB::bind_method(D_METHOD("_has_alpha"), &DataTexture2D::_has_alpha);
    // ClassDB::bind_method(D_METHOD("_draw", "to_canvas_item", "pos", "modulate", "transpose"), &DataTexture2D::_draw);
    // ClassDB::bind_method(D_METHOD("_draw_rect", "to_canvas_item", "rect", "tile", "modulate", "transpose"), &DataTexture2D::_draw_rect);
    // ClassDB::bind_method(D_METHOD("_draw_rect_region", "to_canvas_item", "rect", "src_rect", "modulate", "transpose", "clip_uv"), &DataTexture2D::_draw_rect_region);
}