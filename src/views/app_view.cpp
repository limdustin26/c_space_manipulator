#include "c_space_manipulator/views/app_view.hpp"

namespace cspace_manipulator
{
AppView::AppView(QWidget* parent): QWidget(parent) 
{
    // Widgets
    WorkspaceView* ws_view = new WorkspaceView(,this);
    CSpaceView* cspace_view = new CSpaceView();

    // App Layout
    QHBoxLayout* app_layout = QHBoxLayout(this);
    app_layout->addWidget(ws_view);
    app_layout->addWidget(cspace_view);

    setLayout(app_layout);
}

}