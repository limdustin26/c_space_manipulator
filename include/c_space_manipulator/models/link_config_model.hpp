#include <QString>

struct LinkConfigModel
{
    QString joint_type;
    double link_length;
    double initial_orientation;
    double min_degree;
    double max_degree;
    double max_extension;
};