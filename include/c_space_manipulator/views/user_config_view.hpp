#include <QWidget>
#include "c_space_manipulator/views/link_config_view.hpp"

namespace cspace_manipulator
{
class UserConfigView : public QWidget
{
    Q_OBJECT
    public:
    UserConfigView(QWidget *parent = nullptr);
    ~UserConfigView();

};
}