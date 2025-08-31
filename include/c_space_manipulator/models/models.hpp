#ifndef CSPACE_MANIPULATOR_MODELS_HPP
#define CSPACE_MANIPULATOR_MODELS_HPP

#include <QString>

struct linkModel
{
    QString joint_type;
    double link_length;
    double initial_orientation;
    double min_degree;
    double max_degree;
    double max_extension;
};

struct manipulatorModel
{
    std::vector<linkModel*> data;
};

struct cspaceModel
{

};


struct obstacleModel
{

};






#endif