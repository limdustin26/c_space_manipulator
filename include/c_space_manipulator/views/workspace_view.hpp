#ifndef CSPACE_MANIPULATOR_WORKSPACE_VIEW_HPP
#define CSPACE_MANIPULATOR_WORKSPACE_VIEW_HPP

#include <QWidget>

namespace cspace_manipulator
{
    class WorkspaceView : public QWidget
    {
        Q_OBJECT
        public:
        WorkspaceView(manipulatorModel* model, QWidget* parent=nullptr);
    };
}

#endif

