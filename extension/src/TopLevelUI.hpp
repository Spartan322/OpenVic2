#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace OpenVic2 {
    class TopLevelUI : public godot::Control
    {
        /// GDClass(Self, Inherits) is required for deriving from godot::Object.
        /// Required for Godot to properly support exposing the class to the engine and make calls to it.
        /// Requires a static _bind_methods method on the class somewhere.
        /// Handles things like name and inheritance tree.
        /// Note that with GDExtension, GDCLASS objects are automatically added to Godot Editor's "documentation" list.
        /// However documentation can not be written to yet.
        GDCLASS(TopLevelUI, godot::Control)

        void _on_openvic2_button_pressed();

    protected:
        static void _bind_methods();
    public:
        void _notification(int32_t p_what);

        void add_message_to_list(godot::String p_text);
    };
}
