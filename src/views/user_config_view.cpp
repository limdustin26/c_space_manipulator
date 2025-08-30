#include "c_space_manipulator/views/user_config_view.hpp"

cspace_manipulator::UserConfigView(QWidget* parent) : QWidget(parent)
{
    // By default 2 Links are there
    // Link 1
    LinkConfigView default_link1 = new LinkConfigView(1, this);

    // Link 2
    LinkConfigView default_link2 = new LinkConfigView(2, this);

    // Add/Remove Latest Link Button
    

    // Scroll Bar

    // Update Button

    // Layout
}