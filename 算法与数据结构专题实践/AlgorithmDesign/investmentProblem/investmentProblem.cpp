/*分组背包问题
考古挖掘：P: number of places, and D: the number of total days.
eg.
4个地方可挖，一共只能挖10天；
可看作4组*5个/组=20个items，days=weight
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
	int* spend = new int[p];		// 最后结果：存放每个place挖的天数
	int* reward = new int[p * 5];	// 每个place挖的天数对应的reward：物品的value
	int* profit = new int[d];		// profit[j]:总共挖j天获得的最大利润
	int** path = new int* [(p * 5)];// 状态矩阵path[i][j]:背包容量为j时物品i是否放入（0/1）
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

	for (int i = 0; i < p; i++)			// p组物品
		for (int j = d; j >=0; j--){	// 背包容量j
			for (int k = 0; k < 5; k++) // 每组5个物品，枚举
				if (j >= k + 1) 
					if (profit[j] < (profit[(j - k - 1)] + reward[(5 * i + k)])) {
						profit[j] = profit[(j - k - 1)] + reward[(5 * i + k)];
						choose = 5 * i + k;
					}
			path[choose][j] = 1;
		}
	int w = d;
	while (w)							// 背包容量w：剩余挖的天数
		for (int i = p - 1; i >= 0; i--)// 物品的组号
			for (int j = 0; j < 5; j++)	// 物品组内编号
				if (path[i * 5 + j][w])	// ==1：组内选的物品标号
				{
					spend[i] = j + 1;	// Place i+1所挖天数
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