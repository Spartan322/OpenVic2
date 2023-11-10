#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/string.hpp>

namespace OpenVic {
	class Checksum : public godot::Object {
		GDCLASS(Checksum, godot::Object)

		// BEGIN BOILERPLATE
		static inline Checksum* _checksum = nullptr;

	protected:
		static void _bind_methods();

	public:
		static Checksum* get_singleton();

		Checksum();
		~Checksum();
		// END BOILERPLATE

		godot::String get_checksum_text();
	};
}
