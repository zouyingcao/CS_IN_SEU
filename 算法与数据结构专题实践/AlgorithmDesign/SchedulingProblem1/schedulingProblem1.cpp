#include<iostream>
#include<vector>
using namespace std;
void QuickSort(int* a,int* b, int x, int y);
void Swap(int& x, int& y);
void greedySelect();
int main()
{
	int n;									// ����ĸ���
	cout << "Input the number of the set of intervals:"; cin >> n;
	int* start = new int[n];				// �������˵�
	int* end = new int[n];					// ������Ҷ˵�
	vector<vector<int> >S;					// ǰi+1����������feasible solution,��¼���Ž�·��
	for (int i = 0; i < n; i++)  
		S.push_back(vector<int>());
	cout << "Input the start and end of these intervals:" << endl;
	for (int i = 0; i < n; i++)
		cin >> start[i] >> end[i];
	QuickSort(end, start, 0, n - 1);		// ��end��С��������
	int* profit = new int[n];				// profit[i]:ǰi+1����������feasible solution����
	int* p = new int[n];					// p[i]:����i֮ǰ������ȡ���Ĳ��ص����������
	for (int i = 0; i < n; i++){
		profit[i] = 0;						// ��ʼ����0��ʾ������feasible solution������Ϊ0
		p[i] = -1;							// ��ʼ����-1��ʾ������
		for (int j = i - 1; j >= 0; j--)
			if (end[j] <= start[i]) {
				p[i] = j;					//ʹ������j��i���ص���������,j<i
				break;
			}
	}
	profit[0] = end[0] - start[0];			// ��ֻ��һ��intervalʱ�����feasible solution��Ȼ�������䱾��
	S[0].push_back(0);
	for (int i = 1; i< n; i++){				// ����i����ѡ��:ѡ��:�ҵ�������i���ص���������j,profit[j]+����i����;��ѡ��:profit[i-1]
		if (p[i] != -1){					// ����i֮ǰ�����ڲ��ص�������
			if (profit[i - 1] > profit[p[i]] + (end[i] - start[i])){ 
				profit[i] = profit[i - 1];	// ��ѡ����i�����
				for (int j = 0; j < S[i - 1].size(); j++)
					S[i].push_back(S[i - 1][j]);
			}
			else {							// ѡ����i�����
				profit[i] = profit[p[i]] + (end[i] - start[i]);
				for (int j = 0; j < S[p[i]].size(); j++)
					S[i].push_back(S[p[i]][j]);
				S[i].push_back(i);
			}
		}
		else {								// ����i֮ǰ�������ڲ��ص�������
			if (profit[i - 1] > (end[i] - start[i])) {	
				profit[i] = profit[i - 1];	// ѡ����i�����
				for (int j = 0; j < S[i - 1].size(); j++)
					S[i].push_back(S[i - 1][j]);
			}
			else {							// ѡ����i�����
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
			if (pivotpos != i)			//С�ڻ�׼�Ľ��������
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
	int n;//����ĸ���
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