#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "c_space_manipulator/views/link_config_view.hpp"

namespace cspace_manipulator
{
class UserConfigView : public QWidget
{
    Q_OBJECT
    public:
    UserConfigView(QWidget *parent = nullptr);
    ~UserConfigView();

    private:
    std::vector<LinkConfigView*> link_config_list_;
    QVBoxLayout* links_layout_
    int max_link_num_ = 10;

    private slots:
    void addLinkConfig();
    void removeLinkConfig();
    void updateManipulatorModel();

};
}