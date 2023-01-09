#ifndef HEAP_H
#define HEAP_H
#include<iostream>
const int DefaultSize = 20;
using namespace std;
static size_t CMN, RMN, SWN;

template<class E>
class MinHeap
{
public:
	MinHeap(int sz = DefaultSize);
	MinHeap(E *arr, int n);
	~MinHeap() { delete[]heap; }
	void output(int,int);
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	void HeapSort(E*& dH, int nn);
	bool isEmpty()const
	{
		return(currentSize == 0) ? true : false;
	}
	bool isFull()const
	{
		return(currentSize == maxHeapSize) ? true : false;
	}
	void MakeEmpty() { currentSize = 0; }
	int getSize() { return currentSize; }
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};
template<class E>
MinHeap<E>::MinHeap(int sz)
{
	CMN = 0; RMN = 0; SWN = 0;
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) { cerr << "堆存储分配失败！" << endl; exit(1); }
	currentSize = 0;
}
template<class E>
MinHeap<E>::MinHeap(E *arr, int n)
{
	CMN = 0; RMN = 0; SWN = 0;
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) { cerr << "堆存储分配失败！" << endl; exit(1); }
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
	cout << "初始最小堆: ";
	output(0,currentSize);
	cout <<"\n\n";
}
template<class E>
void MinHeap<E>::output(int start,int n)
{
	for (int i = 0; i < n; i++)
		cout << heap[i] << "  ";
}
template<class E>
void MinHeap<E>::siftDown(int start, int m) //从start到m下滑调整成为最小堆
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		CMN++;
		if (j<m && heap[j]>heap[j + 1])j++;//取左右子女结点中较小的一个
		CMN++;
		if (temp <= heap[j]) break;
		else { 
			cout << "  " << heap[i] << "<-" << heap[j] << "  ";
			heap[i] = heap[j]; RMN++; 
			i = j; j = 2 * j + 1; 
		}
	}
	cout << "  " << temp << "->" << heap[i] << endl; 
	heap[i] = temp; SWN++;
}
template<class E>
void MinHeap<E>::siftUp(int start)	//从start到0上滑调整成为最小堆
{
	int j = start, i = (j - 1) / 2; E temp = heap[j];
	while (j > 0) {
		if (heap[i] <= temp)break;
		else { heap[j] = heap[i]; j = i; i = (i - 1) / 2; }//父节点值大
	}
	heap[j] = temp;
}
template<class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == maxHeapSize)		//堆满
	{
		cerr << "Heap Full" << endl; return false;
	}
	heap[currentSize] = x;			//插入
	siftUp(currentSize);			//向上调整
	currentSize++;					//堆计数加一
	return true;
}
template<class E>
bool MinHeap<E>::RemoveMin(E& x)
{
	if (!currentSize) {
		cout << "Heap empty" << endl; return false;
	}
	x = heap[0]; heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}
template<class E>
void MinHeap<E>::HeapSort(E *&dH,int nn)
{
	int k = 0;
	for (int i = nn - 1; i >= 0; i--)
	{
		cout << "第" << k << "趟";
		output(0, i+1);
		cout << "累计:比较" << CMN << "次，移动" << RMN << "次,交换" << SWN << "次数" << endl;
		dH[k] = heap[0]; k++;
		E temp = heap[i]; heap[i] = heap[0]; heap[0] = temp;
		siftDown(0, i - 1);
	}
}
#endif 