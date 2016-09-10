#ifndef TRAIN_H_
#define TRAIN_H_
#include <iostream>
#include <string>
#include <vector>
#include "Class_Time.h"
#include "Class_MySQL_API.h"
#include "Class_Seat.h"
using namespace std;

class Train
{
private:
	string serial_number;
	int train_type;//�������ͣ�0Ϊ����G��1Ϊ�ؿ�T��2Ϊ�տ�K
	int sleeping_berth;
	int hard_seat;
	string departure;
	string terminal;
	Date departure_date;
	Time departure_time;
	Time running_time;
	float berth_price;
	float seat_price;
	int remain_berth;
	int remain_seat;
public:
	Train(){};
	Train(string& sn, int tt, int s, int h, string& de, string& te, Date& dd, Time& dt, Time& rt, float bp, float sp):\
		serial_number(sn), train_type(tt), sleeping_berth(s), hard_seat(h), departure(de), terminal(te), departure_time(dt),\
		departure_date(dd),running_time(rt), berth_price(bp), seat_price(sp), remain_berth(s*60), remain_seat(h*120){}
	Train(string&);
	Train(vector<string>& );
	friend class Passenger;
	friend class MySQL_API;
	friend class Admin;
	bool create_seat_table(sql_ptr& );//������λ��
	string cvt2serial_st();//���г������������Ϊ�ַ��������ڴ�����λ��
	string cvt2serial();//���ɳ��κ�
	bool add_seat(sql_ptr&, Seat&, string&, Date&);//�ڶ�Ӧ�г���λ���������λ��������Ʊ��Ϣ
	void show();//����г���Ϣ
	bool update(sql_ptr&);//�����г���Ϣ

	//�������
	string get_departure(){return departure;}
	string get_terminal(){return terminal;}
	string get_dep_date(){return departure_date.cvt2String_display();}
	string get_dep_time(){return departure_time.cvt2String_display();}
	string get_run_time(){return running_time.cvt2String_display();}
	string get_berth_remain(){stringstream os;os << remain_berth;return os.str();}
	string get_seat_remain(){stringstream os;os << remain_seat;return os.str();}
};

#endif