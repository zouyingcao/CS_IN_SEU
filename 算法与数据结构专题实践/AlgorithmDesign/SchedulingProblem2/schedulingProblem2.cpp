#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int findMinPtr(int*, int);
void greedAssign();
int main()
{	
	int m, n;												// m:processors����,n:jobs����
	cout << "Input the number of processors:"; cin >> m;
	cout << "Input the number of jobs:"; cin >> n;
	vector<int>times;										// ��¼processing times
	cout << "Input the processing times of these jobs" << endl;
	int temp, sum, max = 0, key = 0;						// max:maximum load,key:maximum load��Ӧ��processor�������ѡ��һ��
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		times.push_back(temp); 
	}
	temp = m;												// ��¼�����processors����
	while (m>1) {											// �ȼۣ���n����Ʒ��ѡȡ���ɸ���������������sum/n���������ﵽ��� 
		sum = 0;											// ����jobs��ʱ�ܺ�
		n = times.size();									// ��ǰ�������jobs����
		for (int i = 0; i < n; i++)
			sum += times[i];
		int* load = new int[sum / m];						// load[i]:����������i����Ʒ���뱳�����������
		memset(load, 0, sizeof(int) * (sum / m));
		int** path = new int* [n];							// ��processor�����job��¼
		for (int i = 0; i < n; i++) {
			path[i] = new int[sum / m];
			memset(path[i], 0, sizeof(int) * (sum / m));
		}
		sort(times.begin(), times.end());					// processing times��С��������
		//double target = double(sum) / m;
		for (int i = 0; i < n; i++) {
			for (int j = sum / m; j >= times[i]; j--)
				if (load[j] < load[j - times[i]] + times[i]) {
					load[j] = load[j - times[i]] + times[i];
					path[i][j] = 1;
				}
		}
		int i = n, j = sum / m;
		vector<int>processor;								// ��¼��processor���ŵ�job���
		cout << "processor " << temp - m + 1 << " : ";
		sum = 0;
		while (j&&i) {
			i--;
			if (path[i][j] == 1) {
				cout << times[i] << " ";					// ��ӡ���ŵ�job processing times
				j -= times[i]; 
				sum += times[i];							// ��¼load�ܺ�
				processor.push_back(i);						// jobs�е�i+1��������
			}
		}
		cout << endl;
		if (sum > max) {									 // ��¼maximum load
			max = sum; 
			key = temp - m + 1; 
		}
		for (int i = 0; i < processor.size(); i++)
			times.erase(times.begin() + processor[i]);		// �����źõ�jobs�޳�
		m--;												// δ���ŵ�processor������һ
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
	if (sum > max) {									 // ��¼maximum load
		max = sum; 
		key = temp;
	}
	cout << "The maximum load is: " << max << " in processor " << key << endl;
	return 0;
}

void greedAssign()
{
	int m,n;							// m:processors����,n:jobs����
	cout << "Input the number of processors:";cin >> m;
	cout << "Input the number of jobs:"; cin >> n;
	cout << "Input the processing times of these jobs" << endl;
	int* load = new int[m];
	memset(load, 0, sizeof(int) * m);	
	vector<vector<int> >processor;		// ��¼processor�����job	
	for (int i = 0; i < m; i++)
		processor.push_back(vector<int>());
	int* times = new int[n];
	int p;
	for (int i = 0; i < n; i++) {
		cin >> times[i];
		p = findMinPtr(load, m);		// �ҵ���ǰload��С��processor
		load[p] += times[i];			// ̰���㷨:�õ�ǰload��С��processor�ӹ���job
		processor[p].push_back(i);		// ��¼��processor p�����job
	}
	cout << "After a greedy algorithm to assign jobs to processors:" << endl;
	int max = 0, k = 0;
	for (int i = 0; i < m; i++){
		if (load[i] > max)				// ��¼maximum load
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
int findMinPtr(int* a,int m)			// �ҵ���ǰload��С��processor
{
	int min = a[0], key = 0;
	for (int i = 0; i < m; i++)
		if (a[i] < min) {
			min = a[i];
			key = i;
		}
	return key;
}
