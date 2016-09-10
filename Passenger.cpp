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

bool Passenger::buy_ticket(Train& t, Seat& s, sql_ptr& p, Date& d, int buy_student)//��Ʊ
{
	//���˿��Ƿ��ѹ�������г��ĳ�Ʊ
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
		//��鵱ǰʱ���Ƿ��뷢��ʱ��30��������
		if(!p->db_check_train_30min(t.serial_number, t.train_type))
		{
			cout << "This train will departure within 30 min " << endl;
			return false;
		}
		else
		{
			//�����ѡ����ʱ���ϯ���Ƿ�����Ʊ
			if(!p->db_remain_ticket(t.serial_number, t.train_type, d, s))
			{
				cout << "No remaining ticket" << endl;
				return false;
			}
			else
			{
				//�������ĳ�Ʊ�Ƿ��ѱ�����
				if(p->db_seat_sold(t.cvt2serial_st(), s, d))
				{
					cout << "The seat you choose has already been sold" << endl;
					return false;
				}
				else
				{
					cout << "Passed checks" << endl;
					//�����г���λ�����ݲ�������Ʊ��Ʊ��Ϣ
					if(!t.add_seat(p, s, account, d))
					{
						cout << "update remaining tickets information failed" << endl;
						return false;
					}

					//���û�����Ǯ����Ǯ
					//����Ƿ�Ϊѧ��Ʊ����������֧���Ľ��
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
					//��Ǯ
					if(!p->db_update_balance(account, balance))
					{
						cout << "update balance failed" << endl;
						return false;
					}
					//���ɶ���
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

bool Passenger::top_up(sql_ptr& p, double ba)//�����Ǯ����ֵ��ba��ʾ��ֵ���
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