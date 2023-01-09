#include<iostream>
#include<queue>
#include"BinaryTree.h"
using namespace std;

int main()
{
	BinaryTree<char> tree('#');//-+a##*b##-c##d##/e##f##
	tree.output(tree.getRoot());
	cout << "(ǰ�����)���������TreeA(��"<< tree.getRefValue()<<"����ս��):" << endl;
	tree.input();
	cout << "���������TreeA���ڵ������(�õ�ǰ�����):\n";
	tree.output(tree.getRoot());
	cout << "\n���������TreeAҶ�ڵ�ĸ���:\n"<<tree.LeafNodes(tree.getRoot());
	cout << endl;
	cout << "��������ǰ�����:\n";
	tree.preOrder(tree.getRoot());
	cout << "\n���������������:\n";
	tree.inOrder(tree.getRoot());
	cout << "\n�������ĺ������:\n";
	tree.postOrder(tree.getRoot());
	cout << "\n�������Ĳ�������:\n";
	tree.levelOrder(tree.getRoot());
	cout << endl;
	cout << "���ÿ������캯����ʼ��TreeB��,ǰ��������B:\n";
	BinaryTree<char> tree1(tree);
	//BinaryTree<char> tree1(tree.LeftSubtree(), tree.RootData(), tree.RightSubtree());
	tree1.output(tree1.getRoot());
	cout << endl;
	cout << "�ٵ���Delete����ɾ��TreeB���нڵ��,ǰ��������B:\n";
	tree1.Delete(tree1.getRoot());
	tree1.output(tree1.getRoot());
	if (tree1.IsEmpty())cout << "��ʱTreeB��Ϊ����" << endl;
	
	cout << "\n\n";
	BinaryTree<char> tree2('#');//ABD#G##E##CF#H###
	cout << "(ǰ�����)���������TreeC(��" << tree2.getRefValue() << "����ս��):" << endl;
	tree2.input();
	BinaryTree<char> tree3('#');
	cout << "TreeC������������ǰ�����Ϊ:\n";//ACFHBEDG
	tree2.SwapTree(tree3);
	tree3.output(tree3.getRoot());
	
	cout << "\n\n����һ����������ǰ��������������:\n";
	char *pre=new char[20],*in=new char[20];//ABDGECFH DGBEAHFC
	//string pre, in;
	cin>>pre>>in;
	int len = strlen(pre);
	//int len = pre.length();
	BinaryTree<char> tree4('#');
	cout << "��������ǰ��������������,���Եõ����ĺ������:\n";//GDEBHFCA
	tree4.Construct(pre, in, len);
	tree4.postOrder(tree4.getRoot());
	
	system("pause");
	return 0;
}