#pragma once

#include <godot_cpp/classes/atlas_texture.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <openvic-simulation/interface/GFXSprite.hpp>

namespace OpenVic {
	class AssetManager : public godot::Object {
		GDCLASS(AssetManager, godot::Object)

		static inline AssetManager* _singleton = nullptr;

	public:
		enum LoadFlags {
			LOAD_FLAG_NONE          = 0,
			LOAD_FLAG_CACHE_IMAGE   = 1 << 0,
			LOAD_FLAG_CACHE_TEXTURE = 1 << 1,
			LOAD_FLAG_FLIP_Y        = 1 << 2
		};

		constexpr friend LoadFlags operator|(LoadFlags lhs, LoadFlags rhs) {
			return static_cast<LoadFlags>(static_cast<int>(lhs) | static_cast<int>(rhs));
		}

	private:
		struct image_asset_t {
			std::optional<godot::Ref<godot::Image>> image;
			std::optional<godot::Ref<godot::ImageTexture>> texture;
		};
		/* deque_ordered_map to avoid the need to reallocate. */
		using image_asset_map_t = deque_ordered_map<godot::StringName, image_asset_t>;
		using font_map_t = deque_ordered_map<godot::StringName, godot::Ref<godot::Font>>;

		image_asset_map_t image_assets;
		font_map_t fonts;

		static godot::Ref<godot::Image> _load_image(godot::StringName const& path, bool flip_y);

	protected:
		static void _bind_methods();

	public:
		static AssetManager* get_singleton();

		AssetManager();
		~AssetManager();

		/* Search for and load an image at the specified path relative to the game defines, first checking the AssetManager's
		 * image cache in case it has already been loaded, and returning nullptr if image loading fails. If the cache image
		 * load flag is set then the loaded image will be stored in the AssetManager's image cache for future access; if the
		 * flip y load flag is set then the image will be flipped vertically before being returned (if the image is already
		 * in the cache then no flipping will occur, regardless of whether it was orginally flipped or not). */
		godot::Ref<godot::Image> get_image(godot::StringName const& path, LoadFlags load_flags = LOAD_FLAG_CACHE_IMAGE);

		/* Create a texture from an image found at the specified path relative to the game defines, fist checking the
		 * AssetManager's texture cache in case it has already been loaded, and returning nullptr if image loading or texture
		 * creation fails. If the cache image load flag is set then the loaded image will be stored in the AssetManager's
		 * image cache for future access; if the cache texture load flag is set then the created texture will be stored in the
		 * AssetManager's texture cache for future access; if the flip y load flag is set then the image will be flipped
		 * vertically before being used to create the texture (if the image is already in the cache then no flipping will
		 * occur, regardless of whether it was orginally flipped or not). */
		godot::Ref<godot::ImageTexture> get_texture(
			godot::StringName const& path, LoadFlags load_flags = LOAD_FLAG_CACHE_TEXTURE
		);

		/* Search for and load a font with the specified name from the game defines' font directory, first checking the
		 * AssetManager's font cache in case it has already been loaded, and returning nullptr if font loading fails. */
		godot::Ref<godot::Font> get_font(godot::StringName const& name);
	};
}

VARIANT_ENUM_CAST(OpenVic::AssetManager::LoadFlags);
