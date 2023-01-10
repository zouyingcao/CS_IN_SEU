/*
数字序列：先递减再递增，
两种情况：
1、任意两个连续数字不同
2、任意两个连续数字可能相同
找到最小的数字
eg.
n=14:20 18 14 13 12 9 10 12 14 15 16 20 25 30
n=20:14 13 12 9 7 5 3 2 4 6 10 12 14 15 16 18 19 20 25 30
n=100:14 13 12 9 7 5 3 2 4 6 10 12 14 15 16 18 19 20 25 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110
*/
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;
int findTheMinimum(int* num, int l, int r);
int findTheMinimum_1(int* num, int l, int r);
int m;										// m:the number of comparisons in the algorithm
int main()
{
	int n;									// n:the number of numbers
	cout << "Input the number of numbers: n = ";
	cin >> n;
	int* num = new int[n];
	/*for (int i = 0; i < n; i++)
		cin >> num[i];
	cout << "The minimum number is: ";
	cout << findTheMinimum(num, 0, n - 1) << endl;
	cout << "The number of comparisons the algorithm needs to find the minimum if n = " << n << " is: " << m << endl;*/
	fstream infile("testData_100_r.txt", ios::in); 
	if (!infile)
	{
		cout << "open error!" << endl;
		exit(1);
	}
	int index = n,total=0;
	while (index) {	// index组测试数据
		m = 0;
		for (int i = 0; i < n; i++)
			infile >> num[i];
		cout << "The minimum number is: ";
		cout << findTheMinimum_1(num, 0, n - 1) << endl;
		cout << "The number of comparisons the algorithm needs to find the minimum if n = " << n << " is: " << m << endl;
		index --;
		total += m;
	}
	cout<< "\nThe average number of comparisons the algorithm needs to find the minimum if n = " << n << " is: " << double(total)/n << endl;
	delete[]num;
	return 0;
}
int findTheMinimum(int* num, int l, int r)		// 一开始未考虑存在相等情况
{
	if (l == r)
		return num[l];							// 递归截止
	int mid = (r + l) / 2;
	m++;// for if followed
	if (num[mid] < num[mid + 1])
		return findTheMinimum(num, l, mid);		// 找左半部分
	else
		return  findTheMinimum(num, mid + 1, r);// 找右半部分
}
int findTheMinimum_1(int* num, int l, int r)	// 考虑存在相等情况
{
	if (l == r)
		return num[l];
	int mid = (r + l) / 2;
	m++;// for while followed
	while (num[mid] == num[mid + 1]){
		mid++;
		m++;
	}
	m++;// for if followed
	if (num[mid] > num[mid + 1]) {
		m++;// for while followed
		while (num[mid] == num[mid - 1]){
			mid--;
			m++;
		}
		return findTheMinimum(num, mid, r);
	}
	else
		return findTheMinimum(num, l, mid);
}