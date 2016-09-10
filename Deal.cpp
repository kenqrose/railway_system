#include "Class_Deal.h"

Deal::Deal(string& sn, Date& pd, Time& pt, string& acc, string& tn, string& de, string& te, Date& dd, Time& dt, Seat& s, int is, float p, int ts):serial_number(sn), \
	purchasing_date(pd), purchasing_time(pt), account(acc), train_number(tn), departure(de), terminal(te), departure_date(dd), departure_time(dt), seat(s), \
	is_student(is), price(p), ticket_status(ts){}

Deal::Deal(vector<string>& deal_info): serial_number(deal_info[0]), purchasing_date(deal_info[1]), purchasing_time(deal_info[2]), account(deal_info[3]), \
	train_number(deal_info[4]), departure(deal_info[5]), terminal(deal_info[6]), departure_date(deal_info[7]), departure_time(deal_info[8]), \
	seat(stoi(deal_info[9]), stoi(deal_info[10]), stoi(deal_info[11]), stoi(deal_info[12])),price(stof(deal_info[13])), is_student(stoi(deal_info[14])), \
	ticket_status(stoi(deal_info[15])){}

