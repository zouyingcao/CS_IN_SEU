#include<iostream>
#include"Polynomal.h"
using namespace std;
int main()
{
	Polynomal a;
	cin >> a;
	cout << "表达式a为:";
	cout << a;
	cout << "表达式a的最高阶为:";
	cout << a.maxOrder() << endl;
	cout << "当x=5时，计算表达式a的值为:"<<a.Evaluate(5.0)<<endl;
	Polynomal b(a),c;
	cout << "调用拷贝构造函数初始化b，表达式b为:";
	cout << b;
	cout << "表达式a与b相加后赋值给表达式c，表达式c为:";
	c = a + b;
	cout << c;
	cout << "表达式a减表达式c，结果为:";
	cout << a - c;
	cout << "表达式a与b相减后结果为:";
	c = a - b;
	cout << c;
	cout << "表达式a与b相乘后结果为:";
	c = a * b;
	cout << c;
	system("pause");
	return 0;
}