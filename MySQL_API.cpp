#include "Class_MySQL_API.h"

//Factory Function 用于初始化MySQL_API类，并将其放入资源管理类shared_ptr内
sql_ptr Create_MySQL_API(string& u, string& p, string& h, string& t, unsigned int po)
{
	return std::tr1::shared_ptr<MySQL_API>(new MySQL_API(u, p, h, t, po));
}

//MySQL_API类的构造函数，初始化连接句柄
MySQL_API::MySQL_API(string& u, string& p, string& h, string& t, unsigned int po):user(u), pswd(p), host(h), table(t), port(po)
{
	mysql_init(&mysql_handle);
}

//尝试与数据库连接，若成功，重设编码格式
bool MySQL_API::Connection()
{
	if(mysql_real_connect(&mysql_handle, host.data(), user.data(), pswd.data(),table.data(),port,NULL,0))
	{
		mysql_query(&mysql_handle, "SET NAMES GBK");//设置编码格式,否则可能无法显示中文
		return true;
	}
	else
	{
		return false;
	}
}

//从数据库检查用户所在组，0为管理员，1为旅客，2为无此用户
int MySQL_API::db_check_account(string& a)
{
	string order_admin = "SELECT name FROM admin WHERE account = '" + a +"'";
	string order_passenger = "SELECT name FROM passenger WHERE account = '" + a +"'";
	int res = mysql_query(&mysql_handle, order_admin.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return 0;
		}
		else
		{
			res = mysql_query(&mysql_handle, order_passenger.data());
			if(!res)
			{
				mysql_result=mysql_store_result(&mysql_handle);
				result_count = mysql_num_rows(mysql_result);
				if(mysql_result!=NULL) mysql_free_result(mysql_result);
				if(result_count > 0)
				{
					return 1;
				}
				else
				{
					return 2;
				}
			}
			else
			{
				//check table passenger failed
			}
		}
	}
	else
	{
		//check table admin failed
	}
	if(mysql_result!=NULL) mysql_free_result(mysql_result);
	return 3;
}

bool MySQL_API::db_check_id_repetition(string& id, string& toc)//检查身份证明信息是否重复
{
	string order = "SELECT name FROM passenger WHERE id_card = '" + id +"' AND type_of_certificate = '" + toc + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

//向Passenger表中添加记录
bool MySQL_API::db_create_passenger(string& account, string& password, string& name,  int gender, Date& birthday, string& type_of_certificate, string& id_card, string& phone_number, int is_student, double balance)
{
	string gender_s = ((gender > 0) ? "1":"0");
	string is_student_s = ((is_student > 0) ? "1":"0");
	string order = "INSERT INTO passenger (account,password,name,gender,birthday,type_of_certificate,id_card,phone_number,is_student,balance) VALUES('"+account+"',MD5('"+password\
		+"'),'"+name+"',"+gender_s+",'"+birthday.cvt2String()+"','"+type_of_certificate+"','"+id_card+"','"+phone_number+"',"+is_student_s;
	stringstream os;
	os << ", " << balance << ")";
	order = order + os.str();
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_create_admin(string& account, string& password, string& name,  int gender, Date& birthday, string& type_of_certificate, string& id_card, string& phone_number, int is_student)
{
	string gender_s = ((gender > 0) ? "1":"0");
	string is_student_s = ((is_student > 0) ? "1":"0");
	string order = "INSERT INTO admin (account,password,name,gender,birthday,type_of_certificate,id_card,phone_number) VALUES('"+account+"',MD5('"+password\
		+"'),'"+name+"',"+gender_s+",'"+birthday.cvt2String()+"','"+type_of_certificate+"','"+id_card+"','"+phone_number+"')";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_change_pswd_passenger(string& acc, string& passwd)
{
	string order = "UPDATE passenger SET password = MD5('"+ passwd + "') WHERE account = '" + acc + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_change_pswd_admin(string& acc, string& passwd)
{
	string order = "UPDATE admin SET password = MD5('"+ passwd + "') WHERE account = '" + acc + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_check_pswd_admin(string& acc, string& passwd)
{
	string order = "SELECT account FROM admin WHERE account = '" + acc + "' AND password = MD5('" + passwd + "')";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//check table admin failed
	}
	if(mysql_result!=NULL) mysql_free_result(mysql_result);
}

bool MySQL_API::db_check_pswd_passenger(string& acc, string& passwd)
{
	string order = "SELECT account FROM passenger WHERE account = '" + acc + "' AND password = MD5('" + passwd + "')";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//check table passenger failed
	}
	if(mysql_result!=NULL) mysql_free_result(mysql_result);
}

vector<string> MySQL_API::db_get_info_passenger(string& acc)
{
	vector<string> passenger_info;
	string order = "SELECT * FROM passenger WHERE account = '" + acc + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result = mysql_store_result(&mysql_handle);
		if(mysql_result)
		{
			while(mysql_row = mysql_fetch_row(mysql_result))
			{
				for(int i=0;i<mysql_num_fields(mysql_result);i++)
				{
					passenger_info.push_back(string(mysql_row[i]));
				}
			}
		}
	}
	else
	{
		//query sql failed
	}
	 if(mysql_result!=NULL) mysql_free_result(mysql_result);
	 return passenger_info;
}

vector<string> MySQL_API::db_get_info_admin(string& acc)
{
	vector<string> admin_info;
	string order = "SELECT * FROM admin WHERE account = '" + acc + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result = mysql_store_result(&mysql_handle);
		if(mysql_result)
		{
			while(mysql_row = mysql_fetch_row(mysql_result))
			{
				for(int i=0;i<mysql_num_fields(mysql_result);i++)
				{
					admin_info.push_back(string(mysql_row[i]));
				}
			}
		}
	}
	else
	{
		//query sql failed
	}
	 if(mysql_result!=NULL) mysql_free_result(mysql_result);
	 return admin_info;
}

bool MySQL_API::db_create_seat_table(string& serial)//在数据库中创建座位表
{
	string order = "CREATE TABLE " + serial + " (carriage_type INT(1), carriage_number INT(2), \
											  seat_type INT(1), seat_number INT(3), buyer_acc VARCHAR(14), boarding_date DATE)";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_add_seat(string& serial, Seat& s, string& account, Date& d)//在对应列车座位表中添加座位
{
	string order = "INSERT INTO " + serial + " (carriage_type, carriage_number, seat_type, seat_number, \
											 buyer_acc, boarding_date) VALUES ( " + s.cvt2String() + ",'" + account + "','" + d.cvt2String() + "')";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_seat_sold(string& table_name, Seat& s, Date& d)//检查座位是否已被占用
{
	string order = "SELECT * FROM " + table_name + " WHERE " + \
		s.cvt2String_check() + " AND boarding_date = '" + d.cvt2String() + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_create_deal(string& account, string& serial, string& departure, string& terminal, Date& d, Time& t, Seat& s, int is_student, int price, int ticket_status)//创建订单
{
	string order = "INSERT INTO deal (purchasing_date, purchasing_time, account, train_number, departure, terminal, departure_date, departure_time, carriage_type, carriage_number, \
				   seat_type, seat_number, price, is_student, ticket_status) VALUES ( CURDATE(), CURTIME(), '"+ account + "', '" + serial + "', '" + departure + "', '"\
				   + terminal + "', '" + d.cvt2String() + "', '" + t.cvt2String() + "', " + s.cvt2String() + " , ";
	stringstream os;
	os << price << "," << is_student << "," << ticket_status << ")";
	order = order + os.str();
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_check_train_30min(string& serial_number, int train_type)//检查当前时间是否离发车时间30分钟以上
{
	string order = "SELECT * FROM train WHERE serial_number = '" + serial_number + "' AND train_type = " ;
	stringstream os;
	os << train_type;
	order = order + os.str() + " AND departure_date = CURDATE() AND departure_time > ADDTIME(CURTIME(), '00:30:00')";

	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

vector<string> MySQL_API::db_find_train(string& departure,string& terminal, Date& departure_date, int carriage_type, int train_type)//从数据库中查找车辆信息
{
	vector<vector<string>> train_info;
	vector<string> train_string;
	string order = "SELECT * FROM train WHERE departure = '" + departure + "' AND terminal = '" + terminal + \
		"' AND departure_date = '" + departure_date.cvt2String() + "' AND departure_time >= ADDTIME(CURTIME(), '00:30:00') ";
	switch(carriage_type)
	{
	case 0:
		{
			order = order + "AND (remain_seat + remain_berth) > 0 ";
			break;
		}
	case 1:
		{
			order = order + "AND remain_seat > 0 ";
			break;
		}
	case 2:
		{
			order = order + "AND remain_berth > 0";
			break;
		}
	default:
		{break;}
	}
	switch(train_type)
	{
	case 0:
		{
		}
	case 1:
		{
			order = order + "AND train_type = 0";
			break;
		}
	case 2:
		{
			order = order + "AND train_type = 1";
			break;
		}
	case 3:
		{
			order = order + "AND train_type = 2";
			break;
		}
	case 4:
		{
			order = order + "AND train_type IN (0, 1)";
			break;
		}
	case 5:
		{
			order = order + "AND train_type IN (0, 2)";
			break;
		}
	case 6:
		{
			order = order + "AND train_type IN (2, 1)";
			break;
		}
	default:
		{break;}
	}

	int res = mysql_query(&mysql_handle,order.data());
	if(!res)
	{
		mysql_result = mysql_store_result(&mysql_handle);
		if(mysql_result)
		{
			int j=0;
			while(mysql_row = mysql_fetch_row(mysql_result))
			{
				//train_string.clear();
				for(int i=0;i<mysql_num_fields(mysql_result);i++)
				{
					train_string.push_back(string(mysql_row[i]));
				}
				//train_info.push_back(train_string);
			}
		}
	}
	else
	{
		//query sql failed
	}
	 if(mysql_result!=NULL) mysql_free_result(mysql_result);
	 return train_string;
}

bool MySQL_API::db_add_train(string& serial_number, int train_type, int sleeping_berth, int hard_seat, string& departure, string& terminal, Date& departure_date, Time& departure_time, Time& running_time, float berth_price, float seat_price)
{
	string order = "INSERT INTO train (serial_number, train_type, sleeping_berth, hard_seat, departure, terminal, departure_date, departure_time, running_time, berth_price, seat_price, remain_seat, remain_berth) VALUES ('" + serial_number +"', ";
	stringstream os;
	os << train_type << ", " << sleeping_berth << ", " << hard_seat << ", '" << departure << "', '" << \
		terminal << "', '" << departure_date.cvt2String() << "', '" << departure_time.cvt2String() << "', '" << running_time.cvt2String() << "', " << berth_price << ", " << seat_price << ", "<< 120*hard_seat << ", " << 60*sleeping_berth << " )";
	order = order + os.str();
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_update_seat_remain(string& serial_number,int train_type, Seat& s, Date& d)
{
	string order = "UPDATE train SET ";
	stringstream os;
	if(s.carriage_type == 0)
	{
		order = order + "remain_seat = remain_seat-1 ";
	}
	else if(s.carriage_type == 1)
	{
		order = order + "remain_berth = remain_berth-1 ";
	}
	order = order + "WHERE serial_number = '" + serial_number + "' AND departure_date = '" + d.cvt2String() + "'";
	stringstream os1;
	os1 << " AND train_type = " << train_type;
	order = order + os1.str();
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_not_bought(string& account, string& serial, Date& departure_date, Seat& seat)
{
	string order = "SELECT * FROM deal WHERE account ='" + account + "' AND train_number='" + \
		serial +"' AND departure_date='" + departure_date.cvt2String() + "' AND carriage_type=";
	stringstream os;
	os << seat.carriage_type;
	order = order + os.str();
	
	int res = mysql_query(&mysql_handle, order.data());
	
	if(!res)
	{
		//query SQL succeed
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count == 0)
		{
			return true;
		}
		else
		{
			order = order + " AND ticket_status=0";
			int res1 = mysql_query(&mysql_handle, order.data());
			if(!res1)
			{
				mysql_result=mysql_store_result(&mysql_handle);
				result_count = mysql_num_rows(mysql_result);
				if(mysql_result!=NULL) mysql_free_result(mysql_result);
				if(result_count == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			return false;
		}
	}
	else
	{
		return false;
	}
	if(mysql_result!=NULL) mysql_free_result(mysql_result);
}

bool MySQL_API::db_remain_ticket(string& serial_number, int train_type, Date& departure_date, Seat& s)
{
	string order = "SELECT * FROM train WHERE serial_number = '" + serial_number + "'";
	if(s.carriage_type == 0)
	{
		order = order + " AND remain_seat >0";
	}
	else if(s.carriage_type == 1)
	{
		order = order + " AND remain_berth >0";
	}
	else
	{
		return false;
	}
	stringstream os;
	os << train_type;
	order = order + " AND train_type=" + os.str();
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		mysql_result=mysql_store_result(&mysql_handle);
		int result_count = mysql_num_rows(mysql_result);
		if(mysql_result!=NULL) mysql_free_result(mysql_result);
		if(result_count > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	if(mysql_result!=NULL) mysql_free_result(mysql_result);
}

bool MySQL_API::db_update_passenger(string& name, int gender, Date& birthday, string& type_of_certi, string& id_card, string& phone_number, int is_student, double balance)//更新旅客用户信息
{
	string order = "UPDATE passenger SET name = '"+name+"', birthday = '"+birthday.cvt2String()+"', type_of_certificate='"+type_of_certi+"', phone_number = '"+phone_number+"', ";
	stringstream os;
	os << "gender = " << gender << ", is_student = " << is_student << ", balance = " << balance;
	order = order + os.str();
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_update_train(string& serial_number, int train_type, int sleeping_berth, int hard_seat, string& departure, string& terminal, Date& departure_date, Time& departure_time, Time& running_time, float berth_price, float seat_price)
{
	string order = "UPDATE train SET departure = '"+departure+", terminal = '"+terminal+"', departure_date = '"+departure_date.cvt2String()+"', departure_time = '"+departure_time.cvt2String()+"',running_time='"+running_time.cvt2String()+"', ";
	stringstream os;
	os << "sleeping_berth = " << sleeping_berth << ", hard_seat=" << hard_seat << ", berth_price=" << berth_price << ", seat_price=" << seat_price;
	order = order + os.str() + "WHERE serial_number = '"+serial_number+"'";
	stringstream os1;
	os1 << "AND train_type = " << train_type;
	order = order + os1.str();

	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_delete_passenger(string& account)
{
	string order = "DELETE FROM passenger WHERE account ='" + account + "'";
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_delete_train(string& serial_number, int train_type)
{
	string order="DELETE FROM train WHERE serial_number = '"+serial_number + "' AND train_type = ";
	stringstream os;
	os << train_type;
	order = order + os.str();
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_delete_seat_table(string& serial_st)
{
	string order = "DROP TABLE IF EXISTS "+serial_st;
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_delete_deal(string& serial, string& account, Date& departure_date)
{
	string order = "DELETE FROM deal WHERE train_number = '"+serial+"' AND account = '"+account+"' AND departure_date = '"+departure_date.cvt2String()+"'";
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MySQL_API::db_delete_seat(string& serial_st, string& account)
{
	string order = "DELETE FROM "+serial_st+" WHERE account = '"+account+"'";
	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<string> MySQL_API::db_get_deal()//从数据库中查找所有订单信息
{
	vector<string> deal_info;
	string order ="SELECT * FROM deal";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result = mysql_store_result(&mysql_handle);
		if(mysql_result)
		{
			while(mysql_row = mysql_fetch_row(mysql_result))
			{
				for(int i=0;i<mysql_num_fields(mysql_result);i++)
				{
					deal_info.push_back(string(mysql_row[i]));
				}
			}
		}
	}
	else
	{
		//query sql failed
	}
	 if(mysql_result!=NULL) mysql_free_result(mysql_result);
	 return deal_info;
}

vector<string> MySQL_API::db_get_deal(string& account)//根据用户名查找订单信息
{
	vector<string> deal_info;
	string order ="SELECT * FROM deal WHERE account = '" + account + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result = mysql_store_result(&mysql_handle);
		if(mysql_result)
		{
			while(mysql_row = mysql_fetch_row(mysql_result))
			{
				for(int i=0;i<mysql_num_fields(mysql_result);i++)
				{
					deal_info.push_back(string(mysql_row[i]));
				}
			}
		}
	}
	else
	{
		//query sql failed
	}
	 if(mysql_result!=NULL) mysql_free_result(mysql_result);
	 return deal_info;
}

vector<string> MySQL_API::db_get_deal(Date& departure_date)//根据日期查找订单信息
{
	vector<string> deal_info;
	string order ="SELECT * FROM deal WHERE departure_date = '" + departure_date.cvt2String() + "'";
	int res = mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		//query SQL succeed
		mysql_result = mysql_store_result(&mysql_handle);
		if(mysql_result)
		{
			while(mysql_row = mysql_fetch_row(mysql_result))
			{
				for(int i=0;i<mysql_num_fields(mysql_result);i++)
				{
					deal_info.push_back(string(mysql_row[i]));
				}
			}
		}
	}
	else
	{
		//query sql failed
	}
	 if(mysql_result!=NULL) mysql_free_result(mysql_result);
	 return deal_info;
}

bool MySQL_API::db_update_balance(string& account, double balance)//更新用户电子钱包余额信息
{
	string order = "UPDATE passenger SET balance = ";
	stringstream os ;
	os << balance;
	order = order + os.str() + " WHERE account = '" + account + "'";

	int res=mysql_query(&mysql_handle, order.data());
	if(!res)
	{
		return true;
	}
	else
	{
		return false;
	}
}