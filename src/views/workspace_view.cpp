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

            QPointF start(origin.x() + link.start_pt.x(),
                          origin.y() - link.start_pt.y());
            QPointF end(origin.x() + link.end_pt.x(),
                        origin.y() - link.end_pt.y());

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
} // end of namespace
