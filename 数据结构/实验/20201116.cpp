#include<iostream>
using namespace std;
bool Findx(int**, int);
//数组每一行每一列都是从小到大排列的，找x,要求O(m+n)
int main()
{
	int m, n, x, flag=0;
	cout << "输入数组的行数与列数:" << endl;
	cin >> m >> n;//4 5
	int **A=new int*[m];
	for (int i = 0; i < m; i++)
		A[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> x;
			A[i][j] = x;
		}
	//1 2 4 5 8
	//2 4 6 8 10
	//4 6 8 9 12
	//5 7 10 11 13
	cout << "输入需要查找的数x:" << endl;
	cin >> x;
	int col = 0, row = 0;
	int p = 0, q = n - 1;
	while (p < m && q >= 0)
		if (A[p][q] == x)
		{
			cout << "x在数组中的位置为:(" << p << "," << q <<")\n";
			flag = 1;
			p++;
		}
		else if (A[p][q] < x)
			p++;
		else
			q--;
	if(flag==0)	cout << "Not Found x!" << endl;
	system("pause");
	return 0;
}