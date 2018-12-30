#include<iostream>
#include<cstring>
using namespace std;


template<class T> class list;
template<class T> ostream & operator<<(ostream&,const list<T>&);
template<class T> istream & operator>>(istream&,const list<T>&);


template<class T>
class list
{
	friend ostream& operator<<<>(ostream&,const list<T>&);
	friend istream& operator>><>(istream&,const list<T>&);
	private:
		T *data;
		int length;
	public:
		list(int l = 0):length(l){data = new T[length];for(int i = 0;i<length;++i) data[i] = 0;}
		~list(){delete []data;}
		list &operator=(const list &);
		list operator+(const list &);
		
}; 
 
template<class T>
list<T> &list<T>::operator=(const list &a)
 {
 	if(&a == this)
 		return *this;
 	delete []data;
 	length = a.length;
 	data = new T[length];
 	for(int i = 0;i<length;++i)
 		data[i] = a.data[i];
	return *this;
}

template<class T>
list<T> list<T>::operator+(const list &a)
 {
	int l;
	l = length+a.length;
 	list<T> tmp(l);
 	for(int i = 0;i<length;++i)
 		tmp.data[i] = data[i];
 	for(int i = 0;i<a.length;++i)
		tmp.data[i+length] = a.data[i];
 	return tmp;
 }
 
 
template<class T>
ostream& operator<<(ostream& os,const list<T>& a)
{
	for(int i = 0;i<a.length;++i)
		os<<a.data[i]<<" ";
	return os;
}


template<class T>
istream& operator>>(istream& is,const list<T>& a)
{
	for(int i = 0;i<a.length;++i)
		is>>a.data[i];
	return is;
}

int main()
{
	char a[10]={};
	int n = 0,m = 0;
	cin>>a;
	cin>>n>>m;
	if(strcmp("int",a)==0)
	{
		list<int> l1(n),l2(m);
		cin>>l1>>l2;
		list<int> l3;
		l3 = l1+l2;
		cout <<l3;
	}
	if(strcmp("char",a)==0)
	{
		list<char> l1(n),l2(m);
		cin>>l1>>l2;
		list<char> l3;
		l3 = l1+l2;
		cout <<l3;
	}
	if(strcmp("double",a)==0)
	{
		list<double> l1(n),l2(m);
		cin>>l1>>l2;
		list<double> l3;
		l3 = l1+l2;
		cout <<l3;
	}
	return 0;
}

