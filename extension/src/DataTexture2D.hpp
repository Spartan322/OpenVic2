#pragma once

#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/classes/wrapped.hpp"

namespace OpenVic2 {
    class DataTexture2D : public godot::Texture2D {
        GDCLASS(DataTexture2D, godot::Texture2D)

    public:
        DataTexture2D();
        ~DataTexture2D();

        void reset_override_texture();

        godot::Ref<godot::Texture2D> get_texture() const;
        godot::Ref<godot::Texture2D> get_override_texture() const;
        godot::String get_texture_basename() const;

        void set_texture(const godot::Ref<godot::Texture2D> &p_texture);
        void set_override_texture(const godot::Ref<godot::Texture2D> &p_override);
        void set_texture_basename(godot::String p_basename);

        int32_t _get_width() const override;
        int32_t _get_height() const override;
        bool _is_pixel_opaque(int32_t x, int32_t y) const override;
        bool _has_alpha() const override;
        void _draw(const godot::RID &to_canvas_item, const godot::Vector2 &pos, const godot::Color &modulate, bool transpose) const override;
        void _draw_rect(const godot::RID &to_canvas_item, const godot::Rect2 &rect, bool tile, const godot::Color &modulate, bool transpose) const override;
        void _draw_rect_region(const godot::RID &to_canvas_item, const godot::Rect2 &rect, const godot::Rect2 &src_rect, const godot::Color &modulate, bool transpose, bool clip_uv) const override;

    protected:
        static void _bind_methods();

    private:
        godot::Ref<godot::Texture2D> _texture;
        godot::Ref<godot::Texture2D> _override_texture;
        godot::String _texture_basename;
    };
}
