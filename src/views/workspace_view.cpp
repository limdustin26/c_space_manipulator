#include "c_space_manipulator/views/workspace_view.hpp"

namespace cspace_manipulator
{
    WorkspaceView::WorkspaceView(QWidget* parent): QWidget(parent)
    {
        setMinimumSize(400, 400);
    }

    void WorkspaceView::setManipulatorModel(const manipulatorModel &model)
    {
        manipulator_model_ = model;
        update();
    }

    void WorkspaceView::paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPointF origin(width() / 2.0, height() / 2.0);

        for (size_t i = 0; i < manipulator_model_.links.size(); ++i)
        {
            const auto& link = manipulator_model_.links[i];

            QPointF start(origin.x() + (link.start_pt.x() / resolution_),
                          origin.y() - (link.start_pt.y() / resolution_));
            QPointF end(origin.x() + (link.end_pt.x() / resolution_),
                        origin.y() - (link.end_pt.y() / resolution_));

            // Draw link
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(start, end);

            // Draw joints
            painter.setBrush(Qt::blue);
            painter.drawEllipse(start, 6, 6);

            painter.setBrush(Qt::red);
            painter.drawEllipse(end, 6, 6);
        }
    }

    void WorkspaceView::mousePressEvent(QMouseEvent* event)
    {
        QPointF click_pos = event->pos();
        QPointF origin(width() / 2.0, height() / 2.0);

        // loop over all joints
        for (size_t i = 0; i < manipulator_model_.links.size(); ++i)
        {
            const auto& link = manipulator_model_.links[i];
            QPointF joint_pos(origin.x() + (link.start_pt.x() / resolution_),
                            origin.y() - (link.start_pt.y() / resolution_));

            if (QLineF(click_pos, joint_pos).length() < 10) // clicked near joint
            {
                selected_joint_ = i;
                drag_start_pos_ = click_pos;
                break;
            }
        }
    }

    void WorkspaceView::mouseMoveEvent(QMouseEvent* event)
    {
        if (selected_joint_ < 0) return;

        const auto& link = manipulator_model_.links[selected_joint_];

        QPointF origin(width() / 2.0, height() / 2.0);
        QPointF joint_pos(origin.x() + (link.start_pt.x() / resolution_),
                        origin.y() - (link.start_pt.y() / resolution_));

        QPointF mouse_pos = event->pos();
        QPointF delta = mouse_pos - joint_pos;

        if (link.config.joint_type == "revolute")
        {
            // angle relative to previous link or x-axis
            double angle = std::atan2(-delta.y(), delta.x()); // note Y flipped
            // clamp to min/max angle
            angle = std::max(link.config.min_degree * M_PI/180.0, std::min(link.config.max_degree * M_PI/180.0, angle));
            manipulator_model_.links[selected_joint_].orientation = angle * 180.0/M_PI;

            // recompute end point based on length and new angle
            double l = link.config.link_length;
            manipulator_model_.links[selected_joint_].end_pt = link.start_pt + Eigen::Vector2d(l * cos(angle), l * sin(angle));
        }
        else if (link.config.joint_type == "prismatic")
        {
            // project mouse delta onto link axis
            Eigen::Vector2d axis = link.end_pt - link.start_pt;
            double axis_len = std::sqrt(axis.x()*axis.x() + axis.y()*axis.y());
            Eigen::Vector2d axis_unit = axis / axis_len;

            double proj = (delta.x() * axis_unit.x() + delta.y() * axis_unit.y()) * resolution_;
            // clamp extension
            proj = std::max(0.0, std::min(link.config.max_extension, proj));

            manipulator_model_.links[selected_joint_].end_pt = link.start_pt + axis_unit * proj;
        }

        update(); // repaint
    }

    void WorkspaceView::mouseReleaseEvent(QMouseEvent*)
    {
        selected_joint_ = -1;
    }


} // end of namespace
