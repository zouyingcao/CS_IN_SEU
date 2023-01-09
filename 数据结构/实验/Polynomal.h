#ifndef POLYNOMAL_H
#define POLYNOMAL_H
#include<iostream>
using namespace std;
struct Term
{
	float coef;
	int exp;
	Term* link;
	Term(float c, int e, Term* next = NULL)
	{
		coef = c;
		exp = e;
		link = next;
	}
	Term* InsertAfter(float c, int e);
	friend ostream& operator<<(ostream&, const Term&);
};
class Polynomal {
public:
	Polynomal() {
		first = new Term(0, -1);
		first->link = first;
	 }
	Polynomal(const Polynomal&);
	~Polynomal();
	Term* getHead() const { 
		return first; 
	}
	int maxOrder() const {
		return first->link->exp;
	}
	const Polynomal& operator=(const Polynomal&);
	Polynomal operator+(const Polynomal&)const;
	Polynomal operator-(const Polynomal&)const;
	Polynomal operator*(const Polynomal&)const;
	float Evaluate(float)const;
private:
	Term* first;
	friend ostream& operator<<(ostream&, const Polynomal&);
	friend istream& operator>>(istream&, const Polynomal&);
};
Term* Term::InsertAfter(float c, int e)
{
	link = new Term(c, e, link);
	return link;
}

ostream& operator<<(ostream& out, const Term& x)
{
	if (x.coef == 0.0)return out;
	out << x.coef;
	switch (x.exp) {
	case 0:break;
	case 1:out << "X"; break;
	default:out << "X^" << x.exp; break;
	}
	return out;
}
istream& operator >> (istream& is, const Polynomal& x)
{
	Term* rear = x.getHead()->link; 
	float c; int e;
	while (1) {
		cout << "Input a term(coef,exp)(exp<0 to end):" << endl;
		is >> c >> e;
		if (e < 0)break;
		/*Term *temp= x.getHead()->link,*p=temp;
		bool b = true;
		while (temp != x.first)
		{
			p = temp;
			temp = temp->link;
			if (b == false && temp->exp < e)break;
			b = false;
		}
		p = p->InsertAfter(c, e);	*/
		rear = rear->InsertAfter(c, e);
	}
	return is;
}
ostream& operator<<(ostream& os, const Polynomal& x)
{
	if (x.maxOrder() == -1) 
	{
		os << 0 << endl; 
		return os;
	}
	Term* current = x.getHead()->link;
	bool h = true;
	while (current != x.getHead())
	{
		if (h == false && current->coef > 0.0)os << '+';
		h = false;
		os << *current;
		current = current->link;
	}
	os << endl;
	return os;
}
Polynomal::Polynomal(const Polynomal& R)
{
	first = new Term(0, -1);
	first->link = first;
	Term* destptr = first, * srcptr = R.getHead()->link;
	while (srcptr != R.getHead()) //循环链表
	{
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
}
const Polynomal& Polynomal::operator=(const Polynomal& a)
{
	first= new Term(0, -1);
	first->link = first;
	Term* destptr = first, * srcptr = a.getHead()->link;
	while (srcptr != a.getHead()) //循环链表
	{
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
	return *this;
}
Polynomal::~Polynomal()
{
	Term *current;
	while (first->link != first)
	{
		current = first->link;
		first->link = current->link;
		delete current;
	}
}
Polynomal Polynomal::operator+(const Polynomal& b) const
{
	Polynomal c;
	Term *pa = first->link, *pb = b.first->link, *pc = c.first,*p;
	float temp;
	while (pa != first && pb != b.first)
	{
		if (pa->exp == pb->exp) {
			temp = pa->coef + pb->coef;
			if (fabs(temp) > 0.001)
				pc = pc->InsertAfter(temp, pa->exp);
			pa = pa->link;
			pb = pb->link;
		}
		else if (pa->exp < pb->exp) {
			pc = pc->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;
		}
		else {
			pc = pc->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;
		}
	}
	if (pa != first) {
		p = pa;
		while (p != first) {
			pc = pc->InsertAfter(p->coef, p->exp);
			p = p->link;
		}
	}
	else {
		p = pb;
		while (p != b.first) {
			pc = pc->InsertAfter(p->coef, p->exp);
			p = p->link;
		}
	}
	return c;
}
Polynomal Polynomal::operator-(const Polynomal& b) const
{
	Polynomal p(b);
	Term* t = p.first->link;
	while(t->exp >= 0)
	{
		t->coef = 0-t->coef;
		t = t->link;
	}
	return (*this + p);
}
Polynomal Polynomal::operator*(const Polynomal& b) const
{
	Polynomal c;
	Term *pa, *pb, *pc=c.first; 
	int AL=maxOrder(), BL=b.maxOrder(), i, k, maxEp;
	if (AL != -1 || BL != -1)
	{
		maxEp = AL + BL;
		float* result = new float[maxEp + 1];
		for (i = 0; i <= maxEp; i++)
			result[i] = 0.0;
		pa = first->link;
		while (pa != first) {
			pb = b.getHead()->link;
			while (pb != b.first)
			{
				k = pa->exp + pb->exp;
				result[k] += pa->coef + pb->coef;
				pb = pb->link;
			}
			pa = pa->link;
		}
		for (i = maxEp; i >=0; i--)
			if (fabs(result[i]) > 0.001)
				pc = pc->InsertAfter(result[i], i);
		delete[]result;
	}
	pc->link = c.first;
	return c;
}
float Polynomal::Evaluate(float x)const
{
	float k = 0.0;
	Term* p = first->link;
	while (p->exp >= 0)
	{
		k += p->coef*pow(x, (float)p->exp);
		p = p->link;
	}
	return k;
}
#endif