#include<iostream>
using namespace std;
struct StNode
{
		int node;
		int timespop;
		StNode(int n=0):node(n),timespop(0){};
		StNode(const StNode &s){node=s.node;timespop=s.timespop;}
};
template <class elemType>
class queue{
	public:
		virtual bool isEmpty()const=0;
		virtual void enQueue(const elemType &x)=0;
		virtual elemType deQueue()=0;
		virtual ~queue(){}
};
 
template <class elemType>
class seqQueue:public queue<elemType>{//顺序队列类
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
template <class elemType>
class stack{
	public:
		virtual bool isEmpty()const=0;//判栈空
		virtual void push(const elemType &x)=0; //进栈
		virtual elemType pop()=0;//出栈 
		virtual elemType top()const=0;//取栈顶元素
		virtual ~stack(){}//虚析构函数 
}; 
 
template <class elemType>
class seqStack:public stack<elemType>{//顺序栈类
	private:
		elemType *elem;
		int top_p;
		int maxSize;
		void doubleSpace();
	public:
		seqStack(int initSize = 10);
		~seqStack();
		bool isEmpty()const;
		void push(const elemType &x);
		elemType pop();
		elemType top()const;
};
template <class elemType>
seqStack<elemType>::seqStack(int initSize){
	elem = new elemType[initSize];
	maxSize = initSize;
	top_p = -1;
}
template <class elemType>
seqStack<elemType>::~seqStack(){
	delete [] elem;
}
template <class elemType>
bool seqStack<elemType>::isEmpty()const{
	return top_p == -1;
}
template <class elemType>
void seqStack<elemType>::push(const elemType &x){
	if(top_p == maxSize-1) doubleSpace();
	elem[++top_p] = x;
} 
template <class elemType>
elemType seqStack<elemType>::pop(){
	return elem[top_p--];
}
template <class elemType>
elemType seqStack<elemType>::top()const{
	return elem[top_p];
}
template <class elemType>
void seqStack<elemType>::doubleSpace(){
	elemType *tmp = elem;
	elem = new elemType[2*maxSize];
	for(int i=0; i<maxSize; ++i) elem[i] = tmp[i];
	maxSize *= 2;
	delete [] tmp;
}
 
class btree
{
	private:
		struct Node
		{
			int data;
			int lchil;
			int rbro;
			int parent;
			Node(){data=lchil=rbro=parent=-1;}
		};
		Node *ns;
		int size;
	public:
		btree(int s=10):size(s){ns = new Node[size];}
		~btree(){delete []ns;}
		void build_btree(int **d);
		void traverse_pre();
		void traverse_stage();
		void traverse_post();
};
void btree::build_btree(int **d)
{
	for(int i=0;i<size;++i)
	{
		
		if(d[i][0]!=0)
		{
			ns[i].lchil=d[i][0]-1;
			ns[d[i][0]-1].parent=i;
		}
		if(d[i][1]!=0)
		{
			ns[i].rbro=d[i][1]-1;
			ns[d[i][1]-1].parent=i;
		}
		ns[i].data=d[i][2];
	}
}
void btree::traverse_pre()
{
	seqStack<int> ss(size);
	int i=0;
	for(;i<size;++i)
		if(ns[i].parent==-1)
			break;
	ss.push(i);
	int p;
	while(!ss.isEmpty())
	{
		
		p=ss.pop();
		if(p==-1)
			continue;
		cout<<ns[p].data<<" ";
		ss.push(ns[p].rbro);
		ss.push(ns[p].lchil);
	}
	cout<<endl;
}
void btree::traverse_stage()
{
	seqQueue<int> queue1(size),queue2(size);

	int i=0;
	for(;i<size;++i)
		if(ns[i].parent==-1)
			break;
	queue1.enQueue(i);
	int p,q;
	while(!queue1.isEmpty())
	{
		p=queue1.deQueue();
		cout<<ns[p].data<<" ";
		if(ns[p].lchil!=-1)
			queue2.enQueue(ns[p].lchil);
			
			
		if(ns[p].rbro!=-1)
			queue1.enQueue(ns[p].rbro);
			
		else
		{
			if(!queue2.isEmpty())
			{
				q=queue2.deQueue();
				queue1.enQueue(q);
			}
		}
	}
	cout<<endl;
}
void btree::traverse_post()
{
	
	seqStack<StNode> ss(size);
	int i=0;
	for(;i<size;++i)
		if(ns[i].parent==-1)
			break;
	ss.push(StNode(i));
	StNode p;
	while(!ss.isEmpty())
	{	
		p=ss.pop();
		if(p.node==-1)
				continue;
		if(++p.timespop==2)
		{
			cout<<ns[p.node].data<<" ";
			ss.push(StNode(ns[p.node].rbro));
		}
		
		else
		{
			ss.push(p);
			ss.push(StNode(ns[p.node].lchil));
		}
			
	}
	cout<<endl;
}
int main()
{
	int n;
	cin>>n;
	int **t;
	t = new int*[n];
	for(int i=0;i<n;++i)
		t[i] = new int[3];
	for(int i=0;i<n;++i)
		cin>>t[i][0]>>t[i][1]>>t[i][2];
	btree bt(n);
	bt.build_btree(t);
	bt.traverse_pre();
	bt.traverse_post();
	bt.traverse_stage();
	for(int i=0;i<n;++i)
		delete []t[i];
	delete []t;
 
	return 0;	
}
