#include<iostream>
#include<climits>

using namespace std;

template<class T>
class Heap
{
	private:
		int Maxsize;
		int Curentsize;
		T *Data;
		void double_space();
		void buildHeap();
		void percolateDown(int);
		
	public:
		Heap(int size = 100):Maxsize(size),Curentsize(0){Data = new T[Maxsize];}
		Heap(T items[],int size):Maxsize(size+10),Curentsize(size)
			{
				Data = new T[Maxsize];
				for(int i=0;i<size;++i)
					Data[i+1]=items[i];
				buildHeap();
			}
		~Heap(){delete []Data;}
		void enHeap(T &);
		T deHeap();
		T get_head(){return Data[1];}
		bool is_empty(){return Curentsize==0;}	
};
template<class T>
void Heap<T>::double_space()
{
	Maxsize*=2;
	T* tmp = Data;
	Data = new T[Maxsize];
	for(int i=1;i<=Curentsize;++i)
		Data[i]=tmp[i];
	delete []tmp;
}

template<class T>
void Heap<T>::enHeap(T &d)
{
	if(Curentsize==Maxsize-1)
		double_space();
	int hole = ++Curentsize;
	for(;hole>1&&Data[hole/2]>d;hole/=2)
		Data[hole]=Data[hole/2];
	Data[hole] = d;
}

template<class T>
T Heap<T>::deHeap()
{
	T data = Data[1];
	Data[1] = Data[Curentsize--];
	percolateDown(1);
	return data;
}

template<class T>
void Heap<T>::percolateDown(int hole)
{
	int child;
	T tmp = Data[hole];
	for (;hole*2<=Curentsize;hole=child)
	{
		child = hole*2;
		if(child<=Curentsize&&Data[child+1]<Data[child])
			child++;
		if(Data[child]<tmp)
			Data[hole]=Data[child];
		else
			break;
	}
	Data[hole]=tmp;
}

template<class T>
void Heap<T>::buildHeap()
{
	for(int i=Curentsize/2;i>0;i--)
		percolateDown(i);
}

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

class DisjointSet
{
	private:
		int size;
		int *parents;
	public:
		DisjointSet(int s):size(s)
		{	
			parents = new int[size];
			for(int i=0;i<size;++i)
				parents[i]=-1;
		}
		~DisjointSet(){delete []parents;}
		void Union(int root1,int root2);
		int Find(int x);
};
void DisjointSet::Union(int root1,int root2)
{
	if(root1==root2)
		return;
	if(parents[root1]<parents[root2])
	{
		parents[root1]+=parents[root2];
		parents[root2]=root1;
	}
	else
	{
		parents[root2]+=parents[root1];
		parents[root1]=root2;
	}
}
int DisjointSet::Find(int x)
{
	int p=x;
	while(parents[p]>=0)
		p = parents[p];
		
	while(parents[x]>=0)
	{
		parents[x]=p;
		x = parents[x];
	}
	return p;
}


template<class T1,class T2> 
class adjListGraph
{
	public:
		adjListGraph(int size,const T1 d[]);
		~adjListGraph();
		bool insert(int u,int v,T2 w);
		bool remove(int u,int v);
		bool exist(int u,int v)const;
		void krusakl()const;
		void dijkstra(T1 start,T1 end)const;
		void spath(T1 start,T1 end)const;
	private:
		struct edgeNode
		{
			int end;
			T2 weight;
			edgeNode *next;
			edgeNode(int e,T2 w,edgeNode *n=NULL):end(e),weight(w),next(n){};
		};
		struct verNode
		{
			T1 ver;
			edgeNode *head;
			verNode(edgeNode *n=NULL):head(n){};
		};
		struct edge
		{
			int beg;
			int end;
			T2 w;
			bool operator<(const edge& rp)const{return w<rp.w;}
			bool operator>(const edge& rp)const{return w>rp.w;}
		};
		verNode *verList;
		int vsize;
		int edges;
};
template<class T1,class T2> 
adjListGraph<T1,T2>::adjListGraph(int size,const T1 d[]):vsize(size),edges(0)
{
	verList = new verNode[vsize];
	for(int i=0;i<vsize;++i)
		verList[i].ver=d[i];
}
template<class T1,class T2> 
adjListGraph<T1,T2>::~adjListGraph()
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
template<class T1,class T2> 
bool adjListGraph<T1,T2>::insert(int u,int v,T2 w)
{
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++edges;
	return true;
} 
template<class T1,class T2> 
bool adjListGraph<T1,T2>::remove(int u,int v)
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
template<class T1,class T2> 
bool adjListGraph<T1,T2>::exist(int u,int v)const
{
	edgeNode *p=verList[u].head;
	while(p!=NULL&&p->end!=v)
		p = p->next;
	if(p==NULL)
		return false;
	return true;
}
template<class T1,class T2> 
void adjListGraph<T1,T2>::krusakl()const
{
	int edgeAccepted = 0,u,v;
	T2 result =0;
	edgeNode *p;
	edge e;
	DisjointSet ds(vsize);
	Heap<edge> hp;
	for(int i=0;i<vsize;++i)
		for(p=verList[i].head;p!=NULL;p=p->next)
		{
			e.beg = i;
			e.end = p->end;
			e.w = p->weight;
			hp.enHeap(e);
		}
	while(edgeAccepted<vsize-1)
	{
		e = hp.deHeap();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		if(u!=v)
		{
			edgeAccepted++;
			ds.Union(u,v);
			result+=e.w;
		}
	}
	cout<<result;
}
template<class T1,class T2>
void adjListGraph<T1,T2>::dijkstra(T1 start,T1 end)const
{
	T2 distance[vsize];
	bool known[vsize];
	int prev[vsize],length[vsize];
	int s,e,u;
	int min;
	edgeNode *p;
	for(int i=0;i<vsize;++i)
	{
		if(verList[i].ver==start)
		{
			known[i]=true;
			distance[i]=0;
			length[i]=0;
			s=i;
			prev[i]=i;
			continue;
		}
		if(verList[i].ver==end)
			e=i;
		known[i]=false;
		distance[i]=INT_MAX;
		length[i]=0;
	}
	for(p=verList[s].head;p!=NULL;p=p->next)
	{
		distance[p->end]=p->weight;
		prev[p->end]=s;
	}
	for(int i=1;i<vsize;i++)
	{
		min=INT_MAX;
		for(int j=0;j<vsize;++j)
		{
			if(!known[j]&&distance[j]<min)
			{
				min=distance[j];
				u=j;
			}
		}
		known[u]=true;
		length[u]=length[prev[u]]+1;
		for(p=verList[u].head;p!=NULL;p=p->next)
		{
			if(!known[p->end]&&distance[p->end]>min+p->weight)
			{
				distance[p->end]=min+p->weight;
				prev[p->end]=u;
				length[p->end]=length[u]+1;
			}
			if(!known[p->end]&&distance[p->end]==min+p->weight&&length[p->end]>0&&length[p->end]>length[u]+1)
			{
				prev[p->end]=u;
				length[p->end]=length[u]+1;
			}
		}
	}
	cout<<distance[e]<<endl;
	int path[vsize],size=0;
	for(int i=0;i<vsize;++i)
	{
		if(e==s)
		{
			path[size]=e;
			break;
		} 
		path[size++]=e;
		e = prev[e];
	}
	for(int i=size;i>=0;--i)
		cout<<path[i]+1<<" ";
}
template<class T1,class T2> 
void adjListGraph<T1,T2>::spath(T1 start,T1 end)const
{
	T2 distance[vsize];
	int prev[vsize],length[vsize];
	int s,e,u;
	edgeNode *p;
	verNode *q;
	seqQueue<int> Que(vsize);
	for(int i=0;i<vsize;++i)
	{
		if(verList[i].ver==start)
		{
			prev[i]=i;
			s=i;
			distance[i]=0;
			length[i]=0;
			continue;
		}
		if(verList[i].ver==end)
			e=i;
		distance[i]=INT_MAX;
		length[i]=0;
	}
	Que.enQueue(s);
	while(!Que.isEmpty())
	{
		u=Que.deQueue();
		for(p=verList[u].head;p!=NULL;p=p->next)
		{
			if(distance[p->end]>distance[u]+p->weight || (distance[p->end]==distance[u]+p->weight && length[p->end]>length[u]+1))
			{
				distance[p->end]=distance[u]+p->weight;
				prev[p->end]=u;
				length[p->end]=length[u]+1;
				Que.enQueue(p->end);
			}
		}
	} 
	cout<<distance[e];
	
}
int main()
{
	int n,m,start,end;
	int a,b,p;
	cin>>n>>m>>start>>end;
	int *d=new int[n];
	for(int i=0;i<n;++i)
		d[i]=i+1;
	adjListGraph<int,int> ALG(n,d);
	for(int i=0;i<m;++i)
	{
		cin>>a>>b>>p;
		ALG.insert(a-1,b-1,p);
	}
	ALG.spath(start,end);

	return 0;
} 
