#ifndef TIME_H_
#define TIME_H_
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;
class Date
{
private:
	int year;
	int month;
	int day;
public:
	Date();
	Date(int y, int m, int d):year(y),month(m),day(d){}
	Date(Date& d):year(d.year),month(d.month),day(d.day){}
	Date(string& d);//使用MySQL返回的数据格式初始化Date对象
	void SetDate(int y, int m, int d){year = y;month = m;day = d;}
	void SetYear(int y){year = y;}
	void SetMonth(int m){month = m;}
	void SetDay(int d){day = d;}

	void AddDate(int y, int m, int d);
	void AddYear(int ay){year = year + ay;}

	int get_year(){return year;}
	int get_month(){return month;}
	int get_day(){return day;}
	bool student_time();//检查日期是否处在可以购买学生票的区间
	bool operator>=(Date&);
	bool operator<=(Date&);
	string cvt2String();
	string cvt2String_display();
	void show()
	{
		cout << endl << "year: " << year << endl;
		cout << "month: " << month << endl;
		cout << "day: " << day << endl;
	}
};

class Time
{
private:
	int hour;
	int minute;
public:
	Time();
	Time(int h, int m):hour(h), minute(m){}
	Time(Time& t):hour(t.hour), minute(t.minute){}
	Time(string& t);//使用MySQL返回的对象格式初始化Time对象
	void SetTime(int h, int m){hour = h;minute = m;}
	void SetHour(int h){hour = h;}
	void SetMinute(int m){minute = m;}
	int get_hour(){return hour;}
	int get_minute(){return minute;}
	string cvt2String();
	string cvt2String_display();
	void show()
	{
		cout << endl << "hour: " << hour << endl;
		cout << "minute: " << minute << endl;
	}
};
 
#endif