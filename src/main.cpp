#include "c_space_manipulator/gui.hpp"
#include "c_space_manipulator/robot_factory.hpp"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow main;
    main.show();
    return app.exec();
}