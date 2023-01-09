#include<iostream>
#include<time.h>
using namespace std;
int Partition(int,int [],const int,const int);
void BiInsertSort(int [],const int,int);
void ShellSort(int [],const int ,const int);
void QuickSort(int ,int [],const int,const int);
void execCH6_2_1();
void execCH6_2_2();
void ImprovedQuickSort(int[], const int, const int);
int median3(int[], const int, const int);
int Partition1(int[], const int, const int);
void execCH6_1();
int cmpNum = 0, movNum = 0, swapNum = 0;
int main()
{
	execCH6_2_1();
	execCH6_2_2();
	execCH6_1();
	system("pause");
	return 0;
}
void execCH6_1()
{
	int n[10] = { 1000,2000,3000,4000,5000,6000,7000,8000,9000,10000 };
	for (int j = 0; j < 10; j++)
	{
		cout << "����һ��˳������ռ�Ϊ:" << n[j] << endl;
		int key[10000]; int zf[2] = { 1,-1 };
		srand((unsigned)time(NULL));
		for (int i = 0; i < n[j]; i++)
			key[i] = zf[(rand() % 2)]*((rand() % 100) + 1);
		cmpNum = 0;
		ImprovedQuickSort( key, 0, n[j] - 1);
		cout << "ImprovedQuickSort�㷨��:�Ƚϴ���:" << cmpNum<< "\n";
	}
}
void execCH6_2_1()
{
	int j;
	int key1[] = { 42,68,35,1,70,25,79,59,63,65 };
	cmpNum = 0; movNum = 0; swapNum = 0;
	cout << "SL4 BiInsertSort\n��ʼ����:";
	for (j = 0; j < 10; j++)
		cout << ' ' << key1[j];
	BiInsertSort(key1, 0, 9);
	cout << "\n\nSL4�����:";
	for (j = 0; j < 10; j++)
		cout << ' ' << key1[j];
	cout << "\nBiInsertSort�㷨��,�Ƚϴ��� : " <<cmpNum<< ", �ƶ����� : "<<movNum<<"���������� : "<<swapNum<<"\n";

	int key2[] = { 42,68,35,1,70,25,79,59,63,65 };
	cmpNum = 0; movNum = 0; swapNum = 0;
	cout << "\nSL5 ShellSort\n��ʼ����:";
		for (j = 0; j < 10; j++)
			cout << ' ' << key2[j];
	ShellSort(key2, 0, 9);
	cout << "\n\nSL5�����:";
	for (j = 0; j < 10; j++)
		cout << ' ' << key2[j];
	cout << "\nShellSort�㷨�У��Ƚϴ���:" << cmpNum << ",�ƶ�����:" << movNum << "����������:" << swapNum << "\n";

	int key3[] = { 42,68,35,1,70,25,79,59,63,65 };
	cmpNum = 0; movNum = 0; swapNum = 0;
	cout << "\nSL6 QuickSort\n��ʼ����:";
	for (j = 0; j < 10; j++)
		cout << ' ' << key3[j];
	QuickSort(10,key3, 0, 9);
	cout << "\n\nSL6�����:";
	for (j= 0; j < 10; j++)
		cout << ' ' << key3[j];
	cout << "\nQuickSort�㷨�У��Ƚϴ���:" << cmpNum << ",�ƶ�����:" << movNum << "����������:" << swapNum << "\n";
}
void execCH6_2_2()
{
	int n[6] = { 50,100,500,1000,5000,10000 };
	for (int j = 0; j < 6; j++)
	{
		cout << "����һ��˳������ռ�Ϊ:" << n[j]
			<< "\n��ǰ������Ԫ�أ��浽date[0]...data[" << n[j] << "]֮��.\n\n";
		int key[10000], key1[10000], key2[10000], key3[10000];
		srand((unsigned)time(NULL));
		for (int i = 0; i < n[j]; i++)
			key[i] = (rand() % 100) + 1;
		for (int i = 0; i < n[j]; i++)
		{
			key1[i] = key[i];
			key2[i] = key[i];
			key3[i] = key[i];
		}
		cmpNum = 0; movNum = 0; swapNum = 0;
		BiInsertSort(key1, 0, n[j]-1);
		cout<<"SL4 BiInsertSort�㷨��:\n�Ƚϴ���:" << cmpNum << ",�ƶ�����:" << movNum << "����������:" << swapNum << "\n";
		cmpNum = 0; movNum = 0; swapNum = 0;
		ShellSort(key2, 0, n[j] - 1);
		cout << "SL5 ShellSort�㷨��:\n�Ƚϴ���:" << cmpNum << ",�ƶ�����:" << movNum << "����������:" << swapNum << "\n";
		cmpNum = 0; movNum = 0; swapNum = 0;
		QuickSort(n[j],key3, 0, n[j] - 1);
		cout << "SL6 QuickSort�㷨��:\n�Ƚϴ���:" << cmpNum << ",�ƶ�����:" << movNum << "����������:" << swapNum << "\n\n\n";
	}
}
void BiInsertSort(int key[],const int left, const int right)
{
	int temp, i, j, low, high, middle, k;
	for (i = left + 1; i <= right; i++)
	{
		temp = key[i]; low = left; high = i - 1;
		while (low <= high)
		{
			middle = (low + high) / 2;cmpNum++;
			if (temp < key[middle])
				high = middle - 1;
			else
				low = middle + 1;
		}
		for (k = i - 1; k >= low; k--)
		{
			key[k + 1] = key[k]; movNum++;
		}
		key[low] = temp; swapNum++;
		if (right - left + 1 == 10)
		{ 
			cout << "\n--" << i << "th��:";
			for (j = 0; j < 10; j++)
				cout << ' ' << key[j] ;
		}
	}
}
void ShellSort(int key[], const int left, const int right)
{
	int temp, i, j, gap = right - left + 1;
	do
	{
		gap = gap / 3 + 1;
		for (i = left + gap; i <= right; i++)
		{
			cmpNum++;
			if (key[i] < key[i - gap]) {
				temp = key[i]; j = i - gap;
				do {
				key[j + gap] = key[j]; movNum++;
				j = j - gap;
				cmpNum++;
				} while (j >= left && temp < key[j]);
				key[j + gap] = temp; swapNum++; 
			}
			if (right - left + 1 == 10)
			{
				cout << "\n-- gap = " << gap << "\t  ";
				for (j = 0; j < 10; j++)
					cout << ' ' << key[j];
			}
		}
	} while (gap > 1);
}
void QuickSort(int l,int key[], const int left, const int right)
{
	int j;
	if (left < right)
	{
		int pivotpos = Partition(l,key, left, right);	//����
		if (l == 10)
			for (j = 0; j < 10; j++)
				cout << ' ' << key[j];
		QuickSort(l,key, left, pivotpos - 1);
		QuickSort(l,key, pivotpos + 1, right);
	}
}
int Partition(int l, int key[], const int low, const int high)
{
	int pivotpos = low; int pivot = key[low];		//��׼Ԫ��
	if(l==10)cout << "\n - - �� " << pivot << "Ϊ��׼��һ������:";
	for (int i = low + 1; i <= high; i++)					//����������У����л���
	{
		cmpNum++;
		if (key[i] < pivot) {
			pivotpos++;
			if (pivotpos != i)						//С�ڻ�׼�Ľ��������
			{
				swapNum++;
				int temp = key[i];
				key[i] = key[pivotpos];
				key[pivotpos] = temp;
			}
		}
	}
	swapNum++;
	key[low] = key[pivotpos]; key[pivotpos] = pivot;//����׼Ԫ�ؾ�λ
	return pivotpos;								//���ػ�׼Ԫ��λ��
}
void ImprovedQuickSort(int key[], const int left, const int right)
{
	if (right - left <= 25)return;
	int pivotpos = Partition1(key, left, right);
	ImprovedQuickSort(key, left, pivotpos - 1);
	ImprovedQuickSort(key, pivotpos + 1, right);
}
int median3(int key[], const int left, const int right)
{
	int mid = (left + right) / 2; int k = left;
	if (key[mid] < key[k])k = mid; cmpNum++;
	if (key[right] < key[k])k = right; cmpNum++;
	if(k!=left){									//��Сֵ������left
		int temp = key[k]; key[k] = key[left]; key[left] = temp;
	}
	cmpNum++;
	if (mid != right && key[mid] < key[right]) {
		int temp = key[mid]; key[mid] = key[right]; key[right] = temp;
	}												//key[mid]Ϊ�м�ֵ��������rightλ��
	return key[right];								//����rightλ�ñ��������м�ֵ
}
int Partition1(int key[], const int left, const int right) 
{
	int i = left, j = right - 1;
	if (left < right) {
		int pivot = median3(key, left, right);		//������ȡ�м�ֵ
		while (1)
		{
			cmpNum += 2;
			while (i < j && key[i] < pivot) { i++; cmpNum++; }	//С��pivot���������
			while (j > i && pivot < key[j]) { j--; cmpNum++; }	//����pivot�������ұ�
			if (i < j)
			{
				int temp = key[i]; key[i] = key[j]; key[j] = temp;
				i++; j--;
			}
			else break;
		}
		cmpNum++;
		if (key[i] > pivot) 
		{ 
			key[right] = key[i]; key[i] = pivot;	//pivot�Ƶ��������Ӧ���ڵ�λ��
		}
	}
	return i;										//���ػ�׼Ԫ��λ��
}