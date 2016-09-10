#ifndef USER_H_
#define USER_H_
#include "Class_Time.h"
#include <mysql.h>
#include "Class_MySQL_API.h"
#include "Class_Train.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <regex>//ʹ��������ʽ
using namespace std;

class User
{
private:
	string account;//�û��˻�����(6,14]λ���ɰ������֣���ĸ��Сд���»���
	string password;//�û����룺(6,10]λ���ɰ������֣���ĸ��Сд���»���
	int status;//�û������û��飬0Ϊ����Ա��1Ϊ�ÿ�,2Ϊ�޴��û���3Ϊδ���״̬
public:
	User(){};//���캯������Ӧû�е�¼�����
	User(string& a, string& p):account(a), password(p), status(3){};//���캯��������ǰ���˻�����
	User(User& u):account(u.account), password(u.password), status(3){};//���ƹ��캯��
	virtual ~User(){};//����������
	string& get_account(){return account;}
	int getstatus(){return status;}//��ʾ�û������û���
	void check_account(sql_ptr& );//����˻������û���
	bool check_password(sql_ptr& );//�������
	void register_account(sql_ptr& );//ע���˺�
	bool change_password(sql_ptr& );//�޸�����
	int check_acc_repetition(sql_ptr&);//�����ڴ����ÿ��û�ʱ����û��Ƿ��Ѵ���
	//vector<Train> find_train(sql_ptr&, string&, string&, Date& = Date(), int = 0, int = 0);//���ҳ�����Ϣ���Ȳ����Ǹ���ʱ��ɸѡ��
	friend class Admin;
	friend class Passenger;
	virtual void show(){cout << "This is User" << endl;}
	//virtual bool add_train() = 0;
};

#endif