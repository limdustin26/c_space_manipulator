#ifndef CSPACE_MANIPULATOR_WORKSPACE_VIEW_HPP
#define CSPACE_MANIPULATOR_WORKSPACE_VIEW_HPP

#include <QWidget>
#include <QPainter>
#include "c_space_manipulator/models/models.hpp"
#include <cmath>
#include <QMouseEvent>


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
        double resolution_{0.02} ; // meter/pixel
        int selected_joint_ = -1;  // index of the joint being dragged
        QPointF drag_start_pos_;

        protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
    };
}

#endif
