#include <iostream>
#include <string>
#include "Class_MySQL_API.h"
#include "Class_User.h"
#include "Class_Passenger.h"
#include "Class_Admin.h"
#include "Class_UFactory.h"

using namespace std;
//sql_ptr Create_MySQL_API(string& u, string& p, string& h, string& t, unsigned int po);

int main()
{
	string user("root");
	string pswd("root");
	string host("localhost");
	string table("railway");
	unsigned int port = 3306;

	//std::tr1::shared_ptr<MySQL_API> mysql_ptr = Create_MySQL_API(user, pswd, host, table, port);
	sql_ptr mysql_ptr = Create_MySQL_API(user, pswd, host, table, port);
	shared_ptr<UFactory> user_ptr;
	if(mysql_ptr->Connection() == true)
	{
		cout << "DataBase Connection Succeed." << endl;
		string account("rgavsv001");
		string password("root");
		
		int reg_flag=register_account(mysql_ptr, account, password, string("我也不知道是谁"), 0, Date(2016, 9, 6), string("身份证"), string("1431618613056"), string("15610215"));

		if(!reg_flag)
		{
			cout << "Register failed" << endl;
		}
		else
		{
			cout << "Register succeed" << endl;
			user_ptr = login(account, password, mysql_ptr);
			user_ptr->show();
			if(!user_ptr->top_up(mysql_ptr, 1000))
			{
				cout << endl << endl << "top up failed" << endl << endl;
			}
			user_ptr = switch_user(user_ptr, account, password, mysql_ptr);
			Date depar_d(2016, 9, 8);
			if(user_ptr.get() != nullptr)
			{
			vector<Train> train_info = user_ptr->find_train(mysql_ptr, string("北京"), string("上海"), depar_d);
			if(train_info.size()!=0)
			{
			for(int i=0;i<train_info.size();i++)
			{
				train_info[i].show();
			}
			cout << "buy ticket: " << user_ptr->buy_ticket(train_info[0], Seat(1,1,0,10), mysql_ptr, depar_d, 0) << endl;
			user_ptr->show();
			}
			else
			{
				cout << "no train" << endl;
			}
			}
			else
			{
				cout << "switch failed" << endl;
			}
		}

	}
	else
	{
		cout << "DataBase Connection Failed." << endl;
	}

	return 0;
}