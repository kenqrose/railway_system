#ifndef ADMIN_H_
#define ADMIN_H_
#include <iostream>
#include <string>
#include "Class_User.h"
#include "Class_MySQL_API.h"
#include "Class_Train.h"
#include "Class_Seat.h"
#include "Class_UFactory.h"

using namespace std;

class Admin:public UFactory
{
public:
	string account;//in User
	string password;//in User

	string name;
	int gender;
	Date birthday;
	string type_of_certificate;
	string id_card;
	string phone_number;
public:
	//User u;
	Admin(string& ,string& , sql_ptr&);//ͨ���û��������û����������ݿ���������ȫ������Ϣ
	Admin(User&, sql_ptr&);//ͨ���û��������û����������ݿ���������ȫ������Ϣ
	bool add_train(sql_ptr&, Train& );//����г���Ϣ�������г���λ��
	void show();
	bool buy_ticket(Train&, Seat&, sql_ptr&, Date&, int){return false;}
	bool create_deal(sql_ptr&, Train&, Seat&, Date&){return false;}
	bool top_up(sql_ptr&, double){return false;}
	//�޸ĳ�Ա����
	void set_name(string& n){name = n;}
	void set_gender(int g){gender = g;}
	void set_birthday(Date& d){birthday = d;}
	void set_tof(string& t){type_of_certificate = t;}
	void set_id(string& id){id_card = id;}
	void set_phone(string& p){phone_number = p;}
	bool delete_train(sql_ptr&, Train&);//ɾ���г���Ϣ����ɾ����λ��
	bool delete_deal(sql_ptr&);//ɾ���������������λ
	bool delete_passenger(sql_ptr&, Passenger&);//ɾ���ÿ���Ϣ
	bool get_passenger_list();//��������ÿ���Ϣ
};

#endif