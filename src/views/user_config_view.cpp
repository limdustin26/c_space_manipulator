#include "c_space_manipulator/views/user_config_view.hpp"

namespace cspace_manipulator
{
UserConfigView::UserConfigView(QWidget* parent) : QWidget(parent)
{
    // Scroll Area
    QScrollArea* scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);
    scroll_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Scroll Content
    scroll_content_ = new QWidget();
    scroll_content_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* scroll_layout = new QVBoxLayout(scroll_content_);

    // Link Content
    links_layout_ = new QVBoxLayout();
    links_layout_ ->setAlignment(Qt::AlignTop);
    scroll_layout->addLayout(links_layout_);

    // Add/Remove Latest Link Button
    QPushButton* add_button = new QPushButton(tr("add"),this);
    QPushButton* remove_button = new QPushButton(tr("remove"),this);
    connect(add_button, &QPushButton::clicked, this, &UserConfigView::addLinkConfig);
    connect(remove_button, &QPushButton::clicked, this, &UserConfigView::removeLinkConfig);

    // Create Button
    QPushButton* create_button = new QPushButton(tr("Create"), this);
    connect(create_button, &QPushButton::clicked, this, &UserConfigView::createManipulatorModel);

    // Button Layout
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addWidget(add_button);
    button_layout->addWidget(remove_button);
    scroll_layout->addLayout(button_layout);

    scroll_content_->setLayout(scroll_layout);
    scroll_area->setWidget(scroll_content_);

    // User Config Layout
    QVBoxLayout* user_config_layout = new QVBoxLayout(this);
    user_config_layout->addWidget(scroll_area);

    QHBoxLayout* create_button_layout = new QHBoxLayout();
    create_button_layout->addStretch();
    create_button_layout->addWidget(create_button);
    user_config_layout->addLayout(create_button_layout);

    setLayout(user_config_layout);

    // By default add 2 Links
    addLinkConfig();
    addLinkConfig();

}

void UserConfigView::addLinkConfig()
{
    // Invalid if max number of link is reached
    if(link_config_views_.size() >= max_link_num_)
    {
        // Warn Message Pop Up
        QMessageBox::warning(
            this,
            tr("Maximum Links Reached"),
            tr("Cannot exceed maximum link number %1").arg(max_link_num_)
        );
        return;
    }

    // Create new link
    int new_index = link_config_views_.size() + 1;
    // LinkConfigView* new_link_view = new LinkConfigView(new_index, this);
    LinkConfigView* new_link_view = new LinkConfigView(new_index, scroll_content_);
    new_link_view->setMinimumHeight(48);
    link_config_views_.push_back(new_link_view);

    // Add to layout
    links_layout_->addWidget(new_link_view);

    // Force geometry/layout update so QScrollArea and tab paint correctly
    scroll_content_->adjustSize();
    this->updateGeometry();
    this->update();

    // find the scroll area that wraps scroll_content_ and ensure the new widget is visible
    QScrollArea* sa = this->findChild<QScrollArea*>();
    if (sa && sa->widget() == scroll_content_)
    {
        sa->widget()->adjustSize();
        sa->updateGeometry();
        sa->ensureWidgetVisible(new_link_view);
    }

}

void UserConfigView::removeLinkConfig()
{
    if(link_config_views_.size() == 0)
    {
        // Warn Message Pop Up
        QMessageBox::warning(
            this,
            tr("No Links"),
            tr("There are no Links to remove !")
        );
        return;
    }

    // Remove link from layout
    LinkConfigView* last_link = link_config_views_.back();
    links_layout_->removeWidget(last_link);

    // Remove link from memory
    last_link->deleteLater();
    link_config_views_.pop_back();

}

void UserConfigView::createManipulatorModel()
{
    std::vector<linkConfig> link_configs;
    link_configs.reserve(link_config_views_.size());

    for (auto* link_config_view : link_config_views_)
    {
        link_configs.push_back(link_config_view->getConfig());  // convert UI → plain data
    }

    // create model
    manipulator_controller_.setLinks(link_configs);
    if(!manipulator_controller_.createManipulator(manipulator_model_))
    {
        std::cerr<<"[ERROR] Cannot Create Manipulator !"<<std::endl;
        // Warn Message Pop Up
        QMessageBox::warning(
            this,
            tr("Error"),
            tr("Cannot Create Manipulator !")
        );
        return;
    }
    std::cout<<"[INFO] Manipulator created !"<<std::endl;

    // emit signal to switch tab to C-space in Main Window
    emit cspaceTabRequested(manipulator_model_);
}

} // end of namespace
