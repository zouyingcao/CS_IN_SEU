#include<iostream>
#include<fstream>
typedef int T;
#include"AVL.h"
using namespace std;
void execCH7_3()
{
	fstream inAVL("inAVL1.txt");
	if (!inAVL) { cerr << "�ļ�inAVL���д�.\n" << endl; exit(1); }
	fstream outAVL("outAVL.txt");
	if (!outAVL) { cerr << "�ļ�outAVL���д�.\n" << endl; exit(1); }
	AVL<int,int> avlTree;
	cout << "���ļ�����һ��AVL��.\n\n";
	avlTree.createAVL(inAVL);
	avlTree.outputAVL(outAVL);
	cout << "\n AVL��:\n";
	avlTree.displayAVL();
	T tmpKey;
	bool isFind;
	for (int j = 0; j <= 1; j++)
	{
		cout << "\n����һ�����ҵ�ֵ��";
		cin >> tmpKey;
		isFind = avlTree.Search(tmpKey);
		if (isFind)cout << "\n��AVL�����ҵ�" << tmpKey << endl;
		else cout << "\nAVL����û��" << tmpKey << endl;
	}
	inAVL.close(); outAVL.close();
}
int main()
{
	execCH7_3();
	system("pause");
	return 0;
}