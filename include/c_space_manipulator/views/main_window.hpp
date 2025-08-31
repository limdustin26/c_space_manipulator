#ifndef CSPACE_MANIPULATOR_MAIN_WINDOW_HPP 
#define CSPACE_MANIPULATOR_MAIN_WINDOW_HPP

#include <QWidget>
#include <QTabWidget>


namespace cspace_manipulator
{
    class MainWindow : public QWidget
    {
        Q_OBJECT
        public:
        MainWindow();
        ~MainWindow()=default;

    };
} // end of namespace

#endif