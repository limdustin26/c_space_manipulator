#include "c_space_manipulator/views/link_config_view.hpp"

namespace cspace_manipulator{
LinkConfigView::LinkConfigView(int link_num,QWidget *parent): QWidget(parent)
{
    // Common Labels
    QLabel* link_name_label = new QLabel(tr("Link ") + QString::number(link_num), this);
    QLabel* joint_type_label = new QLabel(tr("Joint Type"), this);
    QLabel* link_length_label = new QLabel(tr("Link Length"), this);
    QLabel* initial_orientation_label = new QLabel(tr("Initial Orientation"), this);

    // Revolute Labels
    QLabel* min_degree_label = new QLabel(tr("Min Degree"), this);
    QLabel* max_degree_label = new QLabel(tr("Max Degree"), this);

    // Prismatic Labels
    QLabel* max_extension_label = new QLabel(tr("Max Extension"), this);

    // Joint Drop Down
    QComboBox* joint_drop_down_ = new QComboBox(this);
    joint_drop_down_->addItem(tr("revolute"));   // default option
    joint_drop_down_->addItem(tr("prismatic"));

    // Line Edits
    QLineEdit* link_length_edit_ = new QLineEdit(this);
    link_length_edit_->setValidator(new QDoubleValidator(0.0, 6.0, 2, this));
    link_length_edit_->setPlaceholderText(tr("max = 6"));

    QLineEdit* initial_orientation_edit_ = new QLineEdit(this);

    QLineEdit* min_degree_edit_ = new QLineEdit(this);
    QLineEdit* max_degree_edit_ = new QLineEdit(this);

    QLineEdit* max_extension_edit_ = new QLineEdit(this);

    // Layout
    QGridLayout* grid = new QGridLayout(this);

    // Row 0: link name (top left)
    grid->addWidget(link_name_label, 0,0,1,2); // row 0 column 0 rowspan 1 columnspan 2
    grid->addWidget(joint_type_label, 1,0);
    grid->addWidget(joint_drop_down_, 1,1);
    grid->addWidget(link_length_label, 1,2);
    grid->addWidget(link_length_edit_, 1,3);
    grid->addWidget(initial_orientation_label, 2,0);
    grid->addWidget(initial_orientation_edit_, 2,1);
    grid->addWidget(min_degree_label, 2,2);
    grid->addWidget(min_degree_edit_, 2,3);
    grid->addWidget(max_degree_label, 2,4);
    grid->addWidget(max_degree_edit_, 2,5);
    grid->addWidget(max_extension_label, 2,2);
    grid->addWidget(max_extension_edit_, 2,3);

    // Initially hide joint-specific labels
    min_degree_label->hide();
    min_degree_edit_->hide();
    max_degree_label->hide();
    max_degree_edit_->hide();
    max_extension_label->hide();
    max_extension_edit_->hide();

    // Event on joint drop down selection
    connect(joint_drop_down_, &QComboBox::currentTextChanged, this, [=](const QString &text)
    {
        if(text == tr("revolute"))
        {
            min_degree_label->show();
            min_degree_edit_->show();
            max_degree_label->show();
            max_degree_edit_->show();
            max_extension_label->hide();
            max_extension_edit_->hide();
        }

        else if(text == tr("prismatic"))
        {
            max_extension_label->show();
            max_extension_edit_->show();
            min_degree_label->hide();
            min_degree_edit_->hide();
            max_degree_label->hide();
            max_degree_edit_->hide();
        }
    }
    );

    setLayout(grid);

}

linkModel LinkConfigView::getModel() const
{
    linkModel model;
    model.joint_type = joint_drop_down_->currentText();
    model.link_length = link_length_edit_->text().toDouble();
    model.initial_orientation = initial_orientation_edit_->text().toDouble();

    if(model.joint_type == tr("revolute"))
    {
        model.max_degree = max_degree_edit_->text().toDouble();
        model.min_degree = min_degree_edit_->text().toDouble();
        model.max_extension = 0.0;
    }

    else if (model.joint_type == tr("prismatic"))
    {
        model.max_extension = max_extension_edit_->text().toDouble();
        model.min_degree = 0.0;
        model.max_degree = 0.0;
    }
    return model;
}
} // end of namespace