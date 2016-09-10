#include "Class_Time.h"

Date::Date()
{	
	struct tm *local;
	time_t t;
	t=time(NULL);
	local = localtime(&t);
	year = local->tm_year+1900;
	month = local->tm_mon + 1;
	day = local->tm_mday;
}

Date::Date(string& d)
{
		string y = d.substr(0, 4);
		string m = d.substr(5, 2);
		string da = d.substr(8, 2);
		year = stoi(y);
		if(m[0] == '0')
		{
			month = stoi(m.substr(1, 1));
		}
		else
		{
			month = stoi(m);
		}
		if(da[0] == '0')
		{
			day = stoi(da.substr(1, 1));
		}
		else
		{
			day = stoi(da);
		}
}

bool Date::operator>=(Date& rhs)
{
	if(year > rhs.year)
	{
		return true;
	}
	else if(year < rhs.year)
	{
		return false;
	}
	else
	{
		if(month > rhs.month)
		{
			return true;
		}
		else if(month < rhs.month)
		{
			return false;
		}
		else
		{
			if(day >= rhs.day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool Date::operator<=(Date& rhs)
{
	if(year < rhs.year)
	{
		return true;
	}
	else if(year > rhs.year)
	{
		return false;
	}
	else
	{
		if(month < rhs.year)
		{
			return true;
		}
		else if(month > rhs.year)
		{
			return false;
		}
		else
		{
			if(day <= rhs.day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool Date::student_time()
{
	Date d;
	Date d1 = d;
	d1.SetMonth(6);
	d1.SetDay(1);
	Date d2 = d;
	d2.SetMonth(9);
	d2.SetDay(30);
	Date d3 = d;
	d3.SetMonth(12);
	d3.SetDay(1);
	Date d4 = d;
	int t=d4.get_year() + 1;
	d4.SetDate(t, 3, 31);

	return (((*this)>=d1 && (*this)<=d2) || ((*this)>=d3 && (*this)<=d4)); 
}

Time::Time()
{
	struct tm *local;
	time_t t;
	t=time(NULL);
	local = localtime(&t);
	hour = local->tm_hour;
	minute = local->tm_min;
}

Time::Time(string& t)
{
	string h = t.substr(0, 2);
	string m = t.substr(3, 2);
	if(h[0] == '0')
	{
		hour = stoi(h.substr(1, 1));
	}
	else
	{
		hour = stoi(h);
	}
	if(m[0] == '0')
	{
		minute = stoi(m.substr(1, 1));
	}
	else
	{
		minute = stoi(m);
	}
}

string Date::cvt2String()
	{
		string mysql;
		ostringstream os;
		os << year;
		if(month <10)
		{
			if(day < 10)
			{
				os << 0 << month << 0 << day;
			}
			else
			{
				os << 0 << month << day;
			}
		}
		else
		{
			if(day < 10)
			{
				os << month << 0 << day;
			}
			else
			{
				os << month << day;
			}
		}
		return os.str();
	}

string Date::cvt2String_display()
	{
		string mysql;
		ostringstream os;
		os << year << "-" ;
		if(month <10)
		{
			if(day < 10)
			{
				os << 0 << month << "-" << 0 << day;
			}
			else
			{
				os << 0 << month << "-" << day;
			}
		}
		else
		{
			if(day < 10)
			{
				os << month << "-" << 0 << day;
			}
			else
			{
				os << month << "-" << day;
			}
		}
		return os.str();
	}

string Time::cvt2String()
	{
		string mysql;
		ostringstream os;
		if(hour <10)
		{
			if(minute < 10)
			{
				os << 0 << hour << 0 << minute;
			}
			else
			{
				os << 0 << hour << minute;
			}
		}
		else
		{
			if(minute < 10)
			{
				os << hour << 0 << minute;
			}
			else
			{
				os << hour << minute;
			}
		}
		os << 0 << 0;
		return os.str();
	}

string Time::cvt2String_display()
{
	string mysql;
	ostringstream os;
	if(hour <10)
	{
		if(minute < 10)
		{
			os << 0 << hour << ":" << 0 << minute;
		}
		else
		{
			os << 0 << hour << ":" << minute;
		}
	}
	else
	{
		if(minute < 10)
		{
			os << hour << ":" << 0 << minute;
		}
		else
		{
			os << hour << ":" << minute;
		}
	}
	os << ":" << 0 << 0;
	return os.str();
}