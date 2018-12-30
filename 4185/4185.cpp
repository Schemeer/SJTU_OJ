#include<iostream>

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

class huftree
{
	private:
		struct node
		{
			int data;
			int parent;
			bool used;
			node(){data=parent=-1;used=0;}
		};
		node *root;
	public:
		huftree(int &n){root = new node[n];}
		~huftree(){delete []root;}
		void buildhf(int n,int *nums);
		void calcu(int &n);
};
void huftree::buildhf(int n,int *nums)
{
	Bernoulli_tree<int> bt(n);
	for(int i=0;i<n;++i)
	{
		root[i].data=nums[i];
		bt.enQueue(nums[i]);
	}
	int curent = n,n1,n2,n3,count;
	while(!bt.isEmpty())
	{
		n1 = bt.deQueue();
		n2 = bt.deQueue();
		n3 = n1+n2;
		count = 0;
		//cout<<"curent"<<curent<<endl;
		//cout<<"n1 "<<n1<<"n2 "<<n2<<endl;
		for(int i=0;i<curent;++i)
		{
			if(count==2)
				break;
			if(root[i].data==n1&&!root[i].used)
			{
				root[i].parent=curent;
				count++;
				root[i].used=1;
				//cout<<i<<'\t'<<root[i].data<<'\t'<<root[i].parent<<endl;
				continue;
			}
			if(root[i].data==n2&&!root[i].used)
			{
				root[i].parent=curent;
				count++;
				root[i].used=1;
				//cout<<i<<'\t'<<root[i].data<<'\t'<<root[i].parent<<endl;
			}
		}
		root[curent++].data=n3;
		if(!bt.isEmpty())
			bt.enQueue(n3);
	}
}
void huftree::calcu(int &n)
{
	int result = 0,length,j;
	for(int i=0;i<n;++i)
	{
		length=0;
		j=i;
		while(root[j].parent!=-1)
		{
			j = root[j].parent;
			length++;
		}
		result+=length*root[i].data;
	}
	cout<<result;
}
int main()
{
	int n,*nums,n1;
	cin>>n;
	n1 = 2*n-1;
	nums = new int [n];
	huftree ht(n1);
	for(int i=0;i<n;++i)
		cin>>nums[i];
	ht.buildhf(n,nums);
	ht.calcu(n);
	return 0;
}

