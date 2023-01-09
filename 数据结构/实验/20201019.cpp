#include<iostream>
#include<string>
#include<cstring>
#include<stack>
#include<cstdio>
using namespace std;
void Frequency(string);
void getNext(string,int []);
int KMPFind(string, string, int, int[]);
bool IsDigit(char);
double DoOperator(char, char, char);
int pri(char);
int main()
{
	string a;
	/*
	//题目一
	cout << "输入字符串:";
	cin >> a;
	Frequency(a);
	cout << endl;
	//题目二
	string Target, w, x;
	cout << "输入字符串:"; cin >> Target;
	cout << "输入需要替换的子串:"; cin >> w;
	cout << "输入替换后的子串:"; cin >> x;
	int* next = new int[w.length()];
	getNext(w, next);
	char finalStr[100000] = "";
	char temp[10000] = "";
	int i, j, k = 0,n=0;
	for (i = 0; i <= Target.length() - w.length(); i++) {
		for (j = 0; j < w.length(); j++)
			if (Target[i + j] != w[j])break;
		if (j == w.length()) {
			k++;
			if(i!=0){
				if(k == 1)
					strcat(finalStr, Target.substr(0, i).c_str());
				else if (i - 1 >= n + w.length())
					strcat(finalStr, Target.substr(n + w.length(), i - n - w.length()).c_str());
			}
			strcat(finalStr, x.c_str());

			n = i;
		}
	}
	if(n + w.length()<= Target.length() - 1)
		strcat(finalStr, Target.substr(n + w.length(), Target.length()- n - w.length()).c_str());
	cout << "替换后的字符串为:";
	cout << finalStr;
	cout << endl;
	//题目三-1： -1+23 =1-(2+3)= -4
	stack<char> OPTR;
	int value = -1;
	char v1, v2, v3;
	string m;
	cout << "输入表达式:";
	cin >> m;
	for(int i=0;i<m.length();i++)
		OPTR.push(m[i]);
	while (OPTR.empty() == false)
	{
		v1 = OPTR.top();
		OPTR.pop();
		if (OPTR.empty() == false) {
			v2 = OPTR.top();
			OPTR.pop();
			if (OPTR.empty() == false) {
				v3 = OPTR.top();
				OPTR.pop();
				if (IsDigit(v1) == true && IsDigit(v2) == true && IsDigit(v3) == false) {
					value = DoOperator(v1, v2, v3);
					char q = value + '0';
					OPTR.push(q);
				}
			}
			else
				OPTR.push(v2);
		}
		else{
			OPTR.push(v1); break;
		}
	}
	cout << "运算结果是:" ;
	cout << value << endl;
	*/
	//题目三-2：
    //例：1-(2+3)  转换前缀是：- 1 + 2 3
    //例：1+((2+3)*4)-5  转换前缀是：- + 1 * + 2 3 4 5
	string m;
	cout << "输入中缀表达式:";
	cin >> m;
	stack<char> S1, S2;
	for (int i = m.length() - 1; i >= 0; i--) {
		if (m[i]>='0'&&m[i]<='9')
			S1.push(m[i]);
		else if (m[i] == ')' || S2.empty() == true || S2.top() == ')')
			S2.push(m[i]);
		else if (m[i] == '(') {
			while (S2.top() != ')'){
				S1.push(S2.top());
				S2.pop();
			}
			S2.pop();
		}
			else{
				while (S2.empty() == false && pri(m[i]) < pri(S2.top())){
					S1.push(S2.top());
					S2.pop();
				}
				S2.push(m[i]);
			}
	}
	while (S2.empty()==false){
		S1.push(S2.top());
		S2.pop();
	}
	cout << "转化前缀表达式为:";
	while (S1.empty() == false) {
		cout << S1.top();
		S1.pop();
	}
	system("pause");
	return 0;
}
void Frequency(string a)
{
	char* x = new char[a.length()];
	int m= 0;
	for (int i = 0; i < a.length(); i++) {
		int k = 0;
		for (int j = 0; j < strlen(x); j++)
			if (a[i] == x[j])
				k++;
		if (k == 0) {
			x[m] = a[i];
			m++;
			for (int t = 0; t < a.length(); t++)
				if (a[i] == a[t])
					k++;
			cout << a[i] << "出现了" << k << "次" << endl;
		}
	}
}
void getNext(string a,int next[])
{
	int j = 0, k = -1, len =a.length();
	next[0] = -1;
	while (j < len)
		if (k == -1 || a[j] == a[k]) {
			j++; k++; next[j] = k;
		}
		else k = next[k];
}
int KMPFind(string T, string P, int k, int next[])
{
	int posP = 0, posT = k;
	while (posP < P.length() && posT < T.length())
		if (posP == -1 || P[posP] == T[posT])
		{
			posT++; posP++;
		}
		else
			posP = next[posP];
	if (posP <P.length()) return -1;
	else return posT - P.length();
}
bool IsDigit(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/')
		return false;
	else return true;
}
double DoOperator(char v1, char v2, char v3)
{
	switch (v3)
	{
	case '+':return (int)v2-int('0') + (int)v1-int('0'); break;
	case '-':return (int)v2 - (int)v1; break;
	case '*':return ((int)v2 - int('0')) * ((int)v1 - int('0')); break;
	case '/':if (v1 != 0)return ((int)v2 - int('0')) / ((int)v1 - int('0')); break;
	default:
		break;
	}
}
int pri(char a)
{
	switch (a){
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
	}
}

/*
	OPTR.push('#');
	cin>>ch;
	op = '#';
	while (ch != '#' || op != '#')
	{
		if (OPND.empty() == false)
		{
			v1 = OPND.top(); OPND.pop();
		}
		if (OPND.empty() == false)
		{
			v2 = OPND.top(); OPND.pop();
			if (ch == '+'){
				value = v1 + v2; OPND.push(value);
			}
			else if (ch == '-'){
				value = v2 - v1; OPND.push(value);
			}
			else if (ch == '*'){
				value = v1 * v2; OPND.push(value);
			}
			else if (ch == '/'){
				if (v1 == 0)cout << "Divide by 0!" << endl;
				else {
					value = v2 / v1; OPND.push(value);
				}
			}
			else {
				OPND.push((int)ch - int('0'));
				//cin >> ch;
			}
		}
		else {
			OPTR.push(ch);
		}
		cin >> ch;
		op=OPTR.top();
	}
	*/