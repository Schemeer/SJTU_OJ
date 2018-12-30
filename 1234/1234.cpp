#include<iostream>
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
	int p=x,x1;
	while(parents[p]>=0)
		p = parents[p];
		
	while(parents[x]>=0)
	{
		x1 = parents[x];
		parents[x]=p;
		x = x1;
	}
	return p;
}

class adjListGraph
{
	public:
		adjListGraph(int size,const int d[]);
		~adjListGraph();
		bool insert(int u,int v,int w);
		bool remove(int u,int v);
		bool exist(int u,int v)const;
		void kruskal()const;
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
		struct edge
		{
			int beg;
			int end;
			int w;
			bool operator<(const edge& rp)const{return w<rp.w;}
			bool operator>(const edge& rp)const{return w>rp.w;}
			edge operator=(const edge& rp)
			{
				beg = rp.beg;
				end = rp.end;
				w = rp.w;
				return *this;
			}
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

void adjListGraph::kruskal()const
{
	int edgeAccepted = 0,u,v,result =0;
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
		if(hp.is_empty())
			return;
		e = hp.deHeap();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		//cout<<e.beg<<'\t'<<u<<'\t'<<e.end<<'\t'<<v;
		if(u!=v)
		{
			edgeAccepted++;
			ds.Union(u,v);
			result+=e.w;
			//cout << '(' << e.beg+1 <<','<< e.end+1<<','<<e.w<<")\t";
		}
		//cout<<endl;
	}
	cout<<result;
}


int main()
{
	int n,m,*d,b,e,w;
	cin>>n>>m;
	d = new int[n];
	adjListGraph ALG(n,d);
	for(int i=0;i<m;++i)
	{
		cin>>b>>e>>w;
		ALG.insert(b-1,e-1,w);
	}
	ALG.kruskal();
	return 0;
} 
