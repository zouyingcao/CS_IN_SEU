#include<iostream>
#include<queue>
#include"Graphlnk.h"
using namespace std;
template<class T, class E>
void Dijkstra(Graphlnk<T, E>& G, T V, E dist[], int path[])			//Dijkstra算法
{
	int n = G.NumberOfVertices();
	bool* s = new bool[n];
	int i, j, k; E w, min;
	int v = G.getVertexPos(V);
	for (i = 0; i < n; i++)
	{
		dist[i] = G.getWeight(v, i);
		s[i] = false;
		if (i != v && dist[i]< 0x3f3f3f3f )path[i] = v;
		else path[i] = -1;
	}
	s[v] = true; dist[v] = 0;
	for (i = 0; i < n - 1; i++)
	{
		min = inf;
		int u = v;
		for (j = 0; j < n; j++)
			if (s[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		s[u] = true;
		for (k = 0; k < n; k++)
		{
			w = G.getWeight(u, k);
			if (s[k] == false && w + dist[u] < dist[k])
			{
				dist[k] = w + dist[u];
				path[k] = u;
			}
		}
	}
}
template<class T,class E>
void printShortestPath(Graphlnk<T, E>& G, int v, E dist[], int path[])
{
	cout << "从顶点" << G.getValue(v) << "到其他各顶点的最短路径为:" << endl;
	int i, j, k, n=G.NumberOfVertices();
	int *d = new int[n];
	for(i=0;i<n;i++)
		if (i != v)
		{
			j = i; k = 0;
			cout << "顶点" << G.getValue(i) << "的最短路径为:" << G.getValue(v);
			while (j != v)
			{
				d[k++] = j;
				j = path[j];
			}
			while (k > 0)
				cout << " " << G.getValue(d[--k]) ;
			cout << " ,最短路径长度为:"<<dist[i] << endl;
		}
	delete[]d;
}
void BellManFord()													//Bellman-Ford算法	
{
	int i, k, m, n;
	cout << "输入顶点数n与边数m:" << endl;
	cin >> n >> m;
	int* v1 = new int[m], * v2 = new int[m], * w = new int[m], * dist = new int[n];
	cout << "输入端点信息:" << endl;
	for (i = 0; i < m; i++)
		cin >> v1[i] >> v2[i] >> w[i];
	for (i = 0; i < n; i++)
		dist[i] = inf;
	dist[0] = 0;
	for (k = 0; k < n - 1; k++)
		for (i = 0; i < m; i++)
			if (dist[v2[i]] > dist[v1[i]] + w[i])
				dist[v2[i]] = dist[v1[i]] + w[i];
	cout << "打印各点的最短路径长度如下: " << endl;
	for (i = 0; i < n; i++)
		cout << dist[i] << ' ';
}
template<class T, class E>
void SPFA(Graphlnk<T, E>& G, E dist[])
{
	int n = G.NumberOfVertices();
	queue<int> q;
	bool* s = new bool[n];
	for (int i = 0; i < n; i++)
	{
		dist[i] = 0x3f3f3f3f;
		s[i] = false;
	}
	dist[0] = 0; s[0] = true; q.push(0);//0号顶点作为源点
	int j;
	while (!q.empty())
	{
		j = q.front();
		q.pop();
		s[j] = false;//关键
		Edge<T, E>* p = G.NodeTable[j].adj;
		while (p != NULL)
		{
			if (dist[p->dest] > dist[j] + p->cost)//边的起点始终为k
			{	
				dist[p->dest] = dist[j] + p->cost;
				if (!s[p->dest])
				{
					s[p->dest] = true;
					q.push(p->dest);
				}
			}
			p = p->link;
		}
	}
	for (int i = 1; i < n; i++)
		cout <<"从顶点0到顶点"<<i<<"的最短路径长度为:" <<dist[i] << endl;
}
template<class T, class E>
void Prim(Graphlnk<T, E>& G, T V)			//Prim算法
{
	int n = G.NumberOfVertices();
	bool* s = new bool[n];
	int i, j, k;
	E min;
	int v = G.getVertexPos(V);
	E *lowcost = new E[n];
	for (i = 0; i < n; i++)
	{
		s[i] = false;
		lowcost[i] = G.getWeight(v, i);
	}
	s[v] = true;
	cout << "从顶点" << G.getValue(v) << "构造的最小生成树为:" << endl << G.getValue(v) ;
	for (i = 0; i < n-1; i++)
	{
		min = 0x3f3f3f3f;
		for (j = 0; j < n; j++)
		{
			if (s[j] == false && lowcost[j] < min)
			{
				min = lowcost[j];//更新min的值
				k = j;//记录当前最小权重的节点的编号
			}
		}
		cout << " "<< G.getValue(k);
		s[k] = true;//表明k节点已被选了(作标记)
		for(j=0;j<n;j++)
		{ 
			if (k != j && G.getWeight(k, j) < lowcost[j])
				lowcost[j] = G.getWeight(k, j);
		}
	}
}
int main()
{
	Graphlnk<char, int>G;
	cin >> G;//A B 10 A E 100 A D 30 B C 50 C E 10 D C 20 D E 60
	int n = G.NumberOfVertices();
	int *dist=new int[n], *path=new int[n];
	Prim(G, 'A');
//	Dijkstra(G, 'A', dist, path);
//	printShortestPath(G, 0, dist, path);
//	SPFA(G, dist);
	system("pause");
	return 0;
}

/*
	//网上的DPFS算法
	struct node {
		int u, v, w;
	};
	node Data[25];
	int n, m;
	int first[15], Next[15];
	int dis[15], book[15];
	queue<int> q;

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		dis[i] = 0x3f3f3f3f;
	dis[1] = 0;//1号点作为源点

	for (int i = 1; i <= n; i++)
		book[i] = 0;
	for (int i = 1; i <= n; i++)
		first[i] = -1;

	for (int i = 1; i <= m; i++) {
		cin >> Data[i].u >> Data[i].v >> Data[i].w;
		Next[i] = first[Data[i].u];
		first[Data[i].u] = i;
	}

	book[1] = 1;
	q.push(1);
	while (!q.empty()) {
		int t = q.front();
		q.pop();

		int k = first[t];
		while (k != -1) {
			cout << k << endl;
			if (dis[Data[k].v] > dis[Data[k].u] + Data[k].w) {
				dis[Data[k].v] = dis[Data[k].u] + Data[k].w;
				if (book[Data[k].v] == 0) {
					q.push(Data[k].v);
					book[Data[k].v] = 1;
				}
			}
			k = Next[k];
		}
		book[t] = 0;
	}
	for (int i = 1; i <= n; i++)
		cout << dis[i] << " ";

//////////////////////////////////////////////////////
	//自写的O(n^3)的Prim算法
	for (i = 0; i < n; i++)
		s[i] = false;
	int length = 0,t; s[v] = true;
	cout << "从顶点" << G.getValue(v) << "构造的最小生成树为:" << endl <<G.getValue(v);
	do
	{
		t = 0;
		min = inf;
		int u;
		for (j = 0; j < n; j++)
			if (s[j] == true)
				for (k = 0; k < n; k++)
					if (s[k] == false && G.getWeight(j, k) < min)
					{
						u = k;	min = G.getWeight(j, k); 
					}
		cout << " " << G.getValue(u) ;
		length += min;
		s[u] = true;
		for (i = 0; i < n; i++)
			if (s[i]==true)	t++;
	} while (t < n);
	cout << "\n最小生成树长度为:" << length << endl;
*/
