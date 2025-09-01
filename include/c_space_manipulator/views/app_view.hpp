#ifndef CSPACE_MANIPULATOR_APP_VIEW_HPP
#define CSPACE_MANIPULATOR_APP_VIEW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include "c_space_manipulator/models/models.hpp"
#include "c_space_manipulator/views/workspace_view.hpp"

namespace cspace_manipulator
{
class AppView: public QWidget
{
    Q_OBJECT
    public:
    AppView(QWidget* parent=nullptr);
    ~AppView()=default;

    void parseManipulatorModel(const manipulatorModel &model);

    private:
    WorkspaceView* ws_view_;
    // CSpaceView* cspace_view_;
};
}

#endif
