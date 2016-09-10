#include "mainwindow.h"
#include <QtWidgets\QApplication>
#include "login.h"
#include"info.h"
//#include <iostream>
//#include <string>
//#include "Class_MySQL_API.h"
//#include "Class_User.h"
//#include "Class_Passenger.h"
//#include "Class_Admin.h"
//#include "Class_UFactory.h"

using namespace std;

extern shared_ptr<UFactory> user_ptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//string user("root");
	//string pswd("root");
	//string host("localhost");
	//string table("railway");
	//unsigned int port = 3306;

	//sql_ptr mysql_ptr = Create_MySQL_API(user, pswd, host, table, port);
		MainWindow w;
	   //login dlg;
	    w.show();
	   //info inf;
	    w.setWindowOpacity(1);                          //Í¸Ã÷¶È
	    //w.setWindowFlags(Qt::FramelessWindowHint);    //È¥µô±ß¿ò
	    w.setAttribute(Qt::WA_TranslucentBackground);
		return a.exec();
}

