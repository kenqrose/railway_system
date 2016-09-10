#ifndef DEAL_H_
#define DEAL_H_
#include <iostream>
#include <string>
#include <vector>
#include "Class_Time.h"
#include "Class_Seat.h"

using namespace std;


class Deal
{
public:
	string serial_number;
	Date purchasing_date;
	Time purchasing_time;
	string account;
	string train_number;
	string departure;
	string terminal;
	Date departure_date;
	Time departure_time;
	Seat seat;
	float price;
	int is_student;
	int ticket_status;
	Deal(string&, Date&, Time&, string&, string&, string&, string&, Date&, Time&, Seat&, int, float, int);
	Deal(vector<string>& );
};

#endif