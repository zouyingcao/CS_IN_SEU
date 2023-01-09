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
			while (temp > L[c] && c <= right)	//���ţ���temp��λ��ʹ֮���������������ź���
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
	int mid = (left + right) / 2;	//�м��
	MergeSort(n,L, left, mid);		//��������
	MergeSort(n,L, mid + 1, right);	//��������
	//merge(L, left, mid, right);	//����ǰ�ĺϲ�
	merge1(L, left, mid, right);	//�����ĺϲ�
	if (n == 10) 
	{
		cout << "\n����left:" << left << ",mid:" << mid << ",right:" << right << ",�鲢����:";
		output(L, 10);
	}
}
void CountSort(T *arr,int len)
{
	T max = arr[0];//��¼���е����ֵ
	T min = arr[0];//��¼���е���Сֵ
	for (int i = 0; i < len; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	int l = max - min+1;//��������������Сֵ�ò�ֵ
	int* count = new int[l];
	for (int i = 0; i < l; i++)
		count[i] = 0;
	for (int i = 0; i < len; i++)
		count[arr[i] - min]++;//ͳ��Ԫ�ظ���
	for (int i = 1; i < l; i++)//ͳ�����������Σ������Ԫ�ص���ǰ��Ԫ�صĺ�
		count[i] += count[i-1];
	int* result = new int[len];
	for (int i = 0; i < len; i++)
	{
		result[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}
	cout << "\n�����"<<endl;
	output(result, len);
}
void execCH6_3_1()
{
	cout << "------- ������ MergeSort -------\n\n";
	int j;
	int key[] = { 42,68,35,1,70,25,79,59,63,65 };
	CMN = 0; RMN = 0; SWN = 0;
	cout << "��ʼ����:";
	for (j = 0; j < 10; j++)
		cout << key[j] << ' ';
	MergeSort(10,key, 0, 9);
	cout << "\n10��Ԫ�ص���·�鲢������,�Ƚϴ��� : " << CMN << ", �ƶ����� : " << RMN << "���������� : " << SWN << "\n";
	cout << "����֮��: ";
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
		cout << "\n\n......... ������ MergeSort .........\n"
		<< n[j]<< "��Ԫ�أ��Ƚϴ��� : " << CMN << ", �ƶ����� : " << RMN << "���������� : " << SWN;
	}
}
void execCH6_2()
{
	srand((unsigned)time(NULL));
	int n = rand() % 90 + 10;
	int *key=new int[n];
	for (int i = 0; i < n; i++)
		key[i] = (rand() % 99900) + 100;
	cout << "\n\n---------- �������� ----------" << endl;
	cout << "����ǰ:"<<endl;
	output(key, n);
	CountSort(key, n);
	cout << endl;
}
void minHeapSort(MinHeap<T> &minH, T*& dH, int nn)	//��С������
{
	minH.HeapSort(dH, nn);
}
void display(T *& dH, int nn)						//��ʾ������
{	
	for (int i = 0; i < nn; i++)
		cout << dH[i] << " ";
	cout << endl;
}
bool isMinHeap(T * heap, int size)					//�ж���ǰԪ���Ƿ񹹳���С��
{
	for (int i = 0; i <= (size - 2)/2; i++)
		if (heap[i] > heap[2 * i + 1] || (heap[i] > heap[2 * i + 2]&& 2 * i + 2<size))  return false;
	return true;
}
void Isminheap(T * dH, int nn)
{
	bool t;
	t = isMinHeap(dH, nn);
	if (t == false)cout << "�����в�����С��.\n";
	else cout << "����������С��.\n";
}
void execCH6_4()
{
	int n = 10;
	T* dHeap = new T[n];
	for (int i = 0; i < n; i++)dHeap[i] = 1 + rand() % MAXINT;
	cout << "��ʼ����:"; display(dHeap, n);
	Isminheap(dHeap, n);
	MinHeap<T> mheap(dHeap, n);
	minHeapSort(mheap, dHeap, n);
	cout << "\n�����:"; display(dHeap, n);
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
