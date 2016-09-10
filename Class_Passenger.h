#ifndef _PASSENGER_H_
#define _PASSENGER_H_
#include <iostream>
#include <string>
#include <vector>
#include "Class_Time.h"
#include "Class_User.h"
#include "Class_MySQL_API.h"
#include "Class_Train.h"
#include "Class_Seat.h"
#include "Class_UFactory.h"

using namespace std;

class Passenger:public UFactory
{
private:
	string account;//in User
	string password;//in User
	
	string name;
	int gender;
	Date birthday;
	string type_of_certificate;
	string id_card;
	string phone_number;
	int is_student;
	double balance;
public:
	//User u;
	Passenger(string&, string&, wstring&, int, Date&, string&, string&, string&, int, double);//通过完整信息构造用户
	Passenger(string& , string&, sql_ptr&);//通过用户名构造用户，并在数据库中搜索补全其他信息
	Passenger(User&, sql_ptr&);
	bool buy_ticket(Train&, Seat&, sql_ptr&, Date&, int buy_student);//买票，根据选择的座位号，buy_student为是否购买学生票的布尔值
	void show();//显示Passenger类成员变量
	bool create_deal(sql_ptr&, Train&, Seat&, Date&){return false;}//创建订单（在buy_ticket中直接使用db函数实现了这个功能）
	bool add_train(sql_ptr&, Train&){return false;}
	bool update(sql_ptr&);//更新修改后的数据
	bool top_up(sql_ptr&, double);//向电子钱包充值，double为充值金额
	double check_balance(){return balance;}
	//修改成员变量
	void set_name(string& n){name = n;}
	void set_gender(int g){gender = g;}
	void set_birthday(Date& d){birthday = d;}
	void set_tof(string& t){type_of_certificate = t;}
	void set_id(string& id){id_card = id;}
	void set_phone(string& p){phone_number = p;}
	void set_student(int s){is_student = s;}
};
#endif