#include "Class_Passenger.h"
#include "Class_Admin.h"
#include "Class_UFactory.h"

shared_ptr<UFactory> UFact::login(User& u, sql_ptr& p)
{
	u.check_account(p);
	if(u.check_password(p))
	{
		if(u.getstatus() == 0)
		{
			return shared_ptr<UFactory>(new Admin(u, p));
			//return shared_ptr<User*>(new Admin(u.account, u.password, p));
		}
		else if(u.getstatus() == 1)
		{
			return shared_ptr<UFactory>(new Passenger(u, p));
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

shared_ptr<UFactory> UFact::login(string& account, string& password, sql_ptr& p)
{
	User u(account, password);
	u.check_account(p);
	if(u.getstatus() == 2 || u.getstatus() == 3)
	{
		return nullptr;
	}
	else
	{
		if(u.check_password(p))
		{
			if(u.getstatus() == 0)
			{
				return shared_ptr<UFactory>(new Admin(u, p));
			}
			else if(u.getstatus() == 1)
			{
				return shared_ptr<UFactory>(new Passenger(u, p));
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}
}

vector<Train> UFactory::find_train(sql_ptr& p, string& departure, string& terminal, Date& d, int carriage_type, int train_type)//carriage_type=0全部,1硬座,2卧铺;train_type=0全部,1高铁,2特快,3普快
{
	vector<string> train_info = p->db_find_train(departure, terminal, d, carriage_type, train_type);
	vector<Train> train;
	vector<string> temp;
	for(int j=0;j<train_info.size()/13;j++)
	{
		temp.clear();
		for(int i=0;i<13;i++)
		{
			temp.push_back(train_info[i+j]);
		}
		train.push_back(Train(temp));
	}
	return train;
}

bool UFact::register_account(sql_ptr& p, string& account, string& password, string& name,  int gender, Date& birthday, string& type_of_certificate, string& id_card, string& phone_number, int is_student, double balance)
{
	int check=p->db_check_account(account);
	if(check == 2)
	{
		if(p->db_check_id_repetition(id_card, type_of_certificate))
		{
			bool res=p->db_create_passenger(account, password, name, gender, birthday, type_of_certificate, id_card, phone_number, is_student, balance);
			if(res)
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
	else
	{
		return false;
	}
}

vector<Deal> UFactory::get_deal(sql_ptr& p)//获得全部订单信息
{
	vector<Deal> deal;
	vector<string> temp;
	vector<string> deal_info = p->db_get_deal();
	for(int i=0;i<deal_info.size()/16;i++)
	{
		temp.clear();
		for(int j=0;j<16;j++)
		{
			temp.push_back(deal_info[i+j]);
		}
		deal.push_back(Deal(temp));
	}
	return deal;
}

vector<Deal> UFactory::get_deal(sql_ptr& p, string& account)//获得指定旅客的订单信息
{
	vector<Deal> deal;
	vector<string> temp;
	vector<string> deal_info = p->db_get_deal(account);
	for(int i=0;i<deal_info.size()/16;i++)
	{
		temp.clear();
		for(int j=0;j<16;j++)
		{
			temp.push_back(deal_info[i+j]);
		}
		deal.push_back(Deal(temp));
	}
	return deal;
}

vector<Deal> UFactory::get_deal(sql_ptr& p, Date& departure_date)//获得指定日期的订单信息
{
	vector<Deal> deal;
	vector<string> temp;
	vector<string> deal_info = p->db_get_deal(departure_date);
	for(int i=0;i<deal_info.size()/16;i++)
	{
		temp.clear();
		for(int j=0;j<16;j++)
		{
			temp.push_back(deal_info[i+j]);
		}
		deal.push_back(Deal(temp));
	}
	return deal;
}

bool UFact::logout(shared_ptr<UFactory> p)
{
	p.reset();
	if(!p)
	{
		return true;
	}
	else
	{
		return false;
	}
}

shared_ptr<UFactory> UFact::switch_user(shared_ptr<UFactory>& p, string& account, string& passwd, sql_ptr& ptr)
{
	if(p.use_count() == 0)
	{
		cout << "Not login yet!" << endl;
		return UFact::login(account, passwd, ptr);
	}
	else if(p.unique())
	{
		if(!UFact::logout(p))
		{
			cout << "Previous account logout failed" << endl;
			return nullptr;
		}
		else
		{
			cout << "Previous account logout succeed" << endl;
			return UFact::login(account, passwd, ptr);
		}
	}
}

