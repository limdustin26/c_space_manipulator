#ifndef CSPACE_MANIPULATOR_MANIPULATOR_CONTROLLER_HPP
#define CSPACE_MANIPULATOR_MANIPULATOR_CONTROLLER_HPP

#include "c_space_manipulator/models/models.hpp"

namespace cspace_manipulator
{
class manipulatorController
{
    public:
    manipulatorController()=default;
    ~manipulatorController()=default;

    void setLinks(std::vector<linkConfig> link_configs );
    bool createManipulator(&manipulatorModel model);

    private:
    std::vector<LinkConfigView*>  link_configs_;
}


} // end of namespace cspace_manipulator


#endif
