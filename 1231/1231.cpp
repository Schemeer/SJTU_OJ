#include<iostream>
#include<cmath> 
using namespace std;

template <class elemType>
class queue{
	public:
		virtual bool isEmpty()const=0;
		virtual void enQueue(const elemType &x)=0;
		virtual elemType deQueue()=0;
		virtual ~queue(){}
};

template <class elemType>
class seqQueue:public queue<elemType>{//À≥–Ú∂”¡–¿‡
	private:
		elemType *elem;
		int maxSize;
		int front,rear;
		void doubleSpace();
	public:
		seqQueue(int size = 10);
		~seqQueue();
		bool isEmpty()const;
		void enQueue(const elemType &x);
		elemType deQueue();
		elemType getHead()const; 
};
template <class elemType>
seqQueue<elemType>::seqQueue(int size){
	elem = new elemType[size];
	maxSize = size;
	front = rear = 0;
}
template <class elemType>
seqQueue<elemType>::~seqQueue(){
	delete [] elem;
}
template <class elemType>
bool seqQueue<elemType>::isEmpty()const{
	return front == rear;
}
template <class elemType>
elemType seqQueue<elemType>::deQueue(){
	front = (front+1)%maxSize;
	return elem[front];
} 
template <class elemType>
elemType seqQueue<elemType>::getHead()const{
	return elem[(front+1)%maxSize];
}
template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x){
	if((rear+1)%maxSize == front) doubleSpace();
	rear = (rear+1)%maxSize;
	elem[rear] = x;
}
template <class elemType>
void seqQueue<elemType>::doubleSpace(){
	elemType *tmp = elem;
	elem = new elemType[2*maxSize];
	for(int i = 1; i <= maxSize; ++i) elem[i] = tmp[(front+i)%maxSize];
	front = 0;
	rear = maxSize-1;
	maxSize *= 2;
	delete tmp;
}

class btree
{
	private:
		struct Node
		{
			int data;
			int lchil;
			int rchil;
			int parent;
			Node(){data=lchil=rchil=parent=-1;}
		};
		Node *ns;
		int size;
	public:
		btree(int s=10):size(s){ns = new Node[size];}
		~btree(){delete []ns;}
		void build_btree(int **d);
		void com_par(int x,int y);
		
};

void btree::com_par(int x,int y)
{
	int ps[size],count=0,cp=0;
	bool flag=0;
	for(;cp<size;++cp)
		if(ns[cp].parent==-1)
			break;
	while(x!=-1)
	{
		ps[count++]=x;
		x = ns[x].parent;
	}
	while(y!=-1)
	{
		for(int i=0;i<count;++i)
			if(y==ps[i])
			{
				cp=y;
				flag = 1;
				break;
			}
		if(flag)
			break;
		y = ns[y].parent;
	}
	cout<<cp+1<<endl;
}

void btree::build_btree(int **d)
{
	for(int i=0;i<size;++i)
	{
		
		if(d[i][0]!=0)
		{
			ns[i].lchil=d[i][0]-1;
			ns[d[i][0]-1].parent=i;
			ns[i].data=i;
		}
		if(d[i][1]!=0)
		{
			ns[i].rchil=d[i][1]-1;
			ns[d[i][1]-1].parent=i;
			ns[i].data=i;
		}
	}
}

int main()
{
	int n,x,y;
	cin>>n>>x>>y;
	int **t;
	t = new int*[n];
	for(int i=0;i<n;++i)
		t[i] = new int[2];
	for(int i=0;i<n;++i)
		cin>>t[i][0]>>t[i][1];
	btree bt(n);
	bt.build_btree(t);
	bt.com_par(x-1,y-1);
	for(int i=0;i<n;++i)
		delete []t[i];
	delete []t;

	return 0;	
}
