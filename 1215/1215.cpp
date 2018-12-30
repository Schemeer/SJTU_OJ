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
};

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
	int n,node;
	cin>>n;
	Bernoulli_tree<int> Bertree(n);
	char command[10];
	for(int i=0;i<n;++i)
	{
		cin>>command;
		if(strcmp(command,"insert")==0)
		{
			cin>>node;
			Bertree.enQueue(node);
			continue;
		}
		if(strcmp(command,"delete")==0)
		{
			Bertree.deQueue();
			continue;
		}
		cout<<Bertree.getHead()<<endl; 
	}
	return 0;
} 
