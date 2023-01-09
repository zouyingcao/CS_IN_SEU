#include<iostream>
using namespace std;
#define inf 0x3f3f3f3f;
const int DefaultVertices = 100;
template<class T, class E>
struct Edge {												//边结点的定义
	int dest;												//边的另一顶点位置
	E cost;
	Edge<T,E>* link;										//下一条边链指针
	Edge() {}
	Edge(int num,E weight) :dest(num), link(NULL) ,cost(weight){}
};
template<class T,class E>
struct Vertex
{
	T data;													//顶点的名字
	Edge<T,E>* adj;											//边链表的头指针
};
template<class T,class E>
class Graphlnk {
	friend istream& operator>>(istream& in, Graphlnk<T,E>& G) {
		G.input(in);
		return in;
	}
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	void input(istream& in);

	bool GraphEmpty()const
	{
		if (numEdges == 0)
			return true;
		else
			return false;
	}
	bool GraphFull()const
	{
		if (numVertices == maxVertices ||
			numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		else
			return false;
	}
	T getValue(int i) { return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0; }
	E getWeight(int , int );
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }

	int getFirstNeighbour(int);
	int getNextNeighbour(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2,E weight);

	int getVertexPos(const T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex)return i;
		return -1;
	}
	Vertex<T, E>* NodeTable;
private:
	int maxVertices;										//图中最大顶点数
	int numEdges;											//当前边数
	int numVertices;										//当前顶点数
	
};
template<class T,class E>
Graphlnk<T,E>::Graphlnk(int sz)
{
	maxVertices = sz; numVertices = 0; numEdges = 0;
	NodeTable = new Vertex<T,E>[maxVertices];
	if (NodeTable == NULL) { cerr << "存储分配错！" << endl; exit(1); }
	for (int i = 0; i < maxVertices; i++)NodeTable[i].adj = NULL;
}
template<class T,class E>
Graphlnk<T,E>::~Graphlnk()
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T,E>* p = NodeTable[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
}
template<class T,class E>
int Graphlnk<T,E>::getFirstNeighbour(int v)//给出顶点v的第一个邻接顶点的位置
{
	if (v != -1)
	{
		Edge<T>* p = NodeTable[v].adj;
		if (p != NULL) return p->dest;
	}
}
template<class T,class E>
int Graphlnk<T,E>::getNextNeighbour(int v, int w)//给出顶点v的某邻接顶点w的下一个邻接顶点
{
	if (v != -1&&w!=-1)
	{
		Edge<T>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}
template<class T,class E>
bool Graphlnk<T,E>::insertVertex(const T& vertex)
{
	if (numVertices == maxVertices)return false;
	NodeTable[numVertices].data = vertex;
	numVertices++; return true;
}
template<class T,class E>
bool Graphlnk<T,E>::insertEdge(int v1, int v2,E weight)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<T,E>* q = new Edge<T,E>, * p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
			p = p->link;
		if (p != NULL)return false;				//找到这边，不插入
		p = new Edge<T,E>;
		p->dest = v2; p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		numEdges++;
		return true;
	}
	return 0;
}
template<class T,class E>
void Graphlnk<T,E>::input(istream& in)
{
	int i, j, k, m, n; T v1, v2;  E weight;
	cout << "输入顶点数n与边数m:" << endl;
	in >> n >> m;
	cout << "输入顶点表数据:" << endl;
	for (i = 0; i < n; i++) {
		in >> v1;
		insertVertex(v1);
	}
	i = 0;
	cout << "输入端点信息:" << endl;
	while (i < m)
	{
		in >> v1 >> v2 >> weight;
		j = getVertexPos(v1); k = getVertexPos(v2);
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，重新输入！" << endl;
		else {
			insertEdge(j, k,weight); i++;
		}
	}
}
template<class T,class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
			p = p->link;
		if (p != NULL)return p->cost;
	}
	return inf;
}
