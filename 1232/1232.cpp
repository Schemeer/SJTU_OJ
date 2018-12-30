#include<iostream>
using namespace std;

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

struct wall
{
	bool lu;
	bool ru;
	bool ld;
	bool rd;
	wall(bool l1=0,bool l2=0,bool l3=0,bool l4=0):lu(l1),ru(l2),ld(l3),rd(l4){};
};

void Path(DisjointSet &DJS,int start,int end,int N,wall walls[])
{
	int path[N*N],size=0,p=start,p1,stage,direction[N*N];
	bool flag=1;
	int label[N];
	for(int i=0;i<N;++i)
		label[i]=(i+1)*(i+2)/2-1;
	for(int i=0;i<N*N;++i)
		direction[i]=0;
	while(p!=end)
	{
		path[size]=p;
		for(int i=0;i<N;++i)
			if(p<=label[i])
			{
				stage=i;
				break;
			}
		switch(direction[size])
		{
			case 0:
				{
					if(walls[p].lu)
					{
						p1 = p-stage-1;
						flag=1;
						for(int i=0;i<=size;i++)
							if(p1==path[i])
							{
								flag=0;
								break;
							}
						if(flag)
						{
							direction[size++]=1;
							p=p1;
							break;
						}
					}
				}
			case 1:
				{
					if(walls[p].ru)
					{
						p1 = p-stage;
						flag=1;
						for(int i=0;i<=size;i++)
							if(p1==path[i])
							{
								flag=0;
								break;
							}
						
						if(flag)
						{
							direction[size++]=2;
							p=p1;
							break;
						}
					}
				}
			case 2:
				{
					if(walls[p].ld)
					{
						p1 = p+stage+1;
						flag=1;
						for(int i=0;i<=size;i++)
							if(p1==path[i])
							{
								flag=0;
								break;
							}
						if(flag)
						{
							direction[size++]=3;
							p=p1;
							break;
						}
					}
				}
			case 3:
				{
					if(walls[p].rd)
					{
						p1 = p+stage+2;
						flag=1;
						for(int i=0;i<=size;i++)
							if(p1==path[i])
							{
								flag=0;
								break;
							}
						if(flag)
						{
							direction[size++]=4;
							p=p1;
							break;
						}
					}
				}
			default:
				{
					direction[size--]=0;
					p=path[size];
				}
		}
	}
	for(int i=0;i<size;++i)
		cout<<path[i]+1<<" ";
	cout<<end+1;
}

int main()
{
	int N,A,B;
	
	cin>>N>>A>>B;
	int label[N];
	for(int i=0;i<N;++i)
		label[i]=(i+1)*(i+2)/2-1;
	wall walls[(N+1)*N/2];
	DisjointSet DJS((N+1)*N/2);
	int node,stage,choice,node1,stage1;
	while(cin>>node>>choice)
	{
		node = node-1;
		for(int i=0;i<N;++i)
			if(node<=label[i])
			{
				stage=i;
				break;
			}
		switch(choice)
		{
			case 0:
				{
					node1 = node-stage-1;
					if(node1>=0)
					{
						for(int i=0;i<N;++i)
							if(node1<=label[i])
							{
								stage1=i;
								break;
							}
						if(stage-stage1==1)
						{
							DJS.Union(DJS.Find(node),DJS.Find(node1));
							walls[node].lu=1;
							walls[node1].rd=1;
							break;
						}
					}
					
				}
			case 1:
				{
					node1 = node-stage;
					if(node1>=0)
					{
						for(int i=0;i<N;++i)
							if(node1<=label[i])
							{
								stage1=i;
								break;
							}
						if(stage-stage1==1)
						{
							DJS.Union(DJS.Find(node),DJS.Find(node1));
							walls[node].ru=1;
							walls[node1].ld=1;
							break;
						}
					}
				}
			case 2:
				{
					node1 = node+stage+1;
					if(node1<(N+1)*N/2)
					{
						DJS.Union(DJS.Find(node),DJS.Find(node1));
						walls[node].ld=1;
						walls[node1].ru=1;
						break;
					}
				}
			case 3:
				{
					node1 = node+stage+2;
					if(node1<(N+1)*N/2)
					{
						DJS.Union(DJS.Find(node),DJS.Find(node1));
						walls[node].rd=1;
						walls[node1].lu=1;
						break;
					}
				}
		}
		if(DJS.Find(A-1)==DJS.Find(B-1))
		{
			Path(DJS,A-1,B-1,N,walls);
			break;
		}
	}
	
	
	return 0;
}
