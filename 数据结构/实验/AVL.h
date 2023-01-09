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
	void RotateL(AVLNode<E, K>*& ptr);//����
	void RotateR(AVLNode<E, K>*& ptr);//�ҵ���
	void RotateLR(AVLNode<E, K>*& ptr);//�������˫��
	void RotateRL(AVLNode<E, K>*& ptr);//���Һ���˫��
	int Level(AVLNode<E, K>* root,AVLNode<E, K>* ptr,int h)const;//����
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
	while (p != NULL)							//Ѱ�Ҳ���λ��
	{
		if (e1 == p->data)return false;			//�ҵ�����e1�Ľ�㣬������
		pr = p; st.push(pr);					//������ջ�������·��
		if (e1 < p->data)p = p->left;
		else p = p->right;
	}
	p = new AVLNode<E, K>(e1);
	if (p == NULL) { cerr << "�洢�ռ䲻�㣡" << endl; exit(1); }
	if (pr == NULL) { ptr = p; return true; }	//�������½���Ϊ�����
	if (e1 < pr->data)pr->left = p;				//�½�����
	else pr->right = p;
	cout << "*****" << endl;
	displayAVL();								//δ����ǰ���AVL��
	cout << "*****" << endl;
	while (st.empty()==false)					//����ƽ�⻯
	{
		pr = st.top();
		st.pop(); cout <<"\t\t"<< pr->data << "��ջ  :";
		if (p == pr->left)pr->bf--;
		else pr->bf++;
		if (pr->bf == 0)break;					//�ڽ��pr�Ľϰ��������ϲ������½�㣬���pr��ƽ��
		if (pr->bf == 1 || pr->bf == -1)		//|pr->bf|==1,���ϻ��ݣ�����pr������ƽ�����
		{
			p = pr; cout << "��2���������ƽ�⵫��������|bf|=1." << endl;
		}
		else
		{
			cout<<"��2���������ƽ�������|bf|=2.";
			d = (pr->bf < 0) ? -1 : 1;			//����˫��ת��־
			if (p->bf == d) {					//�����ƽ������ͬ�ţ�����ת
				if (d == -1) {
					RotateR(pr);				//�ҵ���ת
					cout << "�ҵ�������ʼ���" << pr->data << endl;
				}
				else {
					RotateL(pr);				//����ת
					cout << "��������ʼ���" << pr->data << endl;
				}
			}
			else {								//�����ƽ�����ӷ��ţ�˫��ת
				if (d == -1) {
					RotateLR(pr);		//�������˫��ת
					cout << "����˫������ʼ���" << pr->data << endl;
				}
				else {
					RotateRL(pr);				//���Һ���˫��ת
					cout << "����˫������ʼ���" << pr->data << endl;
				}
			}
			break;								//�������ϵ���
		}
	}
	if (st.empty() == true)ptr = pr;			//���������ĸ����
	else {										//�м���������
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
	else if (x < ptr->data)return Search(x, ptr->left);	//�������м�������
	else if (x > ptr->data)return Search(x, ptr->right);//�������м�������
	else return ptr;									//�����ɹ�
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
	AVLNode<E,K>* subL = ptr;//Ҫ����ת�Ľ��
	ptr = subL->right;//ԭ��������Ů
	subL->right = ptr->left;//ptr��Ϊ�¸�ж����߸���
	ptr->left = subL;//����ת��ptrΪ�¸�
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
		l = Level(b->left, p, h + 1); // ���������в���
		if (l != 0)
			return l;
		else // ����������δ�ҵ�,�����������в���
			return Level(b->right, p, h + 1);
	}
}