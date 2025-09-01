#include "c_space_manipulator/controllers/manipulator_controller.hpp"

namespace cspace_manipulator
{
    void manipulatorController::setLinks(std::vector<linkConfig> link_configs )
    {
        link_configs_ = link_configs;
    }

    bool manipulatorController::createManipulator(manipulatorModel& model)
    {
        try
        {
            manipulatorModel new_model;
            Eigen::Vector2d start_pt(0.0, 0.0);
            for(auto link_config: link_configs_)
            {
                linkModel link;
                link.config = link_config;
                link.orientation = link.config.initial_orientation; // convert to rad maybe
                link.start_pt = start_pt;
                link.end_pt = Eigen::Vector2d(link.start_pt.x() + link.config.link_length * cos(link.orientation),
                                              link.start_pt.y() + link.config.link_length * sin(link.orientation));
                link.extension = 0.0;
                start_pt = link.end_pt;
                new_model.links.emplace_back();
            }

            model = new_model;
            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

} // end of namespace
