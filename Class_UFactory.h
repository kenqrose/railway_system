#ifndef UFACTORY_H_
#define UFACTORY_H_
#include "Class_MySQL_API.h"
#include "Class_Train.h"
#include "Class_Seat.h"
#include "Class_Deal.h"
#include "Class_User.h"

class UFactory
{
public:
	User u;
	virtual bool buy_ticket(Train&, Seat&, sql_ptr&, Date&,int) = 0;
	virtual void show() = 0;
	virtual bool create_deal(sql_ptr&, Train&, Seat&, Date&) = 0;
	virtual bool add_train(sql_ptr&, Train&) = 0;
	virtual bool top_up(sql_ptr&, double) = 0;
	virtual ~UFactory(){}
	vector<Train> find_train(sql_ptr&, string&, string&, Date& = Date(), int = 0, int = 0);
	vector<Deal> get_deal(sql_ptr&);//���ȫ��������Ϣ
	vector<Deal> get_deal(sql_ptr&, string&);//���ָ���ÿ͵Ķ�����Ϣ
	vector<Deal> get_deal(sql_ptr&, Date&);//���ָ�����ڵĶ�����Ϣ
};
//��¼�������õ���¼�û��Ŀ��ƾ��
namespace UFact
{
shared_ptr<UFactory> login(User& u, sql_ptr& p);
shared_ptr<UFactory> login(string& account, string& password, sql_ptr& p);
bool logout(shared_ptr<UFactory>);
shared_ptr<UFactory> switch_user(shared_ptr<UFactory>&, string&, string&, sql_ptr& );
//�����ݿ���ע���˺ţ�����������ݸ�ʽ��飬���ص�ǰ���£�
bool register_account(sql_ptr& p, string& account, string& password, string& name,  int gender, Date& birthday, string& type_of_certificate, string& id_card, string& phone_number, int is_student = 0, double balance = 0);
}
#endif