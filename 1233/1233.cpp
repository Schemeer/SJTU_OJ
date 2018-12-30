#include<iostream>
using namespace std;

struct N
{
	int length;
	int size;
	int *nodes; 
	N(int s=0):size(s),length(0){nodes = new int[size];}
	N& operator=(N n)
	{
		length = n.length;
		size = n.size;
		nodes = new int[size];
		for(int i=0;i<length;++i)
			nodes[i]=n.nodes[i];
		return *this;
	}
};

template <class elemType>
class stack{
	public:
		virtual bool isEmpty()const=0;//ÅÐÕ»¿Õ
		virtual void push(const elemType &x)=0; //½øÕ»
		virtual elemType pop()=0;//³öÕ» 
		virtual elemType top()const=0;//È¡Õ»¶¥ÔªËØ
		virtual ~stack(){}//ÐéÎö¹¹º¯Êý 
}; 

template <class elemType>
class seqStack:public stack<elemType>{//Ë³ÐòÕ»Àà
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

class adjListGraph
{
	public:
		adjListGraph(int size,const int d[]);
		~adjListGraph();
		bool insert(int u,int v,int w);
		bool remove(int u,int v);
		bool exist(int u,int v)const;
		void path(int b,int M)const;
	private:
		struct edgeNode
		{
			int end;
			int weight;
			edgeNode *next;
			edgeNode(int e,int w,edgeNode *n=NULL):end(e),weight(w),next(n){};
		};
		struct verNode
		{
			int ver;
			edgeNode *head;
			verNode(edgeNode *n=NULL):head(n){};
		};
		verNode *verList;
		int vsize;
		int edges;
};

adjListGraph::adjListGraph(int size,const int d[]):vsize(size),edges(0)
{
	verList = new verNode[vsize];
	for(int i=0;i<vsize;++i)
		verList[i].ver=d[i];
}

adjListGraph::~adjListGraph()
{
	int i;
	edgeNode *p;
	for(int i=0;i<vsize;++i)
	{
		while((p=verList[i].head)!=NULL)
		{
			verList[i].head=p->next;
			delete p;
		}
	}
	delete []verList;
}

bool adjListGraph::insert(int u,int v,int w)
{
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++edges;
	return true;
} 

bool adjListGraph::remove(int u,int v)
{
	edgeNode *p=verList[u].head,*q;
	if(p==NULL)
		return false;
	if(p->end==v)
	{
		verList[u].head=p->next;
		delete p;
		return true; 
	}	
	while(p->next!=NULL&&p->next->end!=v)
		p = p->next;
	if(p->next==NULL)
	return false;
	q = p->next;
	p->next = q->next;
	delete q;
	--edges;
	return true;
}

bool adjListGraph::exist(int u,int v)const
{
	edgeNode *p=verList[u].head;
	while(p!=NULL&&p->end!=v)
		p = p->next;
	if(p==NULL)
		return false;
	return true;
}

void adjListGraph::path(int b,int M)const
{
	int count=0;
	bool flag = 0;
	seqStack<N> ss;
	N n(M+1),m(M+1);
	edgeNode *p=verList[b].head;
	n.nodes[n.length++]=b;
	ss.push(n);
	while(!ss.isEmpty())
	{
		n = ss.pop();
		p = verList[n.nodes[n.length-1]].head;
		while(p!=NULL)
		{
			for(int i=0;i<n.length;++i)
			{
				if(p->end==n.nodes[i])
				{
					flag=1;
					break;
				}
			}
			if(flag)
			{
				flag=0;
				p = p->next;
				continue;
			}
			if(n.length==M)
			{
				count++;
				p = p->next;
				continue;
			}
			m=n;
			m.nodes[m.length++]=p->end;
			ss.push(m);
			p = p->next;
		}
		delete []n.nodes;
	}
	cout<<count;
}

int main()
{
	int n,m,start,M,b,e,*d;
	cin>>n>>m>>start>>M;
	d = new int[n];
	adjListGraph path(n,d);
	for(int i=0;i<m;++i)
	{
		cin>>b>>e;
		path.insert(b-1,e-1,1);
	}
	path.path(start-1,M);
	return 0;
}
