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

            if ((i + 1) == manipulator_model_.links.size())
            {
                painter.setBrush(Qt::red);
                painter.drawEllipse(end, 6, 6);
            }

        }
    }

    void WorkspaceView::mousePressEvent(QMouseEvent* event)
    {
        // convert click to workspace coordinates
        Eigen::Vector2d origin(width()/2.0, height()/2.0);
        Eigen::Vector2d mouse_ws((event->pos().x() - origin.x()) * resolution_,
                                (origin.y() - event->pos().y()) * resolution_);

        for (size_t i = 0; i < manipulator_model_.links.size(); ++i)
        {
            const auto& link = manipulator_model_.links[i];
            Eigen::Vector2d joint_ws = link.end_pt;
            if ((mouse_ws - joint_ws).norm() < 5 * resolution_) // threshold in workspace units
            {
                selected_joint_ = i;
                drag_start_offset_ = joint_ws - mouse_ws; // store offset
                break;
            }
        }
    }

    void WorkspaceView::mouseMoveEvent(QMouseEvent* event)
    {
        if (selected_joint_ < 0) return;

        auto& link = manipulator_model_.links[selected_joint_];

        // Convert mouse position to workspace (meters)
        Eigen::Vector2d origin(width() / 2.0, height() / 2.0); // in pixels
        Eigen::Vector2d mouse_ws(
            (event->pos().x() - origin.x()) * resolution_,      // X in meters
            (origin.y() - event->pos().y()) * resolution_       // Y in meters (flip)
        );

        // Optional: account for initial drag offset to avoid snapping
        Eigen::Vector2d target_pos = mouse_ws + drag_start_offset_;

        if (link.config.joint_type == "revolute")
        {
            // vector from joint start to target
            Eigen::Vector2d delta = target_pos - link.start_pt;

            double angle = std::atan2(delta.y(), delta.x()); // angle in radians
            // clamp to min/max angles
            double min_rad = link.config.min_degree * M_PI / 180.0;
            double max_rad = link.config.max_degree * M_PI / 180.0;
            angle = std::max(min_rad, std::min(max_rad, angle));

            // store orientation in degrees if needed
            link.orientation = angle * 180.0 / M_PI;

            // recompute end point based on length
            double l = link.config.link_length;
            link.end_pt = link.start_pt + Eigen::Vector2d(l * std::cos(angle), l * std::sin(angle));
        }
        else if (link.config.joint_type == "prismatic")
        {
            // vector along current link
            Eigen::Vector2d axis = link.end_pt - link.start_pt;
            double axis_len = axis.norm(); if (axis_len < 1e-6) axis_len = 1e-6;
            // avoid divide by zero
            Eigen::Vector2d axis_unit = axis / axis_len;

            // project mouse delta onto link axis
            Eigen::Vector2d delta = target_pos - link.start_pt;
            double proj = delta.dot(axis_unit); // meters
            // clamp extension
            proj = std::max(0.0, std::min(link.config.max_extension, proj));

            // update end point
             double l = link.config.link_length;
            link.end_pt = link.start_pt + axis_unit * (proj+l);
        }

        // update next link start point if exists
        if (selected_joint_ + 1 < manipulator_model_.links.size())
            manipulator_model_.links[selected_joint_ + 1].start_pt = link.end_pt;

        update(); // repaint
    }


    void WorkspaceView::mouseReleaseEvent(QMouseEvent*)
    {
        selected_joint_ = -1;
    }


} // end of namespace
