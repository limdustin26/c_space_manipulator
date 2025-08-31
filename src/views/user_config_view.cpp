#include "c_space_manipulator/views/user_config_view.hpp"

namespace cspace_manipulator
{
UserConfigView::UserConfigView(QWidget* parent) : QWidget(parent)
{
    // Scroll Area
    QScrollArea* scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);

    // Scroll Content
    QWidget* scroll_content = new QWidget(this);
    QVBoxLayout* scroll_layout = new QVBoxLayout(scroll_content);

    // Link Content
    links_layout_ = new QVBoxLayout();
    links_layout_ ->setAlignment(Qt::AlignTop);
    scroll_layout->addLayout(links_layout_);

    // Add/Remove Latest Link Button
    QPushButton* add_button = new QPushButton(tr("add"),this);
    QPushButton* remove_button = new QPushButton(tr("remove"),this);
    connect(add_button, &QPushButton::clicked, this, &UserConfigView::addLinkConfig);
    connect(remove_button, &QPushButton::clicked, this, &UserConfigView::removeLinkConfig);

    // Button Layout
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addWidget(add_button);
    button_layout->addWidget(remove_button);
    scroll_layout->addLayout(button_layout);

    scroll_content->setLayout(scroll_layout);
    scroll_area->setWidget(scroll_content);

    // User Config Layout
    QVBoxLayout* user_config_layout = new QVBoxLayout(this);
    user_config_layout->addWidget(scroll_area);
    setLayout(user_config_layout);

    // By default add 2 Links
    addLinkConfig();
    addLinkConfig();

}

void UserConfigView::addLinkConfig()
{
    // Invalid if max number of link is reached
    if(link_config_list_.size() >= max_link_num_)
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
    int new_index = link_config_list_.size() + 1;
    LinkConfigView* new_link = new LinkConfigView(new_index, this);
    link_config_list_.push_back(new_link);

    // Add to layout
    links_layout_->addWidget(new_link);

}

void UserConfigView::removeLinkConfig()
{
    if(link_config_list_.size() == 0)
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
    LinkConfigView* last_link = link_config_list_.back();
    links_layout_->removeWidget(last_link);

    // Remove link from memory
    last_link->deleteLater();
    link_config_list_.pop_back();

}

} // end of namespace