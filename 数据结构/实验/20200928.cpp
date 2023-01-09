#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
void Boolean();
void Powerset1();
int subset(char*,char*,int,int);
void Powerset();
using namespace std;
int main()
{
	//Boolean();
	//Powerset1();

	system("pause");
	return 0;
}

void Boolean()
{
	int i,j,k,n,t;
	cout<<"Input the number of Booolean variables:";
	cin>>n;
	if(n>0){
	string* boolean=new string[n];
	for(i=0;i<n;i++)
		boolean[i]="false";
	for(i=0;i<pow(2.0,n);i++)
	{
		j=i;k=1;
		while(j>0)
		{
			if(j%2==0)boolean[n-k]="false";
			if(j%2!=0)boolean[n-k]="true";
			j/=2;
			k++;
		}
		for(t=0;t<n;t++)
		{	
			cout<<boolean[t];
			if(t!=n-1)cout<<",";
		}
		cout<<";"<<endl;
	}
	}
	else cout<<"no output"<<endl;
}
void Powerset1()
{
	int n,i,t,k;
	char a;
	cout<<"Input the number of elements:";cin>>n;
	char* S=new char[n];
	if(n>0){
	cout<<"Input the elements of S(use space to separate):";
	for(i=0;i<n;i++)
	{
		cin>>a;
		S[i]=a;
	}
	cout<<"powerset(S)={";
	char* T=new char[n];
	for(t=0;t<n;t++)	
		T[t]=' ';
	for(i=0;i<pow(2.0,n);i++)
	{	
		k=0;
		k=subset(S,T,i,k);
		cout<<"(";
		for(t=0;t<n;t++)
		{	
			if(T[t]!=' '){
				cout<<T[t];
				if(t!=k-1)cout<<",";
			}
		}
		cout<<")";
		if(i!=pow(2.0,n)-1)cout<<",";
	}
	cout<<"}"<<endl;
	}
	else cout<<"no powerset"<<endl;
}
int subset(char *S,char *T,int n,int k)
{
	if(n==0)
		return k;
	else
	{
		if(n%2==0)T[k]=' ';
		else T[k]=S[k];
		k++;
		return subset(S,T,n/2,k);
	}
}