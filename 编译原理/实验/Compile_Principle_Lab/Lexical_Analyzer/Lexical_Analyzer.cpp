# include<iostream>
#include<stdio.h>
#include<stdlib.h>
# include<string.h>
# include<fstream>
# include<sstream>//流对象
# include<vector>
# include<map>
using namespace std;

void buildKeywords();
void buildIdentifier();
void buildConstant();
void buildOperator();
void buildDelim();
bool isDigit(char);
bool isLetter(char);
bool isOperator(string);
bool isDelim(string);
bool isDelim(char);
void addToken(string, int);
void lexical_analyzer();

struct token {
	string word;	//单词
	string type;	//类型
	int classNumber;//类号
	int internalCode;//内码
};

int state, nNum, idNum;
char c, pre;
string s = "";
vector<token>Token;//保存token序列，大小未知，所以采用vector保存
map<string, int>Keywords;
map<string, int>Identifier;
map<string, int>constantNumber;
map<string, int>Op;
map<string, int>Delim;

int main()
{
	// 建表
	buildKeywords();
	buildIdentifier();
	buildConstant();
	buildOperator();
	buildDelim();
	// 词法分析
	state = 0;
	lexical_analyzer();
	// 输出二元表
	cout << "token sequence:" << endl;
	cout << "\nRE\t\ttype\t\tclassNumber\t\tinternalCode" << endl;
	for (int i = 0; i < Token.size(); i++)
		cout << Token[i].word << "\t\t" << Token[i].type
		<< "\t\t" << Token[i].classNumber << "\t\t" << Token[i].internalCode << endl;
}

void lexical_analyzer()
{
	fstream input("TestCases.txt");
	while (!input.eof())
	{
		switch (state)
		{
		case 0:
			c = input.get();
			s = c;
			if (c == 9 || c == 10 || c == 13 || c == 32) {	//	delim：ASCII码，回车：13，换行：10，制表符：9，空格：32
				state = 0;
				s = "";
			}
			else if (isLetter(c))
				state = 1;
			else if (isDigit(c))
				state = 3;
			else if (c == '<')
				state = 8;
			else if (c == '=')
				state = 13;
			else if (c == '>')
				state = 16;
			else if (c == '+' || c == '-' || c == '&' || c == '|') {
				state = 20; pre = c;
			}
			else if (c == '*' || c == '/' || c == '%' || c == '^' || c == '!')
				state = 24;
			else if (isDelim(s))	state = 27;
			else if (isOperator(s))	state = 28;
			else state = 7;	//error
			break;
		case 1: //letter
			c = input.get();
			if (isLetter(c) || isDigit(c))s += c;	// keywords/id
			else state = 2;
			break;
		case 2:	//* 回退
			addToken(s, 1);	// keywords/id
			input.seekg(-1, ios::cur);
			state = 0;
			break;
		case 3:	// digit
			c = input.get();
			if (isDigit(c))s += c;	// constant
			else if (c == '.') {
				s += c;
				state = 4;
			}
			else state = 6;
			break;
		case 4:
			c = input.get();
			if (isDigit(c)) {
				s += c;
				state = 5;
			}
			else state = 7;	//error
			break;
		case 5:
			c = input.get();
			if (isDigit(c))	s += c;
			else state = 6;
			break;
		case 6:
			if (isLetter(c)) { // e.g."123a" is error, but "123;" needs to retract 
				s += c;
				state = 7;
			}
			else {
				addToken(s, 3);	// constant
				input.seekg(-1, ios::cur);
				state = 0;
			}
			break;
		case 7:	// error
			while (((c = input.get()) != EOF)) {
				if (isDelim(c) || c == 9 || c == 10 || c == 13 || c == 32)
					break;
				else s += c;
			}
			addToken(s, 6);// error
			input.seekg(-1, ios::cur);// then skip error continue
			state = 0;
			break;
		case 8:	// <
			c = input.get();
			if (c == '=') state = 9;	//	<=,Relop
			else if (c == '>') state = 10;	//	<>,Relop
			else if (c == '<')state = 11;	// <<,位左移运算符
			else state = 12;
			break;
		case 9:
			s += c;
			addToken(s, 4);	// op:relop
			state = 0;
			break;
		case 10:
			s += c;
			addToken(s, 4);	// op:relop
			state = 0;
			break;
		case 11:
			s += c;
			addToken(s, 4);	// op
			state = 0;
			break;
		case 12:	// * 回退
			addToken(s, 4);	// op:relop
			input.seekg(-1, ios::cur);
			state = 0;
			break;
		case 13:	// =
			c = input.get();
			if (c == '=') state = 14;	//	==,Resign
			else state = 15;
			break;
		case 14:
			s += c;
			addToken(s, 4); // op:relop
			state = 0;
			break;
		case 15:	//* 回退
			addToken(s, 4);	// op
			input.seekg(-1, ios::cur);
			state = 0;
			break;
		case 16:	// >
			c = input.get();
			if (c == '=') state = 17;	//	>=,Relop
			else if (c == '>')state = 18;	// >>,位右移运算符
			else state = 19;
			break;
		case 17:
			s += c;
			addToken(s, 4);	// op:relop
			state = 0;
			break;
		case 18:
			s += c;
			addToken(s, 4);	// op
			state = 0;
			break;
		case 19:	//* 回退
			addToken(s, 4);	// op:relop
			input.seekg(-1, ios::cur);
			state = 0;
			break;
		case 20:	//
			c = input.get();
			if (c == pre)	state = 21;	//++,--,&&,||
			else if (c == '=')	state = 22;	//+=,-=,&=,|=
			else state = 23;
			break;
		case 21:
			s += c;
			addToken(s, 4);	// op
			state = 0;
			break;
		case 22:
			s += c;
			addToken(s, 4);	// op
			state = 0;
			break;
		case 23:	//* 回退
			addToken(s, 4);	// op:+,-,&,|
			input.seekg(-1, ios::cur);
			state = 0;
			break;
		case 24:
			c = input.get();
			if (c == '=')state = 25;//*=,/=,%=,^=,!=
			else state = 26;
			break;
		case 25:
			s += c;
			addToken(s, 4);	// op
			state = 0;
			break;
		case 26:	//* 回退
			addToken(s, 4);	// op:*,/,%,^,!
			input.seekg(-1, ios::cur);
			state = 0;
			break;
		case 27:
			addToken(s, 5);
			state = 0;
			break;
		case 28:
			addToken(s, 4);
			state = 0;
			break;
		default:
			break;
		}
	}
}

void buildKeywords()
{
	Keywords["asm"] = 1;
	Keywords["auto"] = 2;
	Keywords["bool"] = 3;
	Keywords["break"] = 4;
	Keywords["case"] = 5;
	Keywords["catch"] = 6;
	Keywords["char"] = 7;
	Keywords["class"] = 8;
	Keywords["const"] = 9;
	Keywords["const_cast"] = 10;
	Keywords["continue"] = 11;
	Keywords["default"] = 12;
	Keywords["delete"] = 13;
	Keywords["do"] = 14;
	Keywords["double"] = 15;
	Keywords["dynamic"] = 16;
	Keywords["else"] = 17;
	Keywords["enum"] = 18;
	Keywords["explicit"] = 19;
	Keywords["export"] = 20;
	Keywords["extern"] = 21;
	Keywords["false"] = 22;
	Keywords["float"] = 23;
	Keywords["for"] = 24;
	Keywords["friend"] = 25;
	Keywords["goto"] = 26;
	Keywords["if"] = 27;
	Keywords["inline"] = 28;
	Keywords["int"] = 29;
	Keywords["long"] = 30;
	Keywords["mutable"] = 31;
	Keywords["namespace"] = 32;
	Keywords["new"] = 33;
	Keywords["operator"] = 34;
	Keywords["private"] = 35;
	Keywords["protected"] = 36;
	Keywords["public"] = 37;
	Keywords["register"] = 38;
	Keywords["reinterpret_cast"] = 39;
	Keywords["return"] = 40;
	Keywords["short"] = 41;
	Keywords["signed"] = 42;
	Keywords["sizeof"] = 43;
	Keywords["static"] = 44;
	Keywords["static_cast"] = 45;
	Keywords["struct"] = 46;
	Keywords["switch"] = 47;
	Keywords["template"] = 48;
	Keywords["this"] = 49;
	Keywords["throw"] = 50;
	Keywords["true"] = 51;
	Keywords["try"] = 52;
	Keywords["typedef"] = 53;
	Keywords["typeid"] = 54;
	Keywords["typename"] = 55;
	Keywords["union"] = 56;
	Keywords["unsigned"] = 57;
	Keywords["using"] = 58;
	Keywords["virtual"] = 59;
	Keywords["void"] = 60;
	Keywords["volatile"] = 61;
	Keywords["while"] = 62;
}

void buildIdentifier()
{
	Identifier["a"] = 1;
	Identifier["b"] = 2;
	Identifier["c"] = 3;
	Identifier["d"] = 4;
	Identifier["e"] = 5;
	Identifier["f"] = 6;
	Identifier["g"] = 7;
	Identifier["h"] = 8;
	Identifier["i"] = 9;
	Identifier["g"] = 10;
	Identifier["k"] = 11;
	Identifier["l"] = 12;
	Identifier["m"] = 13;
	Identifier["n"] = 14;
	Identifier["o"] = 15;
	Identifier["p"] = 16;
	Identifier["q"] = 17;
	Identifier["r"] = 18;
	Identifier["s"] = 19;
	Identifier["t"] = 20;
	Identifier["u"] = 21;
	Identifier["v"] = 22;
	Identifier["w"] = 23;
	Identifier["x"] = 24;
	Identifier["y"] = 25;
	Identifier["z"] = 26;
	Identifier["main"] = 27;
	Identifier["fun"] = 28;
	Identifier["number"] = 29;
	Identifier["value"] = 30;
	Identifier["state"] = 31;
	Identifier["width"] = 32;
	Identifier["height"] = 33;
	Identifier["max"] = 34;
	Identifier["min"] = 35;
	Identifier["ptr"] = 36;
	Identifier["str"] = 37;
	Identifier["token"] = 38;
	Identifier["words"] = 39;
	Identifier["constant"] = 40;
	Identifier["pre"] = 41;
	Identifier["next"] = 42;
	Identifier["count"] = 43;
	Identifier["example"] = 44;
	Identifier["comment"] = 45;
	Identifier["keyword"] = 46;
	Identifier["set"] = 47;
	Identifier["fp"] = 48;
	Identifier["name"] = 49;
	Identifier["type"] = 50;
	Identifier["num"] = 51;
	Identifier["letter"] = 52;
	idNum = 53;
}

void buildConstant()
{
	constantNumber["0"] = 0;
	constantNumber["1"] = 1;
	constantNumber["2"] = 2;
	constantNumber["3"] = 3;
	constantNumber["4"] = 4;
	constantNumber["5"] = 5;
	constantNumber["6"] = 6;
	constantNumber["7"] = 7;
	constantNumber["8"] = 8;
	constantNumber["9"] = 9;
	nNum = 10;
}

void buildOperator()
{
	Op["+"] = 1;
	Op["++"] = 2;
	Op["+="] = 3;
	Op["-"] = 4;
	Op["--"] = 5;
	Op["-="] = 6;
	Op["*"] = 7;
	Op["*="] = 8;
	Op["/"] = 9;
	Op["/="] = 10;
	Op["%"] = 11;
	Op["%="] = 12;
	Op["|"] = 13;
	Op["|="] = 14;
	Op["&"] = 15;
	Op["&="] = 16;
	Op["^"] = 17;
	Op["^="] = 18;
	Op["<<"] = 19;
	Op[">>"] = 20;
	Op["="] = 21;
	Op["!"] = 22;
	Op["!="] = 23;
	Op["&&"] = 24;
	Op["||"] = 25;
	Op["~"] = 26;
	Op["<"] = 27;
	Op["<="] = 28;
	Op["<>"] = 29;
	Op[">"] = 30;
	Op[">="] = 31;
	Op["=="] = 32;
}

void buildDelim()
{
	Delim["("] = 1;
	Delim[")"] = 2;
	Delim[","] = 3;
	Delim[";"] = 4;
	Delim["["] = 5;
	Delim["]"] = 6;
	Delim["{"] = 7;
	Delim["}"] = 8;
}

bool isDigit(char c)	//	0-9
{
	if (c >= 48 && c <= 57)
		return true;
	else
		return false;
}

bool isLetter(char c)	//	小写字母
{
	if (c >= 97 && c <= 122)
		return true;
	else
		return false;
}

bool isOperator(string word)
{
	map<string, int>::iterator iter;
	iter = Op.find(word);
	if (iter != Op.end())
		return true;
	else return false;
}

bool isDelim(string word)
{
	map<string, int>::iterator iter;
	iter = Delim.find(word);
	if (iter != Delim.end())
		return true;
	else return false;
}

bool isDelim(char word)
{
	map<string, int>::iterator iter;
	string str(1, word);  //string (size_t n, char c);
	iter = Delim.find(str);
	if (iter != Delim.end())
		return true;
	else return false;
}

void addToken(string word, int classNumber)
{
	map<string, int>::iterator iter;
	token t;
	switch (classNumber) {
	case 1:	//查看关键词表
		iter = Keywords.find(word);
		if (iter != Keywords.end()) {
			t = { word,"keywords",1,iter->second };
			Token.push_back(t);
		}
		else {	//查找是否为id
			iter = Identifier.find(word);
			if (iter == Identifier.end()) {	//未在id表中找到
				Identifier[word] = idNum;	//添加到id表中
				t = { word,"identifier",2,idNum++ };
				Token.push_back(t);
			}
			else {
				t = { word,"identifier",2,iter->second };
				Token.push_back(t);
			}
		}
		break;
	case 2:
		iter = Identifier.find(word);
		if (iter != Identifier.end()) {
			t = { word,"identifier",2,iter->second };
			Token.push_back(t);
		}
		else {
			Identifier[word] = idNum;	//添加到id表中
			t = { word,"identifier",2,idNum++ };
			Token.push_back(t);
		}
		break;
	case 3:
		iter = constantNumber.find(word);
		if (iter != constantNumber.end()) {
			t = { word,"constant_number",3,iter->second };
			Token.push_back(t);
		}
		else {
			constantNumber[word] = nNum;
			t = { word,"constant_number",3,nNum++ };
			Token.push_back(t);
		}
		break;
	case 4:
		iter = Op.find(word);
		if (iter != Op.end()) {
			t = { word,"operator",4,iter->second };
			Token.push_back(t);
		}
		break;
	case 5:
		iter = Delim.find(word);
		if (iter != Delim.end()) {
			t = { word,"delimeter",5,iter->second };
			Token.push_back(t);
		}
		break;
	default:	//error
		t = { word,"lexical error",-1,-1 };
		Token.push_back(t);
		break;
	}
}
