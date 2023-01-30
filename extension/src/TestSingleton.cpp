#include "TestSingleton.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace OpenVic2;

/// Common singleton structure when using Godot.
TestSingleton *TestSingleton::singleton = nullptr;

void TestSingleton::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("hello_singleton"), &TestSingleton::hello_singleton);
}

TestSingleton *TestSingleton::get_singleton()
{
    return singleton;
}

TestSingleton::TestSingleton()
{
    /// Runtime error logging macro for if check is false
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

TestSingleton::~TestSingleton()
{
    /// Runtime error logging macro for if check is false
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void TestSingleton::hello_singleton()
{
    /// UtilityFunctions::print prints both to the console/terminal, meaning stdout, and to Godot's output logger.
    UtilityFunctions::print("Hello GDExtension Singleton!");
}