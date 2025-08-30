#include <QWidget>

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