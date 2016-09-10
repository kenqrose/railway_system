#ifndef MYSQL_API_H_
#define MYSQL_API_H_
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Class_Time.h"
#include <mysql.h> 
#include "Class_Seat.h"

using namespace std;
//std::tr1::shared_ptr<MySQL_API> Create_MySQL_API(string&, string&, string&, string&, unsigned int);
//class Train;

class MySQL_API
{
private:
	const string user;
	const string pswd;
	const string host;
	const string table;
	unsigned int port;
	//MYSQL mysql_handle;
	//MYSQL_RES *mysql_result;
	//MYSQL_ROW mysql_row;
	//MYSQL_FIELD *mysql_field;
public:
	MYSQL mysql_handle;
	MYSQL_RES *mysql_result;
    MYSQL_ROW mysql_row;
    MYSQL_FIELD *mysql_field;
	MySQL_API(string&, string&, string&, string&, unsigned int);//构造 
	~MySQL_API(){mysql_close(&mysql_handle);}//析构
	bool Connection();
	int db_check_account(string& a);//从数据库检查用户所在组，0为管理员，1为旅客，2为无此用户，若为1或2，则说明此账户重复
	bool db_check_id_repetition(string&, string&);//检查身份证明信息是否重复
	bool db_check_pswd_admin(string&, string&);//从数据库检查管理员账户是否正确
	bool db_check_pswd_passenger(string&, string&);//从数据库检查旅客账户是否正确
	bool db_check_train_30min(string&, int);//检查当前时间是否离发车时间30分钟以上
	bool db_create_passenger(string&, string&, string&, int, Date&, string&, string&, string&, int, double = 0);//向数据库添加旅客账户
	bool db_create_admin(string&, string&, string&, int, Date&, string&, string&, string&, int);//向数据库添加管理员账户
	bool db_create_train();//向数据库添加列车数据
	bool db_create_seat_table(string&);//在数据库中创建座位表
	bool db_create_deal(string&, string&, string&, string&, Date&, Time&, Seat&, int, int, int = 0);//添加订单信息
	bool db_change_pswd_passenger(string&, string&);//连接数据库修改旅客密码
	bool db_change_pswd_admin(string&, string&);//连接数据库修改管理员密码
	bool db_add_train(string&, int, int, int, string&, string&, Date&, Time&, Time&, float, float);//添加车辆信息
	bool db_add_seat(string&, Seat&, string&, Date&);//在对应列车座位表中添加座位
	bool db_seat_sold(string&, Seat&, Date&);//检查座位是否已被占用
	bool db_update_passenger(string&, int, Date&, string&, string&, string&, int, double);//更新旅客用户信息
	bool db_update_train(string&, int, int, int, string&, string&, Date&, Time&, Time&, float, float);//更新车辆信息
	bool db_update_seat_remain(string&, int, Seat&, Date&);//更新座位剩余信息
	bool db_update_balance(string&, double);//更新用户电子钱包余额信息
	bool db_not_bought(string& account, string& serial, Date& departure_date, Seat& seat);//检查用户是否已购买此车车票
	bool db_remain_ticket(string& serial_number, int train_type, Date& departure_date, Seat& s);//检查所选车辆是否有余票
	bool db_delete_passenger(string& account);//从数据库删除旅客注册信息
	bool db_delete_train(string&, int);//从数据库删除列车信息
	bool db_delete_seat_table(string& serial_st);//从数据库中删除座位信息表（用于删除列车信息之后）
	bool db_delete_deal(string& serial, string& account, Date& departure_date);//删除订单
	bool db_delete_seat(string& serial_st, string& account);//删除座位信息（用于删除订单之后）

	vector<string> db_get_info_passenger(string&);//根据用户名从数据库中提取其他信息
	vector<string> db_get_info_admin(string&);//根据用户名从数据库中提取其他信息
	vector<string> db_find_train(string&, string&, Date&, int = 0, int = 0);//从数据库中查找车辆信息
	vector<string> db_get_deal();//从数据库中查找所有订单信息
	vector<string> db_get_deal(string& );//根据用户名查找订单信息
	vector<string> db_get_deal(Date&);//根据日期查找订单信息
};
typedef std::tr1::shared_ptr<MySQL_API> sql_ptr;
sql_ptr Create_MySQL_API(string& u=string("root"), string& p=string("root"), string& h=string("localhost"), string& t=string("railway"), unsigned int po=3306);
#endif