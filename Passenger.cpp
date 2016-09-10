#include "Class_Passenger.h"

Passenger::Passenger(string& acc, string& passwd, sql_ptr& p):account(acc),password(passwd)
{
	vector<string> info = p->db_get_info_passenger(acc);
	name = info[2];
	gender = stoi(info[3]);
	birthday = Date(info[4]);
	type_of_certificate = info[5];
	id_card = info[6];
	phone_number = info[7];
	is_student = stoi(info[8]);
	balance = stof(info[9]);
}

Passenger::Passenger(User& u, sql_ptr& p):account(u.account), password(u.password)
{
	vector<string> info = p->db_get_info_passenger(u.account);
	name = info[2];
	gender = stoi(info[3]);
	birthday = Date(info[4]);
	type_of_certificate = info[5];
	id_card = info[6];
	phone_number = info[7];
	is_student = stoi(info[8]);
	balance = stof(info[9]);
}

void Passenger::show()
{
	cout << endl;
	cout << "This is Passenger" << endl;
	cout << "account: " << account << endl;
	cout << "name: " << name << endl;
	cout << "gender: " << ((gender == 1)? "Male":"Female") << endl;
	cout << "birthday: " << endl;
	birthday.show();
	cout << "type_of_certificate: " << type_of_certificate << endl;
	cout << "id_card: " << id_card << endl;
	cout << "phone: " << phone_number << endl;
	cout << ((is_student==1)?"Student":"Not Student") << endl;
	cout << "balance: " << balance << endl;
}

bool Passenger::buy_ticket(Train& t, Seat& s, sql_ptr& p, Date& d, int buy_student)//买票
{
	//检查乘客是否已购买此趟列车的车票
	if(buy_student == 1)
	{
		if(is_student == 0)
		{
			cout << "You're not student, can't buy student ticket " << endl;
			return false;
		}
	}

	if(!p->db_not_bought(account, t.cvt2serial(), d, s))
	{
		cout << "has already bought this train" << endl;
		return false;
	}
	else
	{
		//检查当前时间是否离发车时间30分钟以上
		if(!p->db_check_train_30min(t.serial_number, t.train_type))
		{
			cout << "This train will departure within 30 min " << endl;
			return false;
		}
		else
		{
			//检查所选车辆时间和席别是否还有余票
			if(!p->db_remain_ticket(t.serial_number, t.train_type, d, s))
			{
				cout << "No remaining ticket" << endl;
				return false;
			}
			else
			{
				//检查所买的车票是否已被订购
				if(p->db_seat_sold(t.cvt2serial_st(), s, d))
				{
					cout << "The seat you choose has already been sold" << endl;
					return false;
				}
				else
				{
					cout << "Passed checks" << endl;
					//更新列车座位表数据并更新余票余票信息
					if(!t.add_seat(p, s, account, d))
					{
						cout << "update remaining tickets information failed" << endl;
						return false;
					}

					//从用户电子钱包扣钱
					//检查是否为学生票，并生成需支付的金额
					int actual_price;
					if(buy_student == 1)
					{
						if(t.train_type == 0)
						{
							actual_price = t.seat_price*0.5;
						}
						else
						{
							if(s.carriage_type == 0)
							{
								actual_price = t.seat_price*0.5;
							}
							else if(s.carriage_type == 1)
							{
								actual_price = t.berth_price*0.75;
							}
						}
					}
					else
					{
						if(s.carriage_type == 0)
						{
							actual_price = t.seat_price*0.5;
						}
						else if(s.carriage_type == 1)
						{
							actual_price = t.berth_price*0.75;
						}
					}
					cout << "You need to pay: " << actual_price << endl;
					if(balance < actual_price)
					{
						cout << "you don't have enought money";
						return false;
					}
					balance = balance - actual_price;
					//扣钱
					if(!p->db_update_balance(account, balance))
					{
						cout << "update balance failed" << endl;
						return false;
					}
					//生成订单
					if(!p->db_create_deal(account, t.cvt2serial(), t.departure, t.terminal, t.departure_date, t.departure_time, s, \
						is_student, actual_price))
					{
						cout << "generating deal failed" << endl;
						return false;
					}
					cout << "ticket deal generated successfully" << endl;
					return true;
				}
			}
		}
	}
}

bool Passenger::update(sql_ptr& p)
{
	return p->db_update_passenger(name, gender, birthday,type_of_certificate, id_card,  phone_number, is_student, balance);
}

bool Passenger::top_up(sql_ptr& p, double ba)//向电子钱包充值，ba表示充值金额
{
	balance = balance + ba;
	if(p->db_update_balance(account, balance))
	{
		return true;
	}
	else
	{
		return false;
	}
}