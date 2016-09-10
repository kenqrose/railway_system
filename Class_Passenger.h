#ifndef _PASSENGER_H_
#define _PASSENGER_H_
#include <iostream>
#include <string>
#include <vector>
#include "Class_Time.h"
#include "Class_User.h"
#include "Class_MySQL_API.h"
#include "Class_Train.h"
#include "Class_Seat.h"
#include "Class_UFactory.h"

using namespace std;

class Passenger:public UFactory
{
private:
	string account;//in User
	string password;//in User
	
	string name;
	int gender;
	Date birthday;
	string type_of_certificate;
	string id_card;
	string phone_number;
	int is_student;
	double balance;
public:
	//User u;
	Passenger(string&, string&, wstring&, int, Date&, string&, string&, string&, int, double);//ͨ��������Ϣ�����û�
	Passenger(string& , string&, sql_ptr&);//ͨ���û��������û����������ݿ���������ȫ������Ϣ
	Passenger(User&, sql_ptr&);
	bool buy_ticket(Train&, Seat&, sql_ptr&, Date&, int buy_student);//��Ʊ������ѡ�����λ�ţ�buy_studentΪ�Ƿ���ѧ��Ʊ�Ĳ���ֵ
	void show();//��ʾPassenger���Ա����
	bool create_deal(sql_ptr&, Train&, Seat&, Date&){return false;}//������������buy_ticket��ֱ��ʹ��db����ʵ����������ܣ�
	bool add_train(sql_ptr&, Train&){return false;}
	bool update(sql_ptr&);//�����޸ĺ������
	bool top_up(sql_ptr&, double);//�����Ǯ����ֵ��doubleΪ��ֵ���
	double check_balance(){return balance;}
	//�޸ĳ�Ա����
	void set_name(string& n){name = n;}
	void set_gender(int g){gender = g;}
	void set_birthday(Date& d){birthday = d;}
	void set_tof(string& t){type_of_certificate = t;}
	void set_id(string& id){id_card = id;}
	void set_phone(string& p){phone_number = p;}
	void set_student(int s){is_student = s;}
};
#endif