#include "Class_User.h"

void User::check_account(sql_ptr& p)
{
	if(p->Connection() == true)
	{
		status = p->db_check_account(account);
	}
	else
	{
		cout << "Database hasn't been connected!" << endl;
	}
}

bool User::check_password(sql_ptr& p)
{
	if(p->Connection() == true)
	{
		if(status == 0)
		{
			if(p->db_check_pswd_admin(account, password) == true)
			{
				cout << "Password of administrator " << account << " is right" << endl;
				return true;
			}
			else
			{
				cout << "Password of administrator " << account << " is not right" << endl;
				return false;
			}
		}
		else if(status == 1)
		{
			if(p->db_check_pswd_passenger(account, password) == true)
			{
				cout << "Password of passenger " << account << " is right" << endl;
				return true;
			}
			else
			{
				cout << "Password of passenger " << account << " is not right" << endl;
				return false;
			}
		}
		else
		{
			cout << "account status is wrong" << endl;
			return false;
		}
	}
	else
	{
		cout << "Database Connection failed" << endl;
		return false;
	}
}

bool User::change_password(sql_ptr& p)
{
	if(p->Connection() == true)
	{
		if(status == 0)
		{
			if(p->db_change_pswd_admin(account, password))
			{
				cout << "change administrator " << account << " passwd succeed" << endl;
				return true;
			}
			else
			{
				cout << "change administrator " << account << " passwd failed" << endl;
				return false;
			}
		}
		else if(status == 1)
		{
			if(p->db_change_pswd_passenger(account, password))
			{
				cout << "change passenger " << account << " passwd succeed" << endl;
				return true;
			}
			else
			{
				cout << "change passenger " << account << " passwd failed" << endl;
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

bool check_acc_format(string& acc)//检查账户是否满足格式要求
{
	if(acc.size() < 7 || acc.size() > 14)
	{
		cout << "wrong size" << endl;
		return false;
	}
	else
	{
		const regex pattern("\\w+");
		if(regex_match(acc, pattern) == true)
		{
			return true;
		}
		else
		{
			cout << "wrong pattern" << endl;
			return false;
		}
	}
}

bool check_pswd_format(string& pswd)//检查密码是否满足格式要求
{
	if(pswd.size() < 7 || pswd.size() > 10)
	{
		cout << "wrong size" << endl;
		return false;
	}
	else
	{
		const regex pattern("\\w+");
		if(regex_match(pswd, pattern) == true)
		{
			return true;
		}
		else
		{
			cout << "wrong pattern" << endl;
			return false;
		}
	}
}

//vector<Train> User::find_train(sql_ptr& p, string& departure, string& terminal, Date& d, int carriage_type, int train_type)//carriage_type=0全部,1硬座,2卧铺;train_type=0全部,1高铁,2特快,3普快
//{
//	vector<string> train_info = p->db_find_train(departure, terminal, d, carriage_type, train_type);
//	vector<Train> train;
//	for(int i=0;i<train_info.size();i++)
//	{
//		train.push_back(Train(train_info[i]));
//	}
//	return train;
//}
