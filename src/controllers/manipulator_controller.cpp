#include "c_space_manipulator/controllers/manipulator_controller.hpp"

namespace cspace_manipulator
{
    void manipulatorController::setLinks(std::vector<LinkConfigView*> link_configs )
    {
        link_configs_ = link_configs;
    }

    bool manipulatorController::createManipulator(manipulatorModel& model)
    {
        manipulatorModel new_model;
        Eigen::Vector2d start_pt = Eigen::Vector2d((0.0, 0.0));
        for(auto link_config: link_configs_)
        {
            linkModel link;
            link.config = link_config;
            link.orientation = link.config.initial_orientation; // convert to rad maybe
            link.start_pt = start_pt;
            link.end_pt = (link.start_pt.x + link.config.link_length * cos(link.orientation),
                           link.start_pt.y + link.config.link_length * sin(link_orientation));
            link.extension = 0.0;
            start_pt = link.end_pt;
        }
    }

} // end of namespace
