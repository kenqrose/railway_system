#ifndef SEAT_H_
#define SEAT_H_
#include <iostream>
#include <string>

using namespace std;

class Seat
{
public:
	int carriage_type;//�������ͣ�0ΪӲ����1Ϊ����
	int carriage_number;//�������
	int seat_type;//��λ���ͣ���ΪӲ����ֻ��0����Ϊ���̣�0,1,2�ֱ�Ϊ����������
	int seat_number;//��λ���1-120��1-20
	Seat(int ct, int cn, int st, int sn):carriage_type(ct), carriage_number(cn), seat_type(st), seat_number(sn){};
	string cvt2String();//ת��ΪMySQL����ĸ�ʽ
	string cvt2String_check();//ת��Ϊ���ڼ���MySQL����ĸ�ʽ
};

#endif