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
    joint_drop_down_ = new QComboBox(this);
    joint_drop_down_->addItem(tr("revolute"));   // default option
    joint_drop_down_->addItem(tr("prismatic"));

    // Line Edits
    link_length_edit_ = new QLineEdit(this);
    link_length_edit_->setValidator(new QDoubleValidator(0.0, 6.0, 2, this));
    link_length_edit_->setPlaceholderText(tr("max = 6.00"));

    initial_orientation_edit_ = new QLineEdit(this);
    initial_orientation_edit_->setPlaceholderText(tr("-180.0 to 180.0"));

    min_degree_edit_ = new QLineEdit(this);
    min_degree_edit_->setPlaceholderText(tr("-180.0 to 180.0"));
    max_degree_edit_ = new QLineEdit(this);
    max_degree_edit_->setPlaceholderText(tr("-180.0 to 180.0"));

    max_extension_edit_ = new QLineEdit(this);
    max_extension_edit_->setPlaceholderText(tr("max = 3.0"));

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

    // Initially hide prismatic labels
    min_degree_label->show();
    min_degree_edit_->show();
    max_degree_label->show();
    max_degree_edit_->show();
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

linkConfig LinkConfigView::getConfig()
{
    linkConfig config;
    config.joint_type = joint_drop_down_->currentText().toStdString();
    config.link_length = std::clamp(0.0, 6.0, link_length_edit_->text().toDouble());
    link_length_edit_->setText(QString::number(config.link_length, 'f', 2)); // update input text if exceed
    config.initial_orientation = std::clamp(-180.0,180.0, initial_orientation_edit_->text().toDouble());
    initial_orientation_edit_->setText(QString::number(config.initial_orientation, 'f', 2));

    if(config.joint_type == "revolute")
    {
        config.max_degree = std::clamp(-180.0,180.0,max_degree_edit_->text().toDouble());
        config.min_degree = std::clamp(-180.0,180.0,min_degree_edit_->text().toDouble());
        max_degree_edit_->setText(QString::number(config.max_degree, 'f', 2)); // update input text if exceed
        min_degree_edit_->setText(QString::number(config.min_degree, 'f', 2)); // update input text if exceed
        config.max_extension = 0.0;
    }

    else if (config.joint_type == "prismatic")
    {
        config.max_extension = std::clamp(0.0,3.0,max_extension_edit_->text().toDouble());
        max_extension_edit_->setText(QString::number(config.max_extension, 'f', 2)); // update input text if exceed
        config.min_degree = 0.0;
        config.max_degree = 0.0;
    }

    return config;

}


} // end of namespace
