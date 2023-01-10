/*���鱳������
�����ھ�P: number of places, and D: the number of total days.
eg.
4���ط����ڣ�һ��ֻ����10�죻
�ɿ���4��*5��/��=20��items��days=weight
reward:
10 15 16 17 30
3 9 17 26 28
4 6 9 13 15
1 10 13 16 20
*/
#include<iostream>
using namespace std;
int main()
{
	int p, d, choose;				// P: number of places,D: the number of total days,choose:the index of choosed item
	cout << "The number of places is P = ";
	cin >> p;	
	cout << "The number of total days is D = ";
	cin >> d;	
	int* spend = new int[p];		// ����������ÿ��place�ڵ�����
	int* reward = new int[p * 5];	// ÿ��place�ڵ�������Ӧ��reward����Ʒ��value
	int* profit = new int[d];		// profit[j]:�ܹ���j���õ��������
	int** path = new int* [(p * 5)];// ״̬����path[i][j]:��������Ϊjʱ��Ʒi�Ƿ���루0/1��
	for (int i = 0; i < p * 5; i++)
		path[i] = new int[(d + 1)];
	cout << "The expected rewards: " << endl;
	for (int i = 0; i < p * 5; i++)
		cin >> reward[i];
	for (int i = 0; i < p; i++)
		spend[i] = 0;
	for (int i = 0; i < d; i++)
		profit[i] = 0;
	for (int i = 0; i < p * 5; i++)
		for (int j = 0; j <= d; j++)
			path[i][j] = 0;

	for (int i = 0; i < p; i++)			// p����Ʒ
		for (int j = d; j >=0; j--){	// ��������j
			for (int k = 0; k < 5; k++) // ÿ��5����Ʒ��ö��
				if (j >= k + 1) 
					if (profit[j] < (profit[(j - k - 1)] + reward[(5 * i + k)])) {
						profit[j] = profit[(j - k - 1)] + reward[(5 * i + k)];
						choose = 5 * i + k;
					}
			path[choose][j] = 1;
		}
	int w = d;
	while (w)							// ��������w��ʣ���ڵ�����
		for (int i = p - 1; i >= 0; i--)// ��Ʒ�����
			for (int j = 0; j < 5; j++)	// ��Ʒ���ڱ��
				if (path[i * 5 + j][w])	// ==1������ѡ����Ʒ���
				{
					spend[i] = j + 1;	// Place i+1��������
					w -= j + 1;
					break;
				}
	for (int i = 0; i < p; i++)
		cout << "Place " << i + 1 << ", spend " << spend[i] << " days\n";
	cout << "Total profit = " << profit[d] << endl;
	for (int i = 0; i < p * 5; i++)
		delete[] path[i];
	return 0;
}