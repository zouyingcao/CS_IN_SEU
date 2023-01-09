#include<iostream>
#include<stack>
#include"Graph.h"
using namespace std;
int main()
{
	Graphlnk<int>G;
	cin >> G;//0 1 0 3 1 2 2 3 3 4 4 0
	cout << "图的深度优先遍历" << endl;
	G.DFS(0);
	cout << "\n图的邻接矩阵表示为" << endl;
	G.GraphMatrix();
	system("pause");
	return 0;
}
