#ifndef USER_H_
#define USER_H_
#include "Class_Time.h"
#include <mysql.h>
#include "Class_MySQL_API.h"
#include "Class_Train.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <regex>//使用正则表达式
using namespace std;

class User
{
private:
	string account;//用户账户名：(6,14]位，可包含数字，字母大小写，下划线
	string password;//用户密码：(6,10]位，可包含数字，字母大小写，下划线
	int status;//用户所在用户组，0为管理员，1为旅客,2为无此用户，3为未检查状态
public:
	User(){};//构造函数，对应没有登录的情况
	User(string& a, string& p):account(a), password(p), status(3){};//构造函数，用于前期账户处理
	User(User& u):account(u.account), password(u.password), status(3){};//复制构造函数
	virtual ~User(){};//虚析构函数
	string& get_account(){return account;}
	int getstatus(){return status;}//显示用户所在用户组
	void check_account(sql_ptr& );//检查账户所在用户组
	bool check_password(sql_ptr& );//检查密码
	void register_account(sql_ptr& );//注册账号
	bool change_password(sql_ptr& );//修改密码
	int check_acc_repetition(sql_ptr&);//用于在创建旅客用户时检查用户是否已存在
	//vector<Train> find_train(sql_ptr&, string&, string&, Date& = Date(), int = 0, int = 0);//查找车辆信息（先不考虑根据时间筛选）
	friend class Admin;
	friend class Passenger;
	virtual void show(){cout << "This is User" << endl;}
	//virtual bool add_train() = 0;
};

#endif