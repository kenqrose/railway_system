#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
	
        // 判断用户名和密码是否正确，如果错误则弹出警告对话框
        if(ui->accountEdit->text().trimmed() == tr("123")
               && ui->keyEdit->text() == tr("123456"))
        {
           accept();
        } else {
           QMessageBox::warning(this, tr("Waring"),
                                 tr("user name or password error!"),
                                 QMessageBox::Yes);
           // 清空内容并定位光标
           //ui->accountEdit->clear();
           ui->keyEdit->clear();
           ui->keyEdit->setFocus();
        }
}

