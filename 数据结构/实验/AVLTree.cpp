#include<iostream>
#include<fstream>
typedef int T;
#include"AVL.h"
using namespace std;
void execCH7_3()
{
	fstream inAVL("inAVL1.txt");
	if (!inAVL) { cerr << "文件inAVL打开有错.\n" << endl; exit(1); }
	fstream outAVL("outAVL.txt");
	if (!outAVL) { cerr << "文件outAVL打开有错.\n" << endl; exit(1); }
	AVL<int,int> avlTree;
	cout << "从文件创建一棵AVL树.\n\n";
	avlTree.createAVL(inAVL);
	avlTree.outputAVL(outAVL);
	cout << "\n AVL树:\n";
	avlTree.displayAVL();
	T tmpKey;
	bool isFind;
	for (int j = 0; j <= 1; j++)
	{
		cout << "\n输入一个查找的值：";
		cin >> tmpKey;
		isFind = avlTree.Search(tmpKey);
		if (isFind)cout << "\n在AVL树中找到" << tmpKey << endl;
		else cout << "\nAVL树中没有" << tmpKey << endl;
	}
	inAVL.close(); outAVL.close();
}
int main()
{
	execCH7_3();
	system("pause");
	return 0;
}