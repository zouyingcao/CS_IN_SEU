#include<iostream>
#include<vector>
using namespace std;
void QuickSort(int* a,int* b, int x, int y);
void Swap(int& x, int& y);
void greedySelect();
int main()
{
	int n;									// 区间的个数
	cout << "Input the number of the set of intervals:"; cin >> n;
	int* start = new int[n];				// 区间的左端点
	int* end = new int[n];					// 区间的右端点
	vector<vector<int> >S;					// 前i+1个区间的最佳feasible solution,记录最优解路径
	for (int i = 0; i < n; i++)  
		S.push_back(vector<int>());
	cout << "Input the start and end of these intervals:" << endl;
	for (int i = 0; i < n; i++)
		cin >> start[i] >> end[i];
	QuickSort(end, start, 0, n - 1);		// 按end从小到大排序
	int* profit = new int[n];				// profit[i]:前i+1个区间的最佳feasible solution利润
	int* p = new int[n];					// p[i]:区间i之前，可以取到的不重叠的区间序号
	for (int i = 0; i < n; i++){
		profit[i] = 0;						// 初始化，0表示不存在feasible solution，利润为0
		p[i] = -1;							// 初始化，-1表示不存在
		for (int j = i - 1; j >= 0; j--)
			if (end[j] <= start[i]) {
				p[i] = j;					//使得区间j与i不重叠的最大序号,j<i
				break;
			}
	}
	profit[0] = end[0] - start[0];			// 当只有一个interval时，最佳feasible solution必然就是区间本身
	S[0].push_back(0);
	for (int i = 1; i< n; i++){				// 区间i两个选择:选择:找到与区间i不重叠的最大序号j,profit[j]+区间i利润;不选择:profit[i-1]
		if (p[i] != -1){					// 区间i之前，存在不重叠的区间
			if (profit[i - 1] > profit[p[i]] + (end[i] - start[i])){ 
				profit[i] = profit[i - 1];	// 不选区间i利润大
				for (int j = 0; j < S[i - 1].size(); j++)
					S[i].push_back(S[i - 1][j]);
			}
			else {							// 选区间i利润大
				profit[i] = profit[p[i]] + (end[i] - start[i]);
				for (int j = 0; j < S[p[i]].size(); j++)
					S[i].push_back(S[p[i]][j]);
				S[i].push_back(i);
			}
		}
		else {								// 区间i之前，不存在不重叠的区间
			if (profit[i - 1] > (end[i] - start[i])) {	
				profit[i] = profit[i - 1];	// 选区间i利润大
				for (int j = 0; j < S[i - 1].size(); j++)
					S[i].push_back(S[i - 1][j]);
			}
			else {							// 选区间i利润大
				profit[i] = end[i] - start[i];
				S[i].push_back(i);
			}
		}
	}
	cout << "A dynamic programming algorithm to select the intervals as followed:\nS={";
	for (int i = 0; i < S[n-1].size(); i++) {
		cout << "[" << start[S[n-1][i]] << "," << end[S[n-1][i]] << ")";
		if (i != S[n-1].size() - 1)cout << ",";
	}
	cout << "}\nThe maximum profit is P(S)= " << profit[n-1] << endl;
	delete[] start;
	delete[] end;
	delete[] profit;
	delete[] p;
	return 0;
}

void QuickSort(int* a,int* b, int x, int y)
{
	if (x >= y)return;
	int pivot = a[x], pivotpos = x;
	for (int i = x; i <= y; i++)
	{
		if (a[i] < pivot)
		{
			pivotpos++;
			if (pivotpos != i)			//小于基准的交换到左侧
			{
				Swap(a[pivotpos], a[i]);
				Swap(b[pivotpos], b[i]);
			}
		}
	}
	Swap(a[x], a[pivotpos]);
	Swap(b[x], b[pivotpos]);
	QuickSort(a, b, x, pivotpos - 1);
	QuickSort(a, b, pivotpos + 1, y);
}

void Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

void greedySelect()
{
	int n;//区间的个数
	cout << "Input the number of the set of intervals:"; cin >> n;
	int* start = new int[n];
	int* end = new int[n];
	int S_end = 0;
	vector<int>S;
	int profit = 0;
	cout << "Input the start and end of these intervals:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> start[i] >> end[i];
		if (start[i] >= S_end) {
			profit += end[i] - start[i];
			S_end = end[i];
			S.push_back(i);
		}
	}
	cout << "A greedy algorithm to select the intervals as followed:\nS={";
	for (int i = 0; i < S.size(); i++) {
		cout << "[" << start[S[i]] << "," << end[S[i]] << ")";
		if (i != S.size() - 1)cout << ",";
	}
	cout << "}\nThe profit is P(S)=" << profit << endl;
	delete[] start;
	delete[] end;
}