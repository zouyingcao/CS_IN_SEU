#include<iostream>
#include"Polynomal.h"
using namespace std;
int main()
{
	Polynomal a;
	cin >> a;
	cout << "���ʽaΪ:";
	cout << a;
	cout << "���ʽa����߽�Ϊ:";
	cout << a.maxOrder() << endl;
	cout << "��x=5ʱ��������ʽa��ֵΪ:"<<a.Evaluate(5.0)<<endl;
	Polynomal b(a),c;
	cout << "���ÿ������캯����ʼ��b�����ʽbΪ:";
	cout << b;
	cout << "���ʽa��b��Ӻ�ֵ�����ʽc�����ʽcΪ:";
	c = a + b;
	cout << c;
	cout << "���ʽa�����ʽc�����Ϊ:";
	cout << a - c;
	cout << "���ʽa��b�������Ϊ:";
	c = a - b;
	cout << c;
	cout << "���ʽa��b��˺���Ϊ:";
	c = a * b;
	cout << c;
	system("pause");
	return 0;
}