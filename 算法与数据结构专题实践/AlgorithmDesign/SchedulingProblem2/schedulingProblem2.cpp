#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int findMinPtr(int*, int);
void greedAssign();
int main()
{	
	int m, n;												// m:processors个数,n:jobs个数
	cout << "Input the number of processors:"; cin >> m;
	cout << "Input the number of jobs:"; cin >> n;
	vector<int>times;										// 记录processing times
	cout << "Input the processing times of these jobs" << endl;
	int temp, sum, max = 0, key = 0;						// max:maximum load,key:maximum load对应的processor（若多个选其一）
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		times.push_back(temp); 
	}
	temp = m;												// 记录最初的processors个数
	while (m>1) {											// 等价：从n个物品中选取若干个，其重量不超过sum/n，且重量达到最大 
		sum = 0;											// 计算jobs耗时总和
		n = times.size();									// 当前待分配的jobs个数
		for (int i = 0; i < n; i++)
			sum += times[i];
		int* load = new int[sum / m];						// load[i]:重量不超过i的物品放入背包的最大利润
		memset(load, 0, sizeof(int) * (sum / m));
		int** path = new int* [n];							// 该processor分配的job记录
		for (int i = 0; i < n; i++) {
			path[i] = new int[sum / m];
			memset(path[i], 0, sizeof(int) * (sum / m));
		}
		sort(times.begin(), times.end());					// processing times从小到大排序
		//double target = double(sum) / m;
		for (int i = 0; i < n; i++) {
			for (int j = sum / m; j >= times[i]; j--)
				if (load[j] < load[j - times[i]] + times[i]) {
					load[j] = load[j - times[i]] + times[i];
					path[i][j] = 1;
				}
		}
		int i = n, j = sum / m;
		vector<int>processor;								// 记录该processor安排的job序号
		cout << "processor " << temp - m + 1 << " : ";
		sum = 0;
		while (j&&i) {
			i--;
			if (path[i][j] == 1) {
				cout << times[i] << " ";					// 打印安排的job processing times
				j -= times[i]; 
				sum += times[i];							// 记录load总和
				processor.push_back(i);						// jobs中第i+1个被安排
			}
		}
		cout << endl;
		if (sum > max) {									 // 记录maximum load
			max = sum; 
			key = temp - m + 1; 
		}
		for (int i = 0; i < processor.size(); i++)
			times.erase(times.begin() + processor[i]);		// 将安排好的jobs剔除
		m--;												// 未安排的processor个数减一
		/*for (int i = 0; i < n; i++)
			delete[] path[i];
		delete[] load;*/
	}
	cout << "processor " << temp << " : ";
	sum = 0;
	for (int i = 0; i < times.size(); i++) {
		cout << times[i] << " ";
		sum += times[i];
	}
	if (sum > max) {									 // 记录maximum load
		max = sum; 
		key = temp;
	}
	cout << "The maximum load is: " << max << " in processor " << key << endl;
	return 0;
}

void greedAssign()
{
	int m,n;							// m:processors个数,n:jobs个数
	cout << "Input the number of processors:";cin >> m;
	cout << "Input the number of jobs:"; cin >> n;
	cout << "Input the processing times of these jobs" << endl;
	int* load = new int[m];
	memset(load, 0, sizeof(int) * m);	
	vector<vector<int> >processor;		// 记录processor处理的job	
	for (int i = 0; i < m; i++)
		processor.push_back(vector<int>());
	int* times = new int[n];
	int p;
	for (int i = 0; i < n; i++) {
		cin >> times[i];
		p = findMinPtr(load, m);		// 找到当前load最小的processor
		load[p] += times[i];			// 贪心算法:让当前load最小的processor加工该job
		processor[p].push_back(i);		// 记录该processor p处理的job
	}
	cout << "After a greedy algorithm to assign jobs to processors:" << endl;
	int max = 0, k = 0;
	for (int i = 0; i < m; i++){
		if (load[i] > max)				// 记录maximum load
		{
			max = load[i];
			k = i + 1;
		}
		cout << "processor " << i << " : ";
		for (int j = 0; j < processor[i].size(); j++)
			cout << times[processor[i][j]] << " ";
		cout << endl;
	}
	cout << "The maximum load is: " << max <<" in processor "<< k<< endl;
	delete[] load;
}
int findMinPtr(int* a,int m)			// 找到当前load最小的processor
{
	int min = a[0], key = 0;
	for (int i = 0; i < m; i++)
		if (a[i] < min) {
			min = a[i];
			key = i;
		}
	return key;
}
