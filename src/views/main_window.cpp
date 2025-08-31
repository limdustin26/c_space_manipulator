#include "c_space_manipulator/views/main_window.hpp"

namespace cspace_manipulator
{
MainWindow::MainWindow()
{
    // Create Tab
    QTabWidget* tabs = new QTabWidget(this);

    // Add User Config and C-Space Tab
    tabs->addTab(new UserConfigView(), QObject::tr("User Configuration"));
    // tabs->addTab(new AppView(), QObject::tr("C-Space"));

    // Update Button
    QPushButton* update_button = new QPushButton(tr("Update"), this);
    // connect(push_button, &QPushButton::clicked, this, &UserConfigView::updateManipulatorModel);

    // Main Layout
    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->addWidget(tabs);

    // Horizontal layout for bottom-right alignment
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addStretch();             // Push button to right
    button_layout->addWidget(update_button); // Add button
    main_layout->addLayout(button_layout);   // Add HBoxLayout to VBoxLayout

    // Set main layout
    setLayout(main_layout);

}
} // end of namespace