#ifndef CSPACE_MANIPULATOR_MODELS_HPP
#define CSPACE_MANIPULATOR_MODELS_HPP

#include <QString>
#include <Eigen/Dense>
#include <string>

struct linkConfig
{
    std::string joint_type;
    double link_length;
    double initial_orientation;
    double min_degree;
    double max_degree;
    double max_extension;
}


struct linkModel
{
    linkConfig config;
    Eigen::Vector2d start_pt;
    Eigen::Vector2d end_pt;
    double orientation;
    double extension;
};

struct manipulatorModel
{
    std::vector<linkModel> links;

};

struct cspaceModel
{

};


struct obstacleModel
{

};






#endif
