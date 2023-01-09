#include<iostream>
#include<time.h>
#include"minheap.h"
using namespace std;
typedef int T;
#define MAXINT 1000
//static size_t CMN, RMN, SWN;

void output(T* L, const int n)
{
	for (int i = 0; i < n; i++)
		cout << L[i] << ' ';
}
void merge(T* L, const int left,const int mid, const int right)
{
	int s1 = left, s2 = mid +1, t = left;
	T* tempL = new T[right + 1];
	for (int i = left; i <= right; i++)
		tempL[i] = L[i];
	while (s1 <= mid&&s2<=right)
	{
		CMN++;
		if (tempL[s1] <= tempL[s2]) {
			L[t++] = tempL[s1++]; RMN++;
		}
		else { L[t++] = tempL[s2++]; RMN++; }
	}
	while (s1 <= mid) { L[t++] = tempL[s1++]; RMN++;}
	while (s2 <= right) { L[t++] = tempL[s2++]; RMN++;}
}
void merge1(T* L, const int left, const int mid, const int right)
{
	int s1 = left, s2 = mid + 1;
	while (s1 <= mid)
	{
		CMN++; 
		if (L[s1] > L[s2])
		{
			SWN++;
			T temp = L[s1];
			L[s1] = L[s2];
			int c = s2 + 1;	
			CMN++;
			while (temp > L[c] && c <= right)	//插排，找temp的位置使之在右子序列中仍排好序
			{
				L[c - 1] = L[c]; RMN++; CMN++;
				c++;
			}
			L[c - 1] = temp;  
		}
		s1++;
	}
}
int min(int a,int b)
{
	if (a < b)return a;
	else return b;
}
void MergeSort(int n,T* L, const int left, const int right)
{
	if (left >= right)return;
	int mid = (left + right) / 2;	//中间点
	MergeSort(n,L, left, mid);		//左子序列
	MergeSort(n,L, mid + 1, right);	//右子序列
	//merge(L, left, mid, right);	//改造前的合并
	merge1(L, left, mid, right);	//改造后的合并
	if (n == 10) 
	{
		cout << "\n本趟left:" << left << ",mid:" << mid << ",right:" << right << ",归并序列:";
		output(L, 10);
	}
}
void CountSort(T *arr,int len)
{
	T max = arr[0];//记录数列的最大值
	T min = arr[0];//记录数列的最小值
	for (int i = 0; i < len; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	int l = max - min+1;//计算出数列最大最小值得差值
	int* count = new int[l];
	for (int i = 0; i < l; i++)
		count[i] = 0;
	for (int i = 0; i < len; i++)
		count[arr[i] - min]++;//统计元素个数
	for (int i = 1; i < l; i++)//统计数组做变形，后面的元素等于前面元素的和
		count[i] += count[i-1];
	int* result = new int[len];
	for (int i = 0; i < len; i++)
	{
		result[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}
	cout << "\n排序后："<<endl;
	output(result, len);
}
void execCH6_3_1()
{
	cout << "------- 改造后的 MergeSort -------\n\n";
	int j;
	int key[] = { 42,68,35,1,70,25,79,59,63,65 };
	CMN = 0; RMN = 0; SWN = 0;
	cout << "初始序列:";
	for (j = 0; j < 10; j++)
		cout << key[j] << ' ';
	MergeSort(10,key, 0, 9);
	cout << "\n10个元素的两路归并排序中,比较次数 : " << CMN << ", 移动次数 : " << RMN << "，交换次数 : " << SWN << "\n";
	cout << "排序之后: ";
	output(key, 10);
}
void execCH6_3_2()
{
	int n[7] = { 10,50,100,500,1000,5000,10000 };
	for (int j = 0; j < 7; j++)
	{
		int key[10000];
		srand((unsigned)time(NULL));
		for (int i = 0; i < n[j]; i++)
			key[i] = (rand() % 100) + 1;
		CMN = 0; RMN = 0; SWN = 0;
		MergeSort(0,key, 0, n[j] - 1);
		cout << "\n\n......... 改造后的 MergeSort .........\n"
		<< n[j]<< "个元素，比较次数 : " << CMN << ", 移动次数 : " << RMN << "，交换次数 : " << SWN;
	}
}
void execCH6_2()
{
	srand((unsigned)time(NULL));
	int n = rand() % 90 + 10;
	int *key=new int[n];
	for (int i = 0; i < n; i++)
		key[i] = (rand() % 99900) + 100;
	cout << "\n\n---------- 计数排序 ----------" << endl;
	cout << "排序前:"<<endl;
	output(key, n);
	CountSort(key, n);
	cout << endl;
}
void minHeapSort(MinHeap<T> &minH, T*& dH, int nn)	//最小堆排序
{
	minH.HeapSort(dH, nn);
}
void display(T *& dH, int nn)						//显示排序结果
{	
	for (int i = 0; i < nn; i++)
		cout << dH[i] << " ";
	cout << endl;
}
bool isMinHeap(T * heap, int size)					//判定当前元素是否构成最小堆
{
	for (int i = 0; i <= (size - 2)/2; i++)
		if (heap[i] > heap[2 * i + 1] || (heap[i] > heap[2 * i + 2]&& 2 * i + 2<size))  return false;
	return true;
}
void Isminheap(T * dH, int nn)
{
	bool t;
	t = isMinHeap(dH, nn);
	if (t == false)cout << "该序列不是最小堆.\n";
	else cout << "该序列是最小堆.\n";
}
void execCH6_4()
{
	int n = 10;
	T* dHeap = new T[n];
	for (int i = 0; i < n; i++)dHeap[i] = 1 + rand() % MAXINT;
	cout << "初始序列:"; display(dHeap, n);
	Isminheap(dHeap, n);
	MinHeap<T> mheap(dHeap, n);
	minHeapSort(mheap, dHeap, n);
	cout << "\n排序后:"; display(dHeap, n);
	Isminheap(dHeap, n);
	delete[]dHeap;
	cout << '\n';
}
int main()
{
	//execCH6_3_1();
	//execCH6_3_2();
	//execCH6_2();
	execCH6_4();
	system("pause");
	return 0;
}
