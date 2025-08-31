#ifndef CSPACE_MANIPULATOR_LINK_CONFIG_VIEW_HPP 
#define CSPACE_MANIPULATOR_LINK_CONFIG_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include "c_space_manipulator/models/link_config_model.hpp"


namespace cspace_manipulator
{
class LinkConfigView : public QWidget
{
    Q_OBJECT
    public:
    LinkConfigView(int link_num, QWidget *parent = nullptr);
    ~LinkConfigView()=default;

    LinkConfigModel getModel() const;

    private:
    QComboBox* joint_drop_down_;
    QLineEdit* link_length_edit_ ;
    QLineEdit* initial_orientation_edit_ ;
    QLineEdit* min_degree_edit_ ;
    QLineEdit* max_degree_edit_ ;
    QLineEdit* max_extension_edit_ ;
};
}

#endif