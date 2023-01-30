#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "TestSingleton.hpp"
#include "TopLevelUI.hpp"

using namespace godot;
using namespace OpenVic2;

/// Not strictly required, just common courtesy for tracking the Singleton object.
static TestSingleton *_test_singleton;

/// This is the initialization function, most commonly associated with registering classes and allocating Singletons.
void initialize_openvic2_types(ModuleInitializationLevel p_level)
{
    /// Extra check to ensure module initialization is on at scene level, leave for now.
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<TestSingleton>();

    /// Allocated in order to ensure Singleton exists.
    _test_singleton = memnew(TestSingleton);
    /// Registers a singleton to Godot which can be referenced in GDScript via the identitifer TestSingleton.
    Engine::get_singleton()->register_singleton("TestSingleton", TestSingleton::get_singleton());

    /// Necessary for TopLevelUI to be exposed to Godot.
    ClassDB::register_class<TopLevelUI>();

    /// Register classes here...
}

/// This is the deinitialization function, most commonly associated with deleting things allocated in the initialization function.
void uninitialize_openvic2_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    Engine::get_singleton()->unregister_singleton("TestSingleton");
    memdelete(_test_singleton);
}

extern "C"
{
    // Initialization.

    /// This is the function referenced in game/bin/openvic2.gdextension that is the entry_symbol.
    /// This is used as the core initialization function for the GDExtension.
    /// Leave this format alone for now, there is little need to ever change this.
    GDExtensionBool GDE_EXPORT openvic2_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(initialize_openvic2_types);
        init_obj.register_terminator(uninitialize_openvic2_types);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}