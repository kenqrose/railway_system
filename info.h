#ifndef INFO_H
#define INFO_H

//#include <QMainWindow>
#include <QtWidgets\qmainwindow.h>

namespace Ui {
class info;
}

class info : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit info(QWidget *parent = 0);
    ~info();
    
private:
    Ui::info *ui;
};

#endif // INFO_H
