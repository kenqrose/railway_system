#include "Class_Seat.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string Seat::cvt2String()
{
	string ser;
	stringstream os;
	os << carriage_type << ',' << carriage_number << ',' << seat_type << ',' << seat_number;
	ser = ser + os.str();
	return ser;
}

string Seat::cvt2String_check()
{
	string res = "carriage_type = ";
	stringstream os;
	os << carriage_type << " AND carriage_number = " << carriage_number << " AND seat_type = " << seat_type << " AND seat_number = " << seat_number;
	res = res + os.str();
	return res;
}