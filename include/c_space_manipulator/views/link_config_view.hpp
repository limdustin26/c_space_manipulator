#include <QWidget>

namespace cspace_manipulator
{
class LinkConfigView : public QWidget
{
    Q_OBJECT
    public:
    LinkConfigView(QWidget *parent = nullptr);
    ~LinkConfigView();
};
}