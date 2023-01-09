#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
template<class E, class K>
struct AVLNode {
	int bf;
	E data;
	AVLNode<E, K>* left, * right;
	AVLNode() :left(NULL), right(NULL), bf(0) {}
	AVLNode(const E d, AVLNode<E, K>* L = NULL, AVLNode<E, K>* R = NULL)
		:data(d), left(L), right(R), bf(0) {}
	~AVLNode() {}
	void setData(E d) { data = d; }
	E getData() { return data; }
};
template<class E, class K>
class AVL
{
public:
	AVL() :root(NULL) {}
	AVL(K value) :RefValue(value), root(NULL) {}
	~AVL() {};
	bool Search(const K x)
	{
		return (Search(x,root) != NULL) ? true : false;
	}
	void createAVL(fstream &inAVL);
	void outputAVL(fstream &outAVL);
	void displayAVL();
	void TraverseRVL(AVLNode<E, K>* ptr);
	bool Insert(const E& el) { return Insert(el, root); }
	bool Remove(const K x) { return Remove(x, root); }
private:
	AVLNode<E, K>* root;
	K RefValue;
	AVLNode<E, K>* Search(const K x, AVLNode<E, K>* ptr);
	bool Insert(const E& e1, AVLNode<E, K>*& ptr);
	bool Remove(const K x, AVLNode<E, K>*& ptr);
	void RotateL(AVLNode<E, K>*& ptr);//左单旋
	void RotateR(AVLNode<E, K>*& ptr);//右单旋
	void RotateLR(AVLNode<E, K>*& ptr);//先左后右双旋
	void RotateRL(AVLNode<E, K>*& ptr);//先右后左双旋
	int Level(AVLNode<E, K>* root,AVLNode<E, K>* ptr,int h)const;//求层次
};
template<class E, class K>
void AVL<E, K>::createAVL(fstream& inAVL)
{
	int Num;
	inAVL >> Num;
	for(int i=1;i<=Num;i++)
	{ 
		E elem;
		inAVL >> elem;
		Insert(elem);
		cout << "----" << i << "------" << endl;
		displayAVL();
		cout << "------------" << endl;
	}
}
template<class E, class K>
void AVL<E, K>::outputAVL(fstream& outAVL)
{
}
template<class E, class K>
void AVL<E, K>::TraverseRVL(AVLNode<E, K>* ptr)
{
	if (ptr != NULL)
	{
		TraverseRVL(ptr->right);
		for (int i = 0; i < 5 * (Level(root,ptr,1)-1); i++)
			cout << " ";
		cout <<"....("<< ptr->data << "," << ptr->bf << ")\n";
		TraverseRVL(ptr->left);
	}
}
template<class E, class K>
void AVL<E, K>::displayAVL()
{
	TraverseRVL(root);
	cout << endl;
}
template<class E, class K>
bool AVL<E, K>::Insert(const E& e1, AVLNode<E, K>*& ptr)
{
	AVLNode<E, K>* pr = NULL, * p = ptr, * q; int d;
	stack<AVLNode<E, K>*>st;
	while (p != NULL)							//寻找插入位置
	{
		if (e1 == p->data)return false;			//找到等于e1的结点，不插入
		pr = p; st.push(pr);					//否则用栈记忆查找路径
		if (e1 < p->data)p = p->left;
		else p = p->right;
	}
	p = new AVLNode<E, K>(e1);
	if (p == NULL) { cerr << "存储空间不足！" << endl; exit(1); }
	if (pr == NULL) { ptr = p; return true; }	//空树，新结点成为根结点
	if (e1 < pr->data)pr->left = p;				//新结点插入
	else pr->right = p;
	cout << "*****" << endl;
	displayAVL();								//未调整前输出AVL树
	cout << "*****" << endl;
	while (st.empty()==false)					//重新平衡化
	{
		pr = st.top();
		st.pop(); cout <<"\t\t"<< pr->data << "出栈  :";
		if (p == pr->left)pr->bf--;
		else pr->bf++;
		if (pr->bf == 0)break;					//在结点pr的较矮的子树上插入了新结点，结点pr处平衡
		if (pr->bf == 1 || pr->bf == -1)		//|pr->bf|==1,向上回溯，考察pr父结点的平衡情况
		{
			p = pr; cout << "第2种情况，不平衡但不调整，|bf|=1." << endl;
		}
		else
		{
			cout<<"第2种情况，不平衡调整，|bf|=2.";
			d = (pr->bf < 0) ? -1 : 1;			//区别单双旋转标志
			if (p->bf == d) {					//两结点平衡因子同号，单旋转
				if (d == -1) {
					RotateR(pr);				//右单旋转
					cout << "右单旋的起始结点" << pr->data << endl;
				}
				else {
					RotateL(pr);				//左单旋转
					cout << "左单旋的起始结点" << pr->data << endl;
				}
			}
			else {								//两结点平衡因子反号，双旋转
				if (d == -1) {
					RotateLR(pr);		//先左后右双旋转
					cout << "左右双旋的起始结点" << pr->data << endl;
				}
				else {
					RotateRL(pr);				//先右后左双旋转
					cout << "右左双旋的起始结点" << pr->data << endl;
				}
			}
			break;								//不再向上调整
		}
	}
	if (st.empty() == true)ptr = pr;			//调整到树的根结点
	else {										//中间重新链接
		q=st.top();
		if (q->data > pr->data)q->left = pr;
		else q->right = pr;
	}
	return true;
}
template<class E, class K>
AVLNode<E, K>* AVL<E, K>::Search(const K x, AVLNode<E, K>* ptr)
{
	if (ptr == NULL)return NULL;
	else if (x < ptr->data)return Search(x, ptr->left);	//左子树中继续搜索
	else if (x > ptr->data)return Search(x, ptr->right);//右子树中继续搜索
	else return ptr;									//搜索成功
}
template<class E,class K>
bool AVL<E, K>::Remove(const K x, AVLNode<E, K>*& ptr)
{
	AVLNode<E, K>* temp;
	if (ptr != NULL)
	{
		if (x < ptr->data)Remove(x, ptr->left);
		else if (x > ptr->data)Remove(x, ptr->right);
		else if (ptr->left != NULL && ptr->right != NULL)
		{
			temp = ptr->right;
			while (temp->left != NULL)temp = temp->left;
			ptr->data = temp->data;
			Remove(ptr->data, ptr->right);
		}
		else {
			temp = ptr;
			if (temp->left == NULL)ptr = ptr->right;
			else ptr = ptr->left;
			delete temp;
			return true;
		}
	}
	return false;
}
template<class E, class K>
void AVL<E, K>::RotateL(AVLNode<E, K>*& ptr)
{
	AVLNode<E,K>* subL = ptr;//要左旋转的结点
	ptr = subL->right;//原根的右子女
	subL->right = ptr->left;//ptr成为新根卸掉左边负载
	ptr->left = subL;//左单旋转，ptr为新根
	ptr->bf = subL->bf = 0;
}
template<class E, class K>
void AVL<E, K>::RotateR(AVLNode<E, K>*& ptr)
{
	AVLNode<E,K>* subL = ptr;
	ptr = subL->left;
	subL->left = ptr->right;
	ptr->right = subL;
	ptr->bf = subL->bf = 0;
}
template<class E, class K>
void AVL<E, K>::RotateLR(AVLNode<E, K>*& ptr)
{
	AVLNode<E,K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;
	ptr->left =	subL;
	if (ptr->bf <= 0)subL->bf = 0;
	else subL->bf = -1;
	subR->left = ptr->right;
	ptr->right = subR;
	if (ptr->bf == -1)subR->bf = 1;
	else subR -> bf = 0;
	ptr->bf = 0;
}
template<class E, class K>
void AVL<E, K>::RotateRL(AVLNode<E, K>*& ptr)
{
	AVLNode<E,K>* subL= ptr, * subR = subL->right;
	ptr = subR->left;
	subR->left = ptr->right;
	ptr->right = subR;
	if (ptr->bf>= 0)subR->bf = 0;
	else subR->bf = 1;
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf == 1)subL->bf = -1;
	else subL ->bf = 0;
	ptr->bf = 0;
}
template<class E, class K>
int AVL<E, K>::Level(AVLNode<E, K>* b,AVLNode<E, K>* p,int h)const
{
	int l;
	if (b == NULL)
		return 0;
	else if (b->data == p->data)
		return h;
	else
	{
		l = Level(b->left, p, h + 1); // 在左子树中查找
		if (l != 0)
			return l;
		else // 在左子树中未找到,再在右子树中查找
			return Level(b->right, p, h + 1);
	}
}