#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<stdio.h>
using namespace std;
void syntax_parser(string str);
int terminalNum; // 终结符的个数
int nonTerminalNum; // 非终结符的个数
string** LL1ForecastAnalysisTable;// LL(1)预测分析表
map<string, int> terminalSet;// 终结符(包含结束符#)的集合，map映射表示在分析表的第几列
map<string, int> nonTerminalSet;// 非终结符的集合，map映射表示在分析表的第几行
vector<string>pushdownStack;// 下推栈

vector<vector<void*>>constructSyntaxTreeStack;//辅助构建语法树的栈
struct node
{
	string name;//节点名称
	int cnt;//子树宽度
	vector<node*>child;
};
typedef node* TreeNode;
struct Tree
{
	TreeNode root;
};
Tree syntaxTree;//语法树
void printTree(TreeNode,int);

int main()
{
	cout << "请输入终结符的个数:";	cin >> terminalNum;
	cout << "请输入非终结符的个数:";	cin >> nonTerminalNum;
	cout << "请依次输入预测分析表的内容，出错标志请用英文字符_表示:"<<endl;
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
	cout << "请输入要分析的语言: ";
	string str;	cin >> str;
	syntax_parser(str);
	return 0;
}
void syntax_parser(string str)
{
	cout << "步骤\t\t栈内\t\t输入串\t\t所用产生式\t\t动作" << endl;
	cout << "初态\t\t#" << LL1ForecastAnalysisTable[1][0] << "\t\t" << str << "#\t\t\n";
	str += "#";
	int i = 0, ptr = 0;// i代表进行到步骤i,ptr代表分析到输入语言字符串第几个
	string X, a(1, str[ptr]);// X代表栈顶字符,a为当前读入符号
	string inStack, inputStr;// inStack代表栈内，inputStr代表输入串
	pushdownStack.clear();// 使下推栈为空
	pushdownStack.push_back("#");// 结束符#入栈
	pushdownStack.push_back(LL1ForecastAnalysisTable[1][0]);// 文法开始符号入栈

	syntaxTree.root = new node;//语法树根节点
	auto cur_node = syntaxTree.root;
	cur_node->name = LL1ForecastAnalysisTable[1][0];
	
	constructSyntaxTreeStack.push_back(vector<void*>());//进入语法树的下一层
	constructSyntaxTreeStack.back().push_back(0);//语法栈中两个局部变量
	constructSyntaxTreeStack.back().push_back(cur_node);

	while (++i)
	{
		X = pushdownStack.back();// 下推栈栈顶符号
		if (X == a)
		{
			if (a == "#") {	// X=a='#',表示识别成功
				cout << "\t\t识别成功" << endl;
				break;
			}
			else {	// X=a≠'#',表示匹配
				ptr++;//读头前进一格
				pushdownStack.pop_back();//弹出栈顶符号X
				inStack = "";
				for (int i = 0; i < pushdownStack.size(); i++)
					inStack += pushdownStack[i];
				inputStr = "";
				for (int i = ptr; i < str.size(); i++)
					inputStr += str[i];
				cout << i << "\t\t" << inStack << "\t";
				if (pushdownStack.size() <= 5)cout << "\t";
				cout << inputStr << "\t\t\t\t\t" << a << "匹配" << endl;
				a = str[ptr];
				
				// 语法树栈调整(到树叶节点时)，索引右移动，constructSyntaxTreeStack.size()为语法树层数
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
			if (terminalSet[X]) { //X∈终结符，但X≠a，则调ERROR处理
				cout << i << "\t\t出错\n";
				return;
			}
			else { //X∈非终结符，查预测分析表M
				int row = nonTerminalSet[X], col = terminalSet[a];
				string production = LL1ForecastAnalysisTable[row][col]; // M[X,a]
				if (production == "_"){	//存放着出错标志
					cout << i << "\t\t出错\n";
					return;
				}
				else {	// 存放着关于X的产生式
					pushdownStack.pop_back();	// 弹出栈顶符号X
					if (production != "epsilon")	// 将产生式右部以自右向左的顺序压入栈内
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
					cout << "推导";
					if (production == "epsilon")
						cout << "空串";
					cout << endl;
					
					int index = (int)constructSyntaxTreeStack.back()[0];
					TreeNode Node = (TreeNode)constructSyntaxTreeStack.back()[index + 1];
					cout << Node->name << endl;
					//进入语法树下一层
					constructSyntaxTreeStack.push_back(vector<void*>());
					constructSyntaxTreeStack.back().push_back(0);

					//产生式右部
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
					if (production == "epsilon")//推导出空串时也需调整语法树
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
	cout << "输出语法树如下：" << endl;
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