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

        private:
        RobotManipulatorModel* robot_manipulator_widget_;
        QTabWidget* tabs_;

    };

    class RobotManipulatorWidget : public QWidget
    {
        Q_OBJECT
        public:
        RobotManipulatorWidget(QWidget* parent=nullptr);
        ~RobotManipulatorWidget()=default;
    };
}