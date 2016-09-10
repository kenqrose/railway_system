#ifndef MYSQL_API_H_
#define MYSQL_API_H_
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Class_Time.h"
#include <mysql.h> 
#include "Class_Seat.h"

using namespace std;
//std::tr1::shared_ptr<MySQL_API> Create_MySQL_API(string&, string&, string&, string&, unsigned int);
//class Train;

class MySQL_API
{
private:
	const string user;
	const string pswd;
	const string host;
	const string table;
	unsigned int port;
	//MYSQL mysql_handle;
	//MYSQL_RES *mysql_result;
	//MYSQL_ROW mysql_row;
	//MYSQL_FIELD *mysql_field;
public:
	MYSQL mysql_handle;
	MYSQL_RES *mysql_result;
    MYSQL_ROW mysql_row;
    MYSQL_FIELD *mysql_field;
	MySQL_API(string&, string&, string&, string&, unsigned int);//���� 
	~MySQL_API(){mysql_close(&mysql_handle);}//����
	bool Connection();
	int db_check_account(string& a);//�����ݿ����û������飬0Ϊ����Ա��1Ϊ�ÿͣ�2Ϊ�޴��û�����Ϊ1��2����˵�����˻��ظ�
	bool db_check_id_repetition(string&, string&);//������֤����Ϣ�Ƿ��ظ�
	bool db_check_pswd_admin(string&, string&);//�����ݿ������Ա�˻��Ƿ���ȷ
	bool db_check_pswd_passenger(string&, string&);//�����ݿ����ÿ��˻��Ƿ���ȷ
	bool db_check_train_30min(string&, int);//��鵱ǰʱ���Ƿ��뷢��ʱ��30��������
	bool db_create_passenger(string&, string&, string&, int, Date&, string&, string&, string&, int, double = 0);//�����ݿ�����ÿ��˻�
	bool db_create_admin(string&, string&, string&, int, Date&, string&, string&, string&, int);//�����ݿ���ӹ���Ա�˻�
	bool db_create_train();//�����ݿ�����г�����
	bool db_create_seat_table(string&);//�����ݿ��д�����λ��
	bool db_create_deal(string&, string&, string&, string&, Date&, Time&, Seat&, int, int, int = 0);//��Ӷ�����Ϣ
	bool db_change_pswd_passenger(string&, string&);//�������ݿ��޸��ÿ�����
	bool db_change_pswd_admin(string&, string&);//�������ݿ��޸Ĺ���Ա����
	bool db_add_train(string&, int, int, int, string&, string&, Date&, Time&, Time&, float, float);//��ӳ�����Ϣ
	bool db_add_seat(string&, Seat&, string&, Date&);//�ڶ�Ӧ�г���λ���������λ
	bool db_seat_sold(string&, Seat&, Date&);//�����λ�Ƿ��ѱ�ռ��
	bool db_update_passenger(string&, int, Date&, string&, string&, string&, int, double);//�����ÿ��û���Ϣ
	bool db_update_train(string&, int, int, int, string&, string&, Date&, Time&, Time&, float, float);//���³�����Ϣ
	bool db_update_seat_remain(string&, int, Seat&, Date&);//������λʣ����Ϣ
	bool db_update_balance(string&, double);//�����û�����Ǯ�������Ϣ
	bool db_not_bought(string& account, string& serial, Date& departure_date, Seat& seat);//����û��Ƿ��ѹ���˳���Ʊ
	bool db_remain_ticket(string& serial_number, int train_type, Date& departure_date, Seat& s);//�����ѡ�����Ƿ�����Ʊ
	bool db_delete_passenger(string& account);//�����ݿ�ɾ���ÿ�ע����Ϣ
	bool db_delete_train(string&, int);//�����ݿ�ɾ���г���Ϣ
	bool db_delete_seat_table(string& serial_st);//�����ݿ���ɾ����λ��Ϣ������ɾ���г���Ϣ֮��
	bool db_delete_deal(string& serial, string& account, Date& departure_date);//ɾ������
	bool db_delete_seat(string& serial_st, string& account);//ɾ����λ��Ϣ������ɾ������֮��

	vector<string> db_get_info_passenger(string&);//�����û��������ݿ�����ȡ������Ϣ
	vector<string> db_get_info_admin(string&);//�����û��������ݿ�����ȡ������Ϣ
	vector<string> db_find_train(string&, string&, Date&, int = 0, int = 0);//�����ݿ��в��ҳ�����Ϣ
	vector<string> db_get_deal();//�����ݿ��в������ж�����Ϣ
	vector<string> db_get_deal(string& );//�����û������Ҷ�����Ϣ
	vector<string> db_get_deal(Date&);//�������ڲ��Ҷ�����Ϣ
};
typedef std::tr1::shared_ptr<MySQL_API> sql_ptr;
sql_ptr Create_MySQL_API(string& u=string("root"), string& p=string("root"), string& h=string("localhost"), string& t=string("railway"), unsigned int po=3306);
#endif