#include<iostream>
#include<stack>
#include"Graph.h"
using namespace std;
int main()
{
	Graphlnk<int>G;
	cin >> G;//0 1 0 3 1 2 2 3 3 4 4 0
	cout << "ͼ��������ȱ���" << endl;
	G.DFS(0);
	cout << "\nͼ���ڽӾ����ʾΪ" << endl;
	G.GraphMatrix();
	system("pause");
	return 0;
}
