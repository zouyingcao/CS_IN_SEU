#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<stack>
using namespace std;

template<class T>
struct BinTreeNode {
	T data;
	BinTreeNode<T>* leftChild, * rightChild;
	BinTreeNode() :leftChild(NULL), rightChild(NULL){}
	BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL)
		:data(x), leftChild(l), rightChild(r) {}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree(T x) :root(NULL), refValue(x), LeafNodesNum(0) {}	//constructor
	~BinaryTree() { Delete(root); }									//destructor
	BinaryTree(BinaryTree<T>&);
	//BinaryTree(BinaryTree<T>& ,T& ,BinaryTree<T>&);				//copy constructor
	
	bool IsEmpty() { return(root == NULL) ? true : false; }			//判断二叉树是否为空树
	void Delete(BinTreeNode<T>* &);									//删除节点
	BinTreeNode<T>* create();										//创建二叉树并返回根节点
	void input() { root=create(); }
	void output(BinTreeNode<T>*);
	
	BinTreeNode<T>* copy(BinTreeNode<T>*);
	BinaryTree<T> LeftSubtree();									
	BinaryTree<T> RightSubtree();								
	
	void preOrder(BinTreeNode<T>*);									//前序遍历
	void inOrder(BinTreeNode<T>*);									//中序遍历
	void postOrder(BinTreeNode<T>*);								//后序遍历
	void levelOrder(BinTreeNode<T>*);								//层次序遍历
	
	int LeafNodes(BinTreeNode<T>*);									//返回叶节点过的个数
	
	T& RootData() { return root->data; }
	T getRefValue() { return refValue; }
	BinTreeNode<T>*& getRoot() { return root; }

	BinTreeNode<T>* swapCopy(BinTreeNode<T>*);
	void SwapTree(BinaryTree<T>&);									//交换二叉树
	BinTreeNode<T>* BinaryTreeFromPreorderAndInorder(T*,T*,int);	//前序遍历和中序遍历还原二叉树
	void Construct(T* pre, T* in, int l) 
	{ root = BinaryTreeFromPreorderAndInorder(pre,in, l); }
	
private:
	BinTreeNode<T>* root;
	T refValue;														//截止字符
	int LeafNodesNum;
}; 

template<class T>
void BinaryTree<T>::output(BinTreeNode<T>*root)
{
	if (root!=NULL)
	{
		cout << root->data << ' ';
		output(root->leftChild);
		output(root->rightChild);
	}
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::copy(BinTreeNode<T>*  orignode)
{
	if (orignode)
	{
		BinTreeNode<T>* temp = new BinTreeNode<T>;
		temp->data = orignode->data;
		temp->leftChild = copy(orignode->leftChild);
		temp->rightChild = copy(orignode->rightChild);
		return temp;
	}
	else 
		return NULL;
}

template<class T>
BinaryTree<T> BinaryTree<T>::LeftSubtree()
{
	BinaryTree<T> left(refValue);
	left.root = copy(root->leftChild);
	return left;
}

template<class T>
BinaryTree<T> BinaryTree<T>::RightSubtree()
{
	BinaryTree<T> right(refValue);
	right.root = copy(root->rightChild);
	return right;
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::create()
{
	T elem;
	BinTreeNode<T>* p;
	cin >> elem;
	if (elem == refValue)
		p = NULL;
	else {
		p = new BinTreeNode<T>;
		p->data = elem;
		p->leftChild = create();
		p->rightChild = create();
	}
	return p;
}

template<class T>
//BinaryTree<T>::BinaryTree(BinaryTree<T>& bt1, T& item, BinaryTree<T>& bt2)
BinaryTree<T>::BinaryTree(BinaryTree<T>& bt)
{
	//if (bt2 == NULL)	return;
	//if (root || &bt1 == &bt2)return;
	//root->data = item;
	//root->leftChild = copy(bt1.root);
	//root->rightChild = copy(bt2.root);

	root = copy(bt.root);
}

template<class T>
void BinaryTree<T>::Delete(BinTreeNode<T>* &subTree)
{
	if (subTree!=NULL)
	{
		Delete(subTree->leftChild);
		Delete(subTree->rightChild);
		delete subTree;
		subTree = NULL;			//关键
	}
}

template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		cout << subTree->data << ' ';
		preOrder(subTree->leftChild);
		preOrder(subTree->rightChild);
	}
}

template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		inOrder(subTree->leftChild);
		cout << subTree->data << ' ';
		inOrder(subTree->rightChild);
	}
}

template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		postOrder(subTree->leftChild);
		postOrder(subTree->rightChild);
		cout << subTree->data << ' ';
	}
}

template<class T>
void BinaryTree<T>::levelOrder(BinTreeNode<T>* root)
{
	if (root == NULL)
		return;
	BinTreeNode<T>* cur = root;
	queue<BinTreeNode<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		cur = q.front();
		cout << cur->data << ' ';
		q.pop();
		if (cur->leftChild)
			q.push(cur->leftChild);
		if (cur->rightChild)
			q.push(cur->rightChild);
	}
}

template<class T>
int BinaryTree<T>::LeafNodes(BinTreeNode<T>* subTree)
{
	if (subTree == NULL)
		return 0;
	if (subTree->leftChild == NULL && subTree->rightChild == NULL)
		LeafNodesNum++;
	LeafNodes(subTree->leftChild);
	LeafNodes(subTree->rightChild);
	return LeafNodesNum;
}

template<class T>
void BinaryTree<T>::SwapTree(BinaryTree<T>&sTree)
{
	sTree.root = swapCopy(root);
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::swapCopy(BinTreeNode<T>* orignode)
{
	if (orignode)
	{
		BinTreeNode<T>* temp=new BinTreeNode<T>;
		temp->data = orignode->data;
		temp->leftChild = swapCopy(orignode->rightChild);
		temp->rightChild = swapCopy(orignode->leftChild);
		return temp;
	}
	else
		return NULL;
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::BinaryTreeFromPreorderAndInorder(T* pre, T* in, int len)
{
	if (len == 0)return NULL;
	BinTreeNode<T>* temp = new BinTreeNode<T>;;
	temp->data = pre[0];
	int rootindex = 0;
	for (; rootindex < len; rootindex++)
		if (in[rootindex] == pre[0])break;
	temp->leftChild = BinaryTreeFromPreorderAndInorder(pre + 1, in, rootindex);
	temp->rightChild = BinaryTreeFromPreorderAndInorder(pre + rootindex + 1, in + rootindex + 1, len - rootindex - 1);
	return temp;
}
#endif