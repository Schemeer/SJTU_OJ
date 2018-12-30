#include<iostream>
#include<cstring>
using namespace std;

template<class T>
class Bernoulli_tree
{
	private:
		int currentSize;
		int maxSize;
		T *array;
		void doubleSpace();
		void buildHeap();
		void percolateDown(int);
		T getMax()const
		{
			T Max=array[1];
			for(int i=2;i<=currentSize;++i)
				Max=(Max<array[i])?array[i]:Max;
			return Max;
		}
	public:
		Bernoulli_tree();
    	Bernoulli_tree( int capacity = 100 ) 
	 	{ 
		 	array = new T[capacity];
			maxSize = capacity;   
         	currentSize = 0;
		}
    	Bernoulli_tree(const T data[],int size);
		~Bernoulli_tree() {delete [] array;}
    	bool isEmpty()const{return currentSize == 0;}
    	void enQueue(const T &x);
    	T deQueue();
    	T getHead(){return array[1];}
    	void decrease(int,const T&);
		int find(const T&); 
};
template <class T>
void Bernoulli_tree<T>::decrease(int s,const T& value)
{
	if(value==0)
		return;
	T x=array[s]-value;
	if(value>0)
	{
		for(;s>1&&x<array[s/2];s/=2)
        	array[s]=array[s/2];
  		array[s] = x;
	}
	if(value<0)
		percolateDown(s);
	
}

template <class T>
int Bernoulli_tree<T>::find(const T& value)
{
	T min=getMax();
	int location=currentSize;
	for(int i=1;i<=currentSize;i++)
	{
		if(array[i]>value)
		{
			if(array[i]==min&&i<location)
			{
				location=i;
				continue;
			}
			if(array[i]<min)
			{
				location=i;
				min=array[i];
			}
		}
	}
	return location;
}

template <class T>
void Bernoulli_tree<T>::enQueue(const T &x)
{  
	if(currentSize == maxSize - 1)  
		doubleSpace();
  	int hole = ++currentSize;
  	for(;hole>1&&x<array[hole/2];hole/=2)
        array[hole] = array[hole/2];
  	array[hole] = x;
}

template <class T>
T Bernoulli_tree<T>::deQueue()
{
	T minItem;
  	minItem = array[1];
  	array[1] = array[currentSize--];
  	percolateDown(1);
  	return minItem;
}

template <class T>
void Bernoulli_tree<T>::percolateDown(int hole)
{  
	int child;
   	T tmp = array[hole]; 
   	for(;hole*2<=currentSize;hole=child)
    { 
		child = hole*2;
        if(child+1<=currentSize&&array[child+1] <array[child])
            child++;
        if(array[child]<tmp)
			array[hole] = array[child];
        else
		    break;
       }
   array[hole] = tmp;
}

template <class T>
void Bernoulli_tree<T>::buildHeap()
{  
	for (int i = currentSize / 2;i > 0;i--)
    	percolateDown( i );
}

template <class T>
Bernoulli_tree<T>::Bernoulli_tree(const T *items, int size):maxSize(size + 10 ),currentSize(size)
{  
	array = new T[maxSize];
    for(int i = 0;i < size;i++)   
              array[i+1] = items[i];
   	buildHeap();
} 

template<class T>
void Bernoulli_tree<T>::doubleSpace()
{
	T *tmp=array;
	maxSize*=2;
	array = new T[maxSize];
	for(int i=0;i<currentSize;++i)
		array[i+1]=tmp[i+1];
	delete [] tmp;
} 

int main()
{
	int n,node,value;
	cin>>n;
	Bernoulli_tree<int> Bertree(n);
	char command[10];
	for(int i=0;i<n;++i)
	{
		cin>>command;
		if(strcmp(command,"insert")==0)
		{
			cin>>value;
			Bertree.enQueue(value);
			continue;
		}
		if(strcmp(command,"decrease")==0)
		{
			cin>>node>>value;
			Bertree.decrease(node,value);
			continue;
		}
		if(strcmp(command,"find")==0)
		{
			cin>>value;
			cout<<Bertree.find(value)<<endl;
		}
	}
	return 0;
}
