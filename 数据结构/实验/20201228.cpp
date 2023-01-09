#include<iostream>
#include<fstream>
#include<time.h>
#include <Windows.h>
#include"Huffman.h"
using namespace std;
void testBubbleSort();
void testSort();
void testHuffmanTree();
void BubbleSort(int*, int, int);
template<class E>
void ImprovedQuickSort(E*& ,int,int);
template<class E>
void InsertSort(E*&, int, int);
template<class E>
int Partition1(E*&, const int, const int);
template<class E>
E median3(E*&, const int, const int);
void Swap(int &, int &);
void output(int*,int);

int cmpNum=0;
int main()
{
	testHuffmanTree();
	testSort();
	system("pause");
	return 0;
}

void testHuffmanTree()
{
	float c[26]; 
	char text[1000];
	ifstream in("TXT.txt");
	for (int i = 0; i < 1000; i++)
		in >> text[i];

	for (int i = 0; i < 26; i++)
		c[i] = 0.0;
	for (int i = 0; i < strlen(text); i++)		//text[i]='a'时id=0
		c[text[i] - 97]++;
	cout << "利用text中英文字符串各字符出现频度构建一棵Huffman树."<<endl;
	HuffmanTree HTree(c, 26);
	HTree.Coding();
	HTree.printCode();
	HTree.Encode();
}
void testSort()
{
	MinHeap<int> hp(200000);//20万
	int *key=new int[200000];
	for (int i = 0; i < 100000; i++)
	{	
		key[i] = (rand() % 100000) + 1;
		hp.Insert(key[i]);
	}
	int *k=new int[10];
	hp.HeapSort(k, hp.getSize());
	cout << "前10个最小的数为:";
	for (int i = 0; i < 10; i++)
		cout << k[i] << " ";
	cout << endl;
	ImprovedQuickSort(key, 0, 100000 - 1);
	InsertSort(key, 0, 100000-1);
	cout << "改进的快速-直接插入混合排序算法中比较次数:" << cmpNum << endl;
	cout << "前10个最小的数为:";
	for (int i = 0; i < 10; i++)
		cout << key[i] << " ";
}
void output(int	*a,int n)
{
	for (int i = 0; i < n; i++)
		cout<< a[i]<<" ";
	cout << endl;
}
void BubbleSort(int* a, int left, int right)
{
	int pass = left + 1, exchange = 1;
	while (pass <= right && exchange)
	{
		exchange = 0; //标志为0假定未交换
		for (int j = right; j >= pass; j--)
			if (a[j - 1] > a[j]) //逆序
			{
				Swap(a[j - 1], a[j]); //交换
				exchange = 1; //标志置为1,有交换
			}
		pass++;
	}
}
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

template<class E>
void ImprovedQuickSort(E *&key, const int left, const int right)
{
	if (right - left <= 25)return;
	int pivotpos = Partition1(key, left, right);
	ImprovedQuickSort(key, left, pivotpos - 1);
	ImprovedQuickSort(key, pivotpos + 1, right);
}
template<class E>
void InsertSort(E*& key, int left, int right)
{
	E temp; int i, j;
	for(i=left+1;i<=right;i++)
	{ 
		cmpNum++;
		if (key[i] < key[i - 1])
		{
			temp = key[i]; j = i - 1;
			do {
				key[j + 1] = key[j]; j--; cmpNum++;
			} while (j >= left && temp < key[j]);
			key[j + 1] = temp;
		}
	}
}
template<class E>
E median3(E *&key, const int left, const int right)
{
	int mid = (left + right) / 2; int k = left;
	if (key[mid] < key[k])k = mid; cmpNum++;
	if (key[right] < key[k])k = right; cmpNum++;
	if (k != left) {									//最小值交换到left
		E temp = key[k]; key[k] = key[left]; key[left] = temp;
	}
	cmpNum++;
	if (mid != right && key[mid] < key[right]) {
		E temp = key[mid]; key[mid] = key[right]; key[right] = temp;
	}												//key[mid]为中间值，交换到right位置
	return key[right];								//否则，right位置本来就是中间值
}
template<class E>
int Partition1(E *&key, const int left, const int right)
{
	int i = left, j = right - 1;
	if (left < right) {
		E pivot = median3(key, left, right);		//三者中取中间值
		while (1)
		{
			cmpNum += 2;
			while (i < j && key[i] < pivot) { i++; cmpNum++; }	//小于pivot的留在左边
			while (j > i && pivot < key[j]) { j--; cmpNum++; }	//大于pivot的留在右边
			if (i < j)
			{
				E temp = key[i]; key[i] = key[j]; key[j] = temp;
				i++; j--;
			}
			else break;
		}
		cmpNum++;
		if (key[i] > pivot)
		{
			key[right] = key[i]; key[i] = pivot;	//pivot移到它排序后应该在的位置
		}
	}
	return i;										//返回基准元素位置
}
void testBubbleSort()
{
	int n;
	cout << "输入待排序的数据有多少个:" << endl; cin >> n;
	cout << "排序前的数据:" << endl;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	BubbleSort(a, 0, n - 1);

	QueryPerformanceCounter(&end);

	cout << "排序后的数据:" << endl;
	output(a, n);
	cout << "运行时间：" << (end.QuadPart - start.QuadPart) * 1.0 / freq.QuadPart << endl;
}