#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
//#include <QMainWindow>
#include <QtWidgets\qmainwindow.h>
#include <string>
#include <iostream>
#include "Class_Time.h"
#include "Class_UFactory.h"
#include "Class_MySQL_API.h"
#include "Class_Train.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void check_all();
	int gettrain_type();
	string getdeparture();
	string getterminal();
	Date getdeparture_date();
	int getcarriage_type();
	void MainWindow::addItemContent(int row, int column, QString content);
	inline QString s2q(const string &s){return QString(QString::fromLocal8Bit(s.c_str()));}

signals:
    
private slots:
    void on_action_triggered();
	void query_train();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H