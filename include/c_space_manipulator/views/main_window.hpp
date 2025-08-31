#ifndef CSPACE_MANIPULATOR_MAIN_WINDOW_HPP 
#define CSPACE_MANIPULATOR_MAIN_WINDOW_HPP

#include <QWidget>
#include <QMainWindow>
#include <QTabWidget>
#include "c_space_manipulator/views/user_config_view.hpp"

namespace cspace_manipulator
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        public:
        MainWindow();
        ~MainWindow()=default;

    };
} // end of namespace

#endif