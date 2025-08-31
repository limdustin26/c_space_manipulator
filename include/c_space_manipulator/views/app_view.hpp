#include <QWidget>

namespace cspace_manipulator
{
class AppView(): public QWidget
{
    Q_OBJECT
    public:
    AppView(QWidget* parent=nullptr);
    ~AppView()=default;
};
}