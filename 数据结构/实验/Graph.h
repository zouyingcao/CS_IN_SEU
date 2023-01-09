#include<iostream>
#include<stack>
using namespace std;

const int DefaultVertices = 100;
template<class T>
struct Edge {												//边结点的定义
	int dest;												//边的另一顶点位置
	Edge<T>* link;											//下一条边链指针
	Edge() {}
	Edge(int num) :dest(num), link(NULL) {}
};
template<class T>
struct Vertex
{
	T data;													//顶点的名字
	Edge<T>* adj;											//边链表的头指针
};
template<class T>
class Graphlnk {
	friend istream& operator>>(istream& in, Graphlnk<T>& G) {
		G.input(in);
		return in;
	}
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
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
	void input(istream& in);
	void DFS(const T& v);
	void GraphMatrix();
	T getValue(int i) { return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0; }
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }
	bool insertVertex(const T& vertex);	
	bool insertEdge(int v1, int v2);
	//bool removeVertex(int v);
	//bool removeEdge(int v1, int v2);
	//int getFirstNeighbour(int v);
	//int getNextNeighbour(int v, int w);
	int getVertexPos(const T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex)return i;
		return -1;
	}
private:
	int maxVertices;										//图中最大顶点数
	int numEdges;											//当前边数
	int numVertices;										//当前顶点数
	Vertex<T>* NodeTable;
};
template<class T>
Graphlnk<T>::Graphlnk(int sz)
{
	maxVertices = sz; numVertices = 0; numEdges = 0;
	NodeTable = new Vertex<T>[maxVertices];
	if (NodeTable == NULL) { cerr << "存储分配错！" << endl; exit(1); }
	for (int i = 0; i < maxVertices; i++)NodeTable[i].adj = NULL;
}
template<class T>
Graphlnk<T>::~Graphlnk()
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T>* p = NodeTable[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
}
/*
template<class T>
int Graphlnk<T>::getFirstNeighbour(int v)
{
	if(v!=-1)
	{
		Edge<T>* p = NodeTable[v].adj;
		if (p != NULL) return p->dest;
	}
}
template<class T>
int Graphlnk<T>::getNextNeighbour(int v,int w)
{
	if (v != -1)
	{
		Edge<T>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w) 
			p = p->link;
		if(p!=NULL&&p->link!=NULL)
			return p->link->dest;
	}
	return -1;
}*/
template<class T>
bool Graphlnk<T>::insertVertex(const T& vertex)
{
	if (numVertices == maxVertices)return false;
	NodeTable[numVertices].data = vertex;
	numVertices++; return true;
}
/*
template<class T>
bool Graphlnk<T>::removeVertex(int v)
{
	if (numVertices == -1||v<0||v>=numVertices)return false;
	Edge<T>* p, * s, * t;
	int i, k;
	while (NodeTable[v].adj != NULL) {

	}
	return true;
}*/
template<class T>
bool Graphlnk<T>::insertEdge(int v1,int v2)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<T>* q = new Edge<T>, * p = NodeTable[v1].adj;
		/*
		while (p != NULL && p->dest != v2)
		{
			q = p;	p = p->link;
		}
		if (p != NULL)return false;				//找到这边，不插入
		p = new Edge<T>;
		p->dest = v2;
		p->link = NULL;
		q->link = p;
		*/
		while (p != NULL && p->dest != v2)
			p = p->link;
		if (p != NULL)return false;				//找到这边，不插入
		p = new Edge<T>;
		p->dest = v2;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
	/*	q->dest = v1;							//无向图时
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;*/
		numEdges++; 
		return true;
	}
	return 0;
}
template<class T>
void Graphlnk<T>::input(istream&in)
{
	int i, j, k, m, n; T v1, v2; 
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
		in >> v1 >> v2;
		j = getVertexPos(v1); k = getVertexPos(v2);
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，重新输入！" << endl;
		else {
			insertEdge(j, k); i++;
		}
	}
}
template<class T>
void Graphlnk<T>::DFS( const T& v)
{
	bool* visited = new bool[NumberOfVertices()];
	for (int i = 0; i < NumberOfVertices(); i++)
		visited[i] = false;
	int start = getVertexPos(v);
	stack<T> s;
	s.push(v);
	cout << s.top() << " ";
	visited[start] = true;
	Edge<T> *p;
	while (!s.empty())
	{
		p = NodeTable[s.top()].adj;
		while (p != NULL)
		{
			int k = getVertexPos(p->dest);
			if (visited[k] == false)
			{
				visited[k] = true;
				s.push(p->dest);
				cout << s.top() << " ";
				p = NodeTable[getVertexPos(s.top())].adj;
			}
			else
				p = p->link;
		}
		s.pop();
	}
}
template<class T>
void Graphlnk<T>::GraphMatrix()
{
	int i = NumberOfVertices(),j;
	int	**m = new int*[i];
	for(j=0;j<i;j++)
		m[j]=new int[i];
	for (i = 0; i < NumberOfVertices(); i++)
		for (j = 0; j < NumberOfVertices(); j++)
			m[i][j] = 0;
	
	if (!GraphEmpty())
	{
		for (i = 0; i < numVertices; i++)
		{
			Edge<T>* p = NodeTable[i].adj;
			while (p != NULL)
			{
				int k = getVertexPos(p->dest);
				m[i][k]=1;
				p = p->link;
			}
		}
	}
	
	for (i = 0; i < NumberOfVertices(); i++)
	{
		for (j = 0;j < NumberOfVertices(); j++)
			cout<<m[i][j]<<" ";
		cout << endl;
	}
}