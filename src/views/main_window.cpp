#include "c_space_manipulator/views/main_window.hpp"

namespace cspace_manipulator
{
MainWindow::MainWindow()
{
    // Create Tab
    QTabWidget* tabs = new QTabWidget(this);

    // Add User Config and C-Space Tab
    UserConfigView* user_config_view = new UserConfigView(this);
    AppView* app_view = new AppView(this);

    setMinimumSize(800, 600);  // or whatever size is comfortable


    user_config_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    app_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    tabs->addTab(user_config_view, QObject::tr("User Configuration"));
    tabs->addTab(app_view, QObject::tr("C-Space"));


    connect(user_config_view, &UserConfigView::cspaceTabRequested, this, [app_view, tabs](const manipulatorModel &model)
    {
        // update model in c-space tab
        app_view->parseManipulatorModel(model);

        // switch tab to C-space
        tabs->setCurrentIndex(1);
    });

     // Put tabs into a container widget and set as central widget (correct for QMainWindow)
    QWidget* container = new QWidget();
    QVBoxLayout* main_layout = new QVBoxLayout(container);
    main_layout->addWidget(tabs);
    container->setLayout(main_layout);

    // This is the canonical way for QMainWindow:
    this->setCentralWidget(container);

    // Make sure the tab is the visible/current one
    tabs->setCurrentWidget(user_config_view);
    tabs->setVisible(true);

}

} // end of namespace
