#include "c_space_manipulator/views/main_window.hpp"

namespace cspace_manipulator
{
MainWindow::MainWindow()
{
    // Create Tab
    QTabWidget* tabs = new QTabWidget(this);

    // Add User Config and C-Space Tab
    UserConfigView* user_config_view = new UserConfigView();
    tabs->addTab(user_config_view, QObject::tr("User Configuration"));
    // tabs->addTab(new AppView(), QObject::tr("C-Space"));


    connect(user_config_view, &UserConfigView::cspaceTabRequested, this, [tabs]()
    {
        tabs->setCurrentIndex(1);
    });

    // Main Layout
    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->addWidget(tabs);

    // Horizontal layout for bottom-right alignment
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addStretch();             // Push button to right
    button_layout->addWidget(create_button); // Add button
    main_layout->addLayout(button_layout);   // Add HBoxLayout to VBoxLayout

    // Set main layout
    setLayout(main_layout);

}
} // end of namespace
