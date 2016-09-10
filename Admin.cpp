#include "Class_Admin.h"

Admin::Admin(string& acc, string& passwd, sql_ptr& p):account(acc),password(passwd)
{
	vector<string> info = p->db_get_info_admin(acc);
	name = info[2];
	gender = stoi(info[3]);
	birthday = Date(info[4]);
	type_of_certificate = info[5];
	id_card = info[6];
	phone_number = info[7];
}

Admin::Admin(User& ur, sql_ptr& p):account(ur.account),password(ur.password)
{
	vector<string> info = p->db_get_info_admin(ur.account);
	name = info[2];
	gender = stoi(info[3]);
	birthday = Date(info[4]);
	type_of_certificate = info[5];
	id_card = info[6];
	phone_number = info[7];
}

bool Admin::add_train(sql_ptr& p, Train& t)
{
	bool adt = p->db_add_train(t.serial_number, t.train_type, t.sleeping_berth,\
		t.hard_seat,t.departure,t.terminal,t.departure_date,t.departure_time,t.running_time,t.berth_price,t.seat_price);
	if(adt)
	{
		if(p->db_create_seat_table(t.cvt2serial_st()))
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

void Admin::show()
{
	cout << endl;
	cout << "This is Administrator" << endl;
	cout << "account: " << account << endl;
	cout << "name: " << name << endl;
	cout << "gender: " << ((gender == 1)? "Male":"Female") << endl;
	cout << "birthday: " << endl;
	birthday.show();
	cout << "type_of_certificate: " << type_of_certificate << endl;
	cout << "id_card: " << id_card << endl;
	cout << "phone_number: " << phone_number << endl;
}