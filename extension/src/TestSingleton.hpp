#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace OpenVic2 {
    class TestSingleton : public godot::Object
    {
        GDCLASS(TestSingleton, godot::Object)

        static TestSingleton *singleton;

    protected:
        static void _bind_methods();

    public:
        static TestSingleton *get_singleton();

        /// Godot will automatically call constructors and destructors.
        TestSingleton();
        ~TestSingleton();

        void hello_singleton();
    };
}