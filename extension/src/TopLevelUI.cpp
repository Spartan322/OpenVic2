#include "TopLevelUI.hpp"

/// These are the node headers
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
///

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/node_path.hpp>

#include <godot_cpp/core/memory.hpp>

using namespace godot;
using namespace OpenVic2;

/// Nothing special going on here.
void TopLevelUI::_on_openvic2_button_pressed() {
    add_message_to_list("Button Pressed");
}

/// _notification is a regular method used to designate what type of behavior should be performed.
/// p_what is the notification type. Refers to constants prefixed with NOTIFICATION_.
/// See https://docs.godotengine.org/en/latest/classes/class_node.html#constants for some basic node notifications.
/// NOTIFICATION_READY runs when the node has been readied in the node tree, meaning its children and itself have been loaded into the node tree.
/// See also https://docs.godotengine.org/en/latest/classes/class_node.html#class-node-method-ready
void TopLevelUI::_notification(int32_t p_what) {
    switch(p_what) {
        case NOTIFICATION_READY:
            /// b is an unowned pointer
            /// Node::get_node<T> or this->get_node<T> uses a NodePath to get a node that is at that NodePath.
            /// Button is a basic clickable button node with text.
            /// Documentation for Button found at: https://docs.godotengine.org/en/latest/classes/class_button.html
            /// NodePath is an object for pathing through the Godot node tree.
            /// NodePath willl also implicitly convert from a const char*.
            Button *b = get_node<Button>(NodePath("ListOfUIElements/OpenVic2Button"));

            /// Godot also supports a special % syntax for NodePaths that can retrieve nodes that are made scene unique node names.
            /// Instead of referencing the whole path to get the node, you can reference it by name with %.
            /// In the node tree the node will be marked with a % if it has a scene unique name.
            /// This accomplishes the same thing as OpenVic2Button is unique named within the Godot scene.
            b = get_node<Button>("%OpenVic2Button");

            /// Object::connect is how you connect a Callable to a signal
            /// StringNames are string interned strings, so any string with the same value will produce the same char*.
            /// The first paremeter of connect is the signal name, in this case buttons have pressed signals.
            /// Found in the documentation at https://docs.godotengine.org/en/latest/classes/class_basebutton.html#signals
            /// Callable is an object that stores a method.
            /// The Callable ctor's first parameter is the instance that the Callable will be called.
            /// The Callable ctor's second parameter is the name of the method that will be called when it is called.
            b->connect(StringName("pressed"), Callable(this, "_on_openvic2_button_pressed"));
    }
}

void TopLevelUI::add_message_to_list(String p_text = "") {
    /// VBoxContainer is a vertical list container for its children.
    /// Its children will be listed in a vertical order according to the node tree.
    VBoxContainer *vbc = get_node<VBoxContainer>("%OpenVic2MsgList");

    /// Label is the standard text display UI node.
    /// memnew(T) is how Godot allocates memory, its primary extra functionality is tracking allocation counts .
    Label *label_to_make = memnew(Label);
    /// Label::set_text is the setter method that sets a label's text property.
    label_to_make->set_text(p_text);

    /// Node::add_child adds a node to the end of the node's children list, causing it to perform procesing, input, and drawing in the engine.
    /// This is required for nodes to function.
    /// This takes ownership of the node, unless the child is removed, it automatically frees the child node's memory.
    vbc->add_child(label_to_make);
}


/// _bind_methods is a required static method for all classes derived somewhere from godot::Object.
/// _bind_methods is run on engine initialization and fills the engine with all the necessary data for the engine to understand the class.
void TopLevelUI::_bind_methods() {
    /// ClassDB::bind_method binds a method to a name that can be referenced anywhere in Godot.
    /// D_METHOD creates a method definition that is used as a signture for the method in Godot.
    /// First parameter of D_METHOD is the name of the method.
    /// All subsequent parameters of D_METHOD are the names of the parameters for the method.
    /// The first parameter of bind_method must be a method definition so must use D_METHOD.
    /// The second paremeter of bind_method must be a function reference that will called when the method would be called in engine.
    /// Each subsequent parameter of bind_method assigns a default value to the method in Godot. It is however not required.
    /// The name of the method is irrelevant to its reference.
    /// bind_method automatically binds the method to this, so all instances of TopLevelUI can call an add_message_to_list method.
    ClassDB::bind_method(D_METHOD("add_message_to_list", "text"), &TopLevelUI::add_message_to_list, "");

    ClassDB::bind_method(D_METHOD("_on_openvic2_button_pressed"), &TopLevelUI::_on_openvic2_button_pressed);
}