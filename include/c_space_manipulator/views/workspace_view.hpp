#ifndef CSPACE_MANIPULATOR_WORKSPACE_VIEW_HPP
#define CSPACE_MANIPULATOR_WORKSPACE_VIEW_HPP

#include <QWidget>
#include <QPainter>
#include "c_space_manipulator/models/models.hpp"

namespace cspace_manipulator
{
    class WorkspaceView : public QWidget
    {
        Q_OBJECT
        public:
        WorkspaceView(QWidget* parent=nullptr);
        void setManipulatorModel(const manipulatorModel &model);
        void paintEvent(QPaintEvent*);

        private:
        manipulatorModel manipulator_model_;
    };
}

#endif
