#include "c_space_manipulator/views/main_window.hpp"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cspace_manipulator::MainWindow main;
    main.show();
    return app.exec();
}
// #include <QApplication>
// #include "c_space_manipulator/views/user_config_view.hpp"

// int main(int argc, char **argv)
// {
//     QApplication app(argc, argv);

//     cspace_manipulator::UserConfigView w;
//     w.setWindowTitle("UserConfigView - standalone");
//     w.resize(800, 600);
//     w.show();

//     return app.exec();
// }
