#include<iostream>
#include<string>
#include"heap.h"

struct HuffmanNode
{
	HuffmanNode():leftChild(-1),rightChild(-1),parent(-1){}
	bool operator<=(HuffmanNode& R) { return data <= R.data;}
	bool operator>(HuffmanNode& R) { return data>R.data; }
	float data;
	int id, leftChild, rightChild, parent;
};

class HuffmanTree
{
public:
	HuffmanTree(float [], int n);
	~HuffmanTree() { delete[]node; }
	bool isLeaf(HuffmanNode);
	void Coding();
	void printCode();
	void Encode();
private:
	int root;
	int size;
	int leafNum;
	HuffmanNode *node;
	string *code;
};
HuffmanTree::HuffmanTree(float w[], int n)
{
	size = 2 * n; 
	node = new HuffmanNode[size]; 
	code = new string[n];
	MinHeap<HuffmanNode> hp(size);
	int i,key = 0;
	HuffmanNode first, second;
	for (i = 0; i < n; i++)
	{
		code[i] = "";
		node[key].data = w[i];
		node[key].id = i;
		if (w[i] != 0)
			hp.Insert(node[key]);
		key++;
	}
	leafNum = key; 
	while(true)
	{
		hp.RemoveMin(first);
		hp.RemoveMin(second);
		node[key].leftChild = first.id;
		node[key].rightChild = second.id; 
		node[key].id = key;
		node[first.id].parent = node[key].id;
		node[second.id].parent = node[key].id;
		node[key].data = node[first.id].data + node[second.id].data;
		if (hp.isEmpty())
		{
			root = key;
			break;
		}
		hp.Insert(node[key]);
		key++;
	}
}
void HuffmanTree::Coding()
{
	for (int i = 0; i <size/2; i++)
	{
		if (isLeaf(node[i]))
		{
			int current = i;
			int father = node[i].parent;
			while (father != -1)
			{
				if (node[father].leftChild == current)
					code[node[i].id] = "0" + code[node[i].id];
				else
					code[node[i].id] = "1" + code[node[i].id];
				current = father;
				father = node[father].parent;
			}
		}
	}
}
bool HuffmanTree::isLeaf(HuffmanNode node)
{
	if (node.leftChild == -1 && node.rightChild == -1&&node.data!=0)
		return true;
	else return false;
}
void HuffmanTree::printCode()
{
	for (int i = 0; i < size/2; ++i)
	{
		if (isLeaf(node[i]))
		{
			char x = node[i].id + 97;
			cout << x << "的huffman编码为:" << code[node[i].id] << endl;
		}
	}
}
void HuffmanTree::Encode()
{
	for (int i = 0; i < size/2; i++)
	{
		if (isLeaf(node[i]))
		{
			int current = root; char x;
			for (int j = 0; j < code[node[i].id].size(); j++)
			{
				if (code[node[i].id][j] == '0')
					current = node[current].leftChild;
				if (code[node[i].id][j] == '1')
					current = node[current].rightChild;
			}
			x = node[current].id + 97;
			cout << code[node[i].id] << "解码后对应的字符是" << x << endl;
		}
	}
}