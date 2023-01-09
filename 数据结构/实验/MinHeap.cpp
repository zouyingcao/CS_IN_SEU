#include<iostream>
#include"MinHeap.h"
using namespace std;

int main()
{
	MinHeap<int> heap(100000);
	for (int i = 100000; i >0; i--)
		heap.Insert(i);
	cout << "十万个数中选取前10个最小数为:" << endl;
	for(int i=0;i<10;i++)
	{
		int x;
		if (heap.RemoveMin(x))cout << x<<" ";
	}
	system("pause");
	return 0;
}