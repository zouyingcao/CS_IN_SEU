#include<iostream>
#include<queue>
#include"BinaryTree.h"
using namespace std;

int main()
{
	BinaryTree<char> tree('#');//-+a##*b##-c##d##/e##f##
	tree.output(tree.getRoot());
	cout << "(前序遍历)输入二叉树TreeA(用"<< tree.getRefValue()<<"代表空结点):" << endl;
	tree.input();
	cout << "输出二叉树TreeA各节点的数据(用的前序遍历):\n";
	tree.output(tree.getRoot());
	cout << "\n输出二叉树TreeA叶节点的个数:\n"<<tree.LeafNodes(tree.getRoot());
	cout << endl;
	cout << "二叉树的前序遍历:\n";
	tree.preOrder(tree.getRoot());
	cout << "\n二叉树的中序遍历:\n";
	tree.inOrder(tree.getRoot());
	cout << "\n二叉树的后序遍历:\n";
	tree.postOrder(tree.getRoot());
	cout << "\n二叉树的层次序遍历:\n";
	tree.levelOrder(tree.getRoot());
	cout << endl;
	cout << "调用拷贝构造函数初始化TreeB后,前序遍历输出B:\n";
	BinaryTree<char> tree1(tree);
	//BinaryTree<char> tree1(tree.LeftSubtree(), tree.RootData(), tree.RightSubtree());
	tree1.output(tree1.getRoot());
	cout << endl;
	cout << "再调用Delete函数删除TreeB所有节点后,前序遍历输出B:\n";
	tree1.Delete(tree1.getRoot());
	tree1.output(tree1.getRoot());
	if (tree1.IsEmpty())cout << "此时TreeB已为空树" << endl;
	
	cout << "\n\n";
	BinaryTree<char> tree2('#');//ABD#G##E##CF#H###
	cout << "(前序遍历)输入二叉树TreeC(用" << tree2.getRefValue() << "代表空结点):" << endl;
	tree2.input();
	BinaryTree<char> tree3('#');
	cout << "TreeC交换二叉树的前序遍历为:\n";//ACFHBEDG
	tree2.SwapTree(tree3);
	tree3.output(tree3.getRoot());
	
	cout << "\n\n输入一个二叉树的前序遍历和中序遍历:\n";
	char *pre=new char[20],*in=new char[20];//ABDGECFH DGBEAHFC
	//string pre, in;
	cin>>pre>>in;
	int len = strlen(pre);
	//int len = pre.length();
	BinaryTree<char> tree4('#');
	cout << "根据它的前序遍历和中序遍历,可以得到它的后序遍历:\n";//GDEBHFCA
	tree4.Construct(pre, in, len);
	tree4.postOrder(tree4.getRoot());
	
	system("pause");
	return 0;
}