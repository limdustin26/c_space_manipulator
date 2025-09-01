#include "c_space_manipulator/views/app_view.hpp"

namespace cspace_manipulator
{
AppView::AppView(QWidget* parent): QWidget(parent)
{
    // Widgets
    ws_view_ = new WorkspaceView(this);
    // cspace_view_ = new CSpaceView(this);

    ws_view_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // App Layout
    QHBoxLayout* app_layout = new QHBoxLayout(this);
    app_layout->addWidget(ws_view_);
    // app_layout->addWidget(cspace_view);

    setLayout(app_layout);
}

void AppView::parseManipulatorModel(const manipulatorModel &model)
{
    // set manipulator in ws_view
    ws_view_->setManipulatorModel(model);

}

}
