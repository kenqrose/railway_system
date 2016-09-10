#ifndef SEAT_H_
#define SEAT_H_
#include <iostream>
#include <string>

using namespace std;

class Seat
{
public:
	int carriage_type;//车厢类型：0为硬座，1为卧铺
	int carriage_number;//车厢序号
	int seat_type;//座位类型：若为硬座，只有0；若为卧铺，0,1,2分别为上中下三种
	int seat_number;//座位序号1-120或1-20
	Seat(int ct, int cn, int st, int sn):carriage_type(ct), carriage_number(cn), seat_type(st), seat_number(sn){};
	string cvt2String();//转换为MySQL命令的格式
	string cvt2String_check();//转换为用于检查的MySQL命令的格式
};

#endif