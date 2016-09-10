#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "info.h"
#include "login.h"
#include <qdebug.h>
#include <QMessageBox>
#include <QTextCodec>  

using namespace std;

shared_ptr<UFactory> user_ptr;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	//ui->action->setVisible(false);
	//ui->action_2->setVisible(false);
	//ui->action_3->setVisible(false);
	//ui->action_4->setVisible(false);
	//ui->action_5->setVisible(false);
	//ui->menu->hide();
	//ui->menuBar->hide();

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	//connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(getdeparture())); 
	//connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(getterminal()));
	//connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(getdeparture_date()));
	//connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(gettrain_type()));
	connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(query_train()));
	

	ui->dateEdit->setCalendarPopup(true);
	ui->dateEdit->setDate(QDate::currentDate());
	ui->checkBox->setChecked(true);
	ui->checkBox_2->setChecked(true);
	ui->checkBox_3->setChecked(true);
	ui->checkBox_4->setChecked(true);
	ui->checkBox_5->setChecked(true);

	ui->tableWidget->setColumnCount(7);
	ui->tableWidget->setRowCount(0);
	QStringList headers;
	headers<<QString::fromLocal8Bit("车次")<<QString::fromLocal8Bit("始发站")<<QString::fromLocal8Bit("终点站");
	headers<<QString::fromLocal8Bit("发车时间")<<QString::fromLocal8Bit("运行时间")<<QString::fromLocal8Bit("硬座余票");
	headers<<QString::fromLocal8Bit("卧铺余票");
	ui->tableWidget->setHorizontalHeaderLabels(headers);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); 

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
      login dlg;
      //dlg =new login;
      dlg.show();
      if (dlg.exec() == QDialog::Accepted)
      {
              info *inf;
              inf=new info;
              inf->show();
       //  return a.exec();
      }
}

void MainWindow::query_train()
{
	cout << "inside query train " << endl;
	string departure = getdeparture();
	string terminal = getterminal();
	Date departure_date=getdeparture_date();
	int train_type = gettrain_type();
	int carriage_type = getcarriage_type();
	if(departure.size() == 0 || terminal.size() == 0)
	{
		QMessageBox::warning(this, tr("Waring"),QString::fromLocal8Bit("请重新输入查询信息"),QMessageBox::Yes);
		ui->lineEdit->setFocus();
	}
	else
	{
		cout << "all inputs are right" << endl;
	sql_ptr mysql_ptr=Create_MySQL_API();
	if(mysql_ptr->Connection()==true)
	{
		cout << "DataBase Connection Succeed" << endl;
		vector<Train> train_info = user_ptr->find_train(mysql_ptr, departure, terminal, departure_date, carriage_type, train_type);
		
		//int rowIndex = ui->tableWidget->rowCount();
		//ui->tableWidget->setRowCount(rowIndex + train_info.size());//增加足够的行数

 
		cout << "get train info from database succeed, there are totally " << train_info.size() << " trains." << endl;
		if(train_info.size()==0)
		{
			QMessageBox::warning(this, tr("Waring"),QString::fromLocal8Bit("没有符合条件的列车"),QMessageBox::Yes);
		}
		for(int i=0;i<train_info.size();i++)
		{
			int row = ui->tableWidget->rowCount();  
			ui->tableWidget->insertRow(row); 
			for(int j=0;j<7;j++)
			{
				addItemContent(i, 0, s2q(train_info[i].cvt2serial()));
				addItemContent(i, 1, s2q(train_info[i].get_departure()));
				addItemContent(i, 2, s2q(train_info[i].get_terminal()));
				addItemContent(i, 3, s2q(train_info[i].get_dep_time()));
				addItemContent(i, 4, s2q(train_info[i].get_run_time()));
				addItemContent(i, 5, s2q(train_info[i].get_seat_remain()));
				addItemContent(i, 6, s2q(train_info[i].get_berth_remain()));
			}
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Waring"),tr("Database Connection Failed!"),QMessageBox::Cancel);
	}
	}


}

string MainWindow::getdeparture()
{
	string a = string(ui->lineEdit->text().toLocal8Bit());
	//if(a.size() == 0)
	//{
	//	QMessageBox::warning(this, tr("Waring"),tr("Please input departure station!"),QMessageBox::Yes);
	//}
	return a;
}

string MainWindow::getterminal()
{
	string a = string(ui->lineEdit_2->text().toLocal8Bit());
	//if(a.size() == 0)
	//{
	//	QMessageBox::warning(this, tr("Waring"),tr("Please input terminal station!"),QMessageBox::Yes);
	//}
	return a;
}

Date MainWindow::getdeparture_date()
{
	QDate d = ui->dateEdit->date();
	Date date(d.year(),d.month(), d.day());
	date.show();
	return date;
}

int MainWindow::gettrain_type()//0全部1高铁2特快3快速4高铁+特快5高铁+快速6特快+快速
{
	if(ui->checkBox->isChecked())
	{
		if(ui->checkBox_2->isChecked())
		{
			if(ui->checkBox_3->isChecked())
			{
				cout << "all the train" << endl;
				return 0;
			}
			else
			{
				return 4;
			}
		}
		else
		{
			if(ui->checkBox_3->isChecked())
			{
				return 5;
			}
			else
			{
				return 1;
			}
		}
	}
	else
	{
		if(ui->checkBox_2->isChecked())
		{
			if(ui->checkBox_3->isChecked())
			{
				return 6;
			}
			else
			{
				return 2;
			}
		}
		else
		{
			if(ui->checkBox_3->isChecked())
			{
				return 3;
			}
			else
			{
				cout << "no choice ,default all the train" << endl;
				return 0;
			}
		}
	}
}

int MainWindow::getcarriage_type()//0全部1硬座2卧铺
{
	if(ui->checkBox_4->isChecked())
	{
		if(ui->checkBox_5->isChecked())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if(ui->checkBox_5->isChecked())
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
}

void MainWindow::addItemContent(int row, int column, QString content)
{
      QTableWidgetItem *item = new QTableWidgetItem (content);
      ui->tableWidget->setItem(row, column, item);
}
