#include "c_space_manipulator/views/main_window.hpp"

cspace_manipulator::MainWindow()
{

    tabs_ = new QTabWidget(this);

    // Add User Config and C-Space Tab
    tabs_->addTab(new UserConfigView(), QObject::tr("User Configuration"));
    tabs_->addTab(new MainAppView(), QObject::tr("C-Space"));

    
    
    
    // Max 6 DoF
    // Default 2 DoF revolute

    // Create 2D RobotManipulator Widget with user config
    robot_manipulator_widget_ = new RobotManipulatorWidget(this, user_config);

    // Create C-Space Widget
    c_space_widget_ = new CSpaceWidget(this);

    // Create Obstacle Widget
    obstacle_widget_ = new ObstacleWidget(this)

    // Put to Layout

    
    

}