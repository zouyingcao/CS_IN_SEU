#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<time.h>
#include<fstream>
using namespace std;
int main()
{
	int n,index; cin >> n; index = n;
	vector<int> t;
	srand(time(0));
	ofstream file; file.open("testData_100_r.txt");
	while (index) {
		for (int i = 0; i < index; i++)
			t.push_back(rand() % (n/2) + 1);
		sort(t.begin(), t.end());
		for (int i = index - 1; i >= 0; i--)
			file << t[i] << " ";
		int min = t.front();
		t.clear();
		for (int i = index; i < n; i++) 
			t.push_back(min + rand() % (n/2) + 1);
		sort(t.begin(), t.end());
		for (int i = 0; i < n - index; i++)
			file << t[i] << " ";
		file << '\n';
		index--;
	}
	return 0;
}

/*
	for (int i = 0; i < index; i++)
		t.push_back(rand() % 1000 + 1);
	sort(t.begin(), t.end());
	for (int i = index-1; i >=0; i--)
		file << t[i] << " ";
	int min = t.front();
	t.clear();
	for (int i = index; i < n; i++)
		t.push_back(min + rand() % 1000 + 1);
	sort(t.begin(), t.end());
	for (int i = 0; i < n - index; i++)
		file << t[i] << " ";
*/

/*不存在相等的
	int bias = rand() % 100 + 1;
	for (int i = index - 1; i >= 0; i--)
		file << i + bias << " ";
	for (int i = index; i < n; i++)
		file << i + bias << " ";
	file << '\n';
	index--;
*/