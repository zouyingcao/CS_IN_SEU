#include<iostream>
#include"MinHeap.h"
using namespace std;

int main()
{
	MinHeap<int> heap(100000);
	for (int i = 100000; i >0; i--)
		heap.Insert(i);
	cout << "ʮ�������ѡȡǰ10����С��Ϊ:" << endl;
	for(int i=0;i<10;i++)
	{
		int x;
		if (heap.RemoveMin(x))cout << x<<" ";
	}
	system("pause");
	return 0;
}