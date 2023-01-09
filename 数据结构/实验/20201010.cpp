#include<iostream>
#include<cmath>
#include<time.h>
#include<chrono>
int BinarySearch(int*, const int, const int);
char compare(int, int);
int Compare(int[], int[], int, int);
void ChangeFastTranspose();
using namespace std;
int main()
{
	/*int i,j,k;
	for (i = 1;pow(i,2)>=(pow(2.0,i)/4); i++);
	cout <<"当n≥"<<i << "时，2^n/4>n^2"<<endl;
	int a[100];
	double ave[100];
	for (j = 0; j < 100; j++)//数组a全赋值为偶数
		a[j] = 2*j;
	for (j = 1; j < 101; j++) {
		double x=0;
		cout << j << " "<< endl;
		for (int k = 0; k < 10000; k++) {
			auto start = std::chrono::steady_clock::now();
			BinarySearch(a,sqrt(k), j);
			auto end = std::chrono::steady_clock::now();
			double dr_ns = std::chrono::duration<double, std::nano>(end - start).count();
		//	cout << dr_ns << " ";
			x += dr_ns;
		}
		ave[j - 1] = x/10000;
		//cout << endl;
	}
	for (j = 0; j < 100; j++)
		cout << ave[j] <<endl;
	int n,m;
	cout << "有序表A的大小为:";
	cin >> n;
	int* a = new int[n];
	cout << "输入有序表A:";
	int x,i;
	for (i = 0; i < n; i++)
	{
		cin >> x;
		a[i] = x;
	}
	cout << "有序表B的大小为:";
	cin >> m;
	int* b = new int[m];
	cout << "输入有序表B:";
	for (i = 0; i < m; i++)
	{
		cin >> x;
		b[i] = x;
	}
	i = Compare(a, b, n, m);
	cout << "比较结果是:" << endl;
	switch (i)
	{
	case 1:cout << "A>B\n"; break;
	case -1:cout << "A<B\n"; break;
	case 0:cout << "A=B\n"; break;
	default:cout << "error\n";
	}*/
	ChangeFastTranspose();

	system("pause");
	return 0;
}
int BinarySearch(int* a, const int x, const int n)
{
	for (int left = 0, right = n - 1; left <= right;) {
		int middle = (left + right) / 2;
		switch (compare(x, a[middle])) {
		case 1:left = middle + 1; break;
		case -1:right = middle - 1; break;
		case 0:return middle;
		}
		return -1;
	}
}
char compare(int x, int y)
{
	if (x > y)return 1;
	else if (x < y)return -1;
	else return 0;
}
int Compare(int a[], int b[], int n, int m)
{
	int i = 0;
	while (a[i] == b[i] && i < n && i < m)
		i++;
	if (n == m && i == n)return 0;
	if (n < m && i == n)return -1;
	if (n > m && i == m)return 1;
	if (i < n && i < m)
		if (a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
}

 void ChangeFastTranspose()
{
	 int m, n, x, t=0;
	 cout << "首先请输入稀疏矩阵的行与列:" << endl;
	 cin >> m >> n;
	 int* a = new int[m*n];
	cout << "输入一个稀疏矩阵" << endl;
	for (int i = 0; i < m * n; i++)
	{
		cin >> x;
		a[i] = x;
		if(x!=0)t++;
	}
	cout << "其三元组表为:" << endl;
	int** smArray = new int *[t];
	for (int i = 0; i < t; i++)
		smArray[i] = new int[3];
	int k = 0;
	for (int i = 0; i < m * n; i++)
	{
		if (a[i] != 0)
		{
			smArray[k][0] = i / n;
			smArray[k][1] = i- i / n *n;
			smArray[k][2] = a[i];
			cout << smArray[k][0] << " "<<smArray[k][1] <<" "<< smArray[k][2]<<" " << endl;
			k++;
		}
	}
	int* RSRS = new int[n];
	int** smArray1 = new int* [t];
	for (int i = 0; i < t; i++)
		smArray1[i] = new int[3];
	if (t > 0)
	{
		for (int i = 0; i < n; i++)
			RSRS[i] = 0;
		for (int i = 0; i < t; i++)
			RSRS[smArray[i][1]]++;
		int temp = RSRS[0];
		RSRS[0] = 0;
		for (int i = 1; i < n; i++)//覆盖数组操作
		{
			int tem = RSRS[i];
			RSRS[i] = RSRS[i - 1] + temp;
			temp = tem;
		}
		for (int i = 0; i < t; i++)
		{
			int j = RSRS[smArray[i][1]];
			smArray1[j][0] = smArray[i][1];
			smArray1[j][1] = smArray[i][0];
			smArray1[j][2] = smArray[i][2];
			RSRS[smArray[i][1]]++;
		}
		cout << "其转置矩阵的三元组表为:" << endl;
		for (int i = 0; i < t; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << smArray1[i][j] << " ";
			cout << endl;
		}
	}
}
 /*
0 0 2 0 0 0 0
3 0 0 -11 0 0 0
0 0 0 -6 0 0 0
0 0 0 0 0 -17 0
0 9 0 0 19 0 0
0 0 0 -8 0 0 -52
*/