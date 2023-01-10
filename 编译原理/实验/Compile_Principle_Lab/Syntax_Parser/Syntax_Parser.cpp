#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<stdio.h>
using namespace std;
void syntax_parser(string str);
int terminalNum; // �ս���ĸ���
int nonTerminalNum; // ���ս���ĸ���
string** LL1ForecastAnalysisTable;// LL(1)Ԥ�������
map<string, int> terminalSet;// �ս��(����������#)�ļ��ϣ�mapӳ���ʾ�ڷ�����ĵڼ���
map<string, int> nonTerminalSet;// ���ս���ļ��ϣ�mapӳ���ʾ�ڷ�����ĵڼ���
vector<string>pushdownStack;// ����ջ

vector<vector<void*>>constructSyntaxTreeStack;//���������﷨����ջ
struct node
{
	string name;//�ڵ�����
	int cnt;//�������
	vector<node*>child;
};
typedef node* TreeNode;
struct Tree
{
	TreeNode root;
};
Tree syntaxTree;//�﷨��
void printTree(TreeNode,int);

int main()
{
	cout << "�������ս���ĸ���:";	cin >> terminalNum;
	cout << "��������ս���ĸ���:";	cin >> nonTerminalNum;
	cout << "����������Ԥ�����������ݣ������־����Ӣ���ַ�_��ʾ:"<<endl;
	LL1ForecastAnalysisTable = new string * [nonTerminalNum + 1];
	for (int i = 0; i <= nonTerminalNum; i++){
		LL1ForecastAnalysisTable[i] = new string[terminalNum + 2];
		for (int j = 0; j <= terminalNum +1; j++){
			if (i == 0 && j == 0)LL1ForecastAnalysisTable[i][j] = " ";
			else {
				cin >> LL1ForecastAnalysisTable[i][j];
				if (i == 0)terminalSet[LL1ForecastAnalysisTable[i][j]] = j;
				if (j == 0)nonTerminalSet[LL1ForecastAnalysisTable[i][j]] = i;
			}
		}
	}
	cout << "������Ҫ����������: ";
	string str;	cin >> str;
	syntax_parser(str);
	return 0;
}
void syntax_parser(string str)
{
	cout << "����\t\tջ��\t\t���봮\t\t���ò���ʽ\t\t����" << endl;
	cout << "��̬\t\t#" << LL1ForecastAnalysisTable[1][0] << "\t\t" << str << "#\t\t\n";
	str += "#";
	int i = 0, ptr = 0;// i������е�����i,ptr������������������ַ����ڼ���
	string X, a(1, str[ptr]);// X����ջ���ַ�,aΪ��ǰ�������
	string inStack, inputStr;// inStack����ջ�ڣ�inputStr�������봮
	pushdownStack.clear();// ʹ����ջΪ��
	pushdownStack.push_back("#");// ������#��ջ
	pushdownStack.push_back(LL1ForecastAnalysisTable[1][0]);// �ķ���ʼ������ջ

	syntaxTree.root = new node;//�﷨�����ڵ�
	auto cur_node = syntaxTree.root;
	cur_node->name = LL1ForecastAnalysisTable[1][0];
	
	constructSyntaxTreeStack.push_back(vector<void*>());//�����﷨������һ��
	constructSyntaxTreeStack.back().push_back(0);//�﷨ջ�������ֲ�����
	constructSyntaxTreeStack.back().push_back(cur_node);

	while (++i)
	{
		X = pushdownStack.back();// ����ջջ������
		if (X == a)
		{
			if (a == "#") {	// X=a='#',��ʾʶ��ɹ�
				cout << "\t\tʶ��ɹ�" << endl;
				break;
			}
			else {	// X=a��'#',��ʾƥ��
				ptr++;//��ͷǰ��һ��
				pushdownStack.pop_back();//����ջ������X
				inStack = "";
				for (int i = 0; i < pushdownStack.size(); i++)
					inStack += pushdownStack[i];
				inputStr = "";
				for (int i = ptr; i < str.size(); i++)
					inputStr += str[i];
				cout << i << "\t\t" << inStack << "\t";
				if (pushdownStack.size() <= 5)cout << "\t";
				cout << inputStr << "\t\t\t\t\t" << a << "ƥ��" << endl;
				a = str[ptr];
				
				// �﷨��ջ����(����Ҷ�ڵ�ʱ)���������ƶ���constructSyntaxTreeStack.size()Ϊ�﷨������
				while (constructSyntaxTreeStack.size() > 1)
				{
					constructSyntaxTreeStack.back()[0] = (void*)((int)constructSyntaxTreeStack.back()[0] + 1);
					int index = (int)constructSyntaxTreeStack.back()[0];
					int parent_idx = (int)constructSyntaxTreeStack[constructSyntaxTreeStack.size() - 2][0];
					TreeNode Node = (TreeNode)constructSyntaxTreeStack[constructSyntaxTreeStack.size() - 2][parent_idx + 1];
					if (Node->child.size() == index)
					{
						constructSyntaxTreeStack.pop_back();
						continue;
					}
					break;
				}
			}
		}
		else {
			if (terminalSet[X]) { //X���ս������X��a�����ERROR����
				cout << i << "\t\t����\n";
				return;
			}
			else { //X�ʷ��ս������Ԥ�������M
				int row = nonTerminalSet[X], col = terminalSet[a];
				string production = LL1ForecastAnalysisTable[row][col]; // M[X,a]
				if (production == "_"){	//����ų����־
					cout << i << "\t\t����\n";
					return;
				}
				else {	// ����Ź���X�Ĳ���ʽ
					pushdownStack.pop_back();	// ����ջ������X
					if (production != "epsilon")	// ������ʽ�Ҳ������������˳��ѹ��ջ��
						for (int i = production.size() - 1; i >= 0; i--)
							if(production[i]=='\''){
								i--;
								pushdownStack.push_back(string(1, production[i]) + "'");
							}
							else
								pushdownStack.push_back(string(1, production[i]));
					inStack = "";
					for (int i = 0; i < pushdownStack.size(); i++)
						inStack += pushdownStack[i];
					inputStr = "";
					for (int i = ptr; i < str.size(); i++)
						inputStr += str[i];
					cout << i << "\t\t" << inStack << "\t";
					if (pushdownStack.size() < 5)cout << "\t";
					cout << inputStr << "\t\t" << X << "->" << production << "\t\t";
					if (production.size() < 4)cout << "\t";
					cout << "�Ƶ�";
					if (production == "epsilon")
						cout << "�մ�";
					cout << endl;
					
					int index = (int)constructSyntaxTreeStack.back()[0];
					TreeNode Node = (TreeNode)constructSyntaxTreeStack.back()[index + 1];
					cout << Node->name << endl;
					//�����﷨����һ��
					constructSyntaxTreeStack.push_back(vector<void*>());
					constructSyntaxTreeStack.back().push_back(0);

					//����ʽ�Ҳ�
					if(production != "epsilon")
						for (int i = 0; i < production.size(); i++)
						{
							TreeNode newNode = new node;
							if (i + 1 < production.size() && production[i + 1] == '\'') {
								newNode->name = string(1, production[i]) + "'";
								i++;
							}
							else 
								newNode->name = string(1, production[i]);
							Node->child.push_back(newNode);
							constructSyntaxTreeStack.back().push_back(newNode);
						}
					else {
						TreeNode newNode = new node;
						newNode->name = "epsilon";
						Node->child.push_back(newNode);
						constructSyntaxTreeStack.back().push_back(newNode);
					}
					if (production == "epsilon")//�Ƶ����մ�ʱҲ������﷨��
					{
						while (constructSyntaxTreeStack.size() > 1)
						{
							constructSyntaxTreeStack.back()[0] = (void*)((int)constructSyntaxTreeStack.back()[0] + 1);
							int index = (int)constructSyntaxTreeStack.back()[0];
							int parent_idx = (int)constructSyntaxTreeStack[constructSyntaxTreeStack.size() - 2][0];
							TreeNode Node = (TreeNode)constructSyntaxTreeStack[constructSyntaxTreeStack.size() - 2][parent_idx + 1];
							if (Node->child.size() == index)
							{
								constructSyntaxTreeStack.pop_back();
								continue;
							}
							break;
						}
					}
				}
			}
		}
	}
	cout << "����﷨�����£�" << endl;
	printTree(syntaxTree.root,0);
}

void printTree(TreeNode Node,int deep)
{
	for (int i = 0; i <= deep; i++)
		cout << "\t";
	cout << Node->name << endl;
	for (int i = 0; i < Node->child.size(); i++)
		printTree(Node->child[i], deep + 1);
}