#ifndef CSPACE_MANIPULATOR_USER_CONFIG_VIEW_HPP
#define CSPACE_MANIPULATOR_USER_CONFIG_VIEW_HPP

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <iostream>

#include "c_space_manipulator/models/models.hpp"
#include "c_space_manipulator/views/link_config_view.hpp"
#include "c_space_manipulator/controllers/manipulator_controller.hpp"

namespace cspace_manipulator
{
class UserConfigView : public QWidget
{
    Q_OBJECT
    public:
    UserConfigView(QWidget *parent = nullptr);
    ~UserConfigView()=default;

    private:
    std::vector<LinkConfigView*> link_config_views_;
    manipulatorModel manipulator_model_;
    manipulatorController manipulator_controller_;
    QWidget* scroll_content_;
    QVBoxLayout* links_layout_;
    int max_link_num_ = 10;

    signals:
    void cspaceTabRequested(const manipulatorModel& model);

    private slots:
    void addLinkConfig();
    void removeLinkConfig();
    void createManipulatorModel();

};
}

#endif
