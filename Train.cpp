#include "Class_Train.h"


Train::Train(vector<string>& s):serial_number(s[0]), train_type(atoi(s[1].data())), sleeping_berth(atoi(s[2].data())), hard_seat(atoi(s[3].data())),\
	departure(s[4]), terminal(s[5]), departure_date(Date(s[6])), departure_time(Time(s[7])), running_time(Time(s[8])), berth_price(atof(s[9].data())),\
	seat_price(atof(s[10].data())), remain_berth(atoi(s[11].data())), remain_seat(atoi(s[12].data())){}


string Train::cvt2serial_st()
{
	string ser;
	if(train_type == 0)
	{
		ser = "G" + serial_number + "_st";
	}
	else if(train_type == 1)
	{
		ser = "T" + serial_number + "_st";
	}
	else
	{
		ser = "K" + serial_number + "_st";
	}
	return ser;
}

string Train::cvt2serial()
{
	string ser;
	if(train_type == 0)
	{
		ser = "G" + serial_number;
	}
	else if(train_type == 1)
	{
		ser = "T" + serial_number;
	}
	else
	{
		ser = "K" + serial_number;
	}
	return ser;
}

bool Train::create_seat_table(sql_ptr& p)
{
	if(p->db_create_seat_table(cvt2serial_st()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Train::add_seat(sql_ptr& p, Seat& s, string& account, Date& d)
{
	if(p->db_add_seat(cvt2serial_st(), s, account, d))
	{
		cout << "add to seat table succeed" << endl;
		if(p->db_update_seat_remain(serial_number, train_type, s, d))
		{
			cout << "update remain ticket info succeed" << endl;
			if(s.carriage_type == 0)
			{
					remain_seat--;
			}
			else if(s.carriage_type == 1)
			{
					remain_berth--;
			}
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

void Train::show()
{
	cout << "Train: " << cvt2serial() << endl;
	cout << "Number of berth: " << sleeping_berth << endl;
	cout << "Number of seat: " << hard_seat << endl;
	cout << "Departure station: " << departure << endl;
	cout << "Terminal station: " << terminal << endl;
	cout << "Departre date: " << endl;
	departure_date.show();
	cout << "Departure time: " << endl;
	departure_time.show();
	cout << "Running time: " << endl;
	running_time.show();
	cout << "Berth_price: " << berth_price << endl;
	cout << "Seat_price: " << seat_price << endl;
	cout << "Remaining berth: " << remain_berth << endl;
	cout << "Remaining seat: " << remain_seat << endl;
}

bool Train::update(sql_ptr& p)
{
	bool flag = p->db_update_train(serial_number, train_type, sleeping_berth, hard_seat, departure, terminal, departure_date, departure_time, running_time, berth_price, hard_seat);
	if(flag)
	{
		return true;
	}
	else
	{
		return false;
	}
}