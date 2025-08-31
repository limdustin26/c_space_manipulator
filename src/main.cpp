#include "c_space_manipulator/views/main_window.hpp"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cspace_manipulator::MainWindow main;
    main.show();
    return app.exec();
}