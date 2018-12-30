#include<iostream>

using namespace std;

class Heap
{
	private:
		int Maxsize;
		int Curentsize;
		int *Data;
		int count;
		void double_space();
		void buildHeap();
		void percolateDown(int);
		
	public:
		Heap(int size = 100):Maxsize(size),Curentsize(0),count(0){Data = new int[Maxsize];}
		Heap(const int items[],int size):Maxsize(size+10),Curentsize(size),count(0)
			{
				Data = new int[Maxsize];
				for(int i=0;i<size;++i)
					Data[i+1]=items[i];
				buildHeap();
			}
		~Heap(){delete []Data;}
		void enHeap(const int &);
		int deHeap();
		int get_head(){return Data[1];}
		bool is_empty(){return Curentsize==0;}
		int get_count(){return count;}	
};

void Heap::double_space()
{
	Maxsize*=2;
	int* tmp = Data;
	Data = new int[Maxsize];
	for(int i=1;i<=Curentsize;++i)
		Data[i]=tmp[i];
	delete []tmp;
}

void Heap::enHeap(const int &d)
{
	if(Curentsize==Maxsize-1)
		double_space();
	int hole = ++Curentsize;
	for(;hole>1&&Data[hole/2]>d;hole/=2)
	{
		Data[hole]=Data[hole/2];
		count+=1;
	}
	if(hole>1)
		count+=1;
	Data[hole] = d;
}

int Heap::deHeap()
{
	int data = Data[1];
	Data[1] = Data[Curentsize--];
	percolateDown(1);
	return data;
}

void Heap::percolateDown(int hole)
{
	int child,tmp = Data[hole];
	for (;hole*2<=Curentsize;hole=child)
	{
		child = hole*2;
		if(child!=Curentsize&&Data[child+1]<Data[child])
		{
			child++;
			count++;
		}
		if(hole*2!=Curentsize && child==2*hole)
			count++; 
		count++;
		if(Data[child]<tmp)
			Data[hole]=Data[child];
		else
			break;
	}
	Data[hole]=tmp;
}

void Heap::buildHeap()
{
	for(int i=Curentsize/2;i>0;i--)
		percolateDown(i);
}

void merge(int nums[],int left,int mid,int right,int &count)
{
	int i = left,j = mid,*tmp,k=0;
	tmp = new int[right-left];
	while(i<mid&&j<right)
	{
		if(nums[i]<nums[j])
			tmp[k++] = nums[i++];
		else
			tmp[k++] = nums[j++];
		count++;
	}
	while(i<mid)
		tmp[k++]=nums[i++];
		
	while(j<right)
		tmp[k++]=nums[j++];
		
	for(i = 0,j=left;i<k;)
		nums[j++]=tmp[i++];
	delete []tmp;
}

void mergesort(int nums[],int left,int right,int &count)
{
//	cout<<left<<'\t'<<right<<endl;
	if(left==right-1)
		return;
//	cout<<left<<'\t'<<right<<endl<<endl;
	int mid=(left+right)/2;
	mergesort(nums,left,mid,count);
	mergesort(nums,mid,right,count);
	merge(nums,left,mid,right,count);
}

void mergesort(int nums[],int size,int &count)
{
	mergesort(nums,0,size,count);
}

int divide(int nums[],int low,int high,int &count)
{
	int k = nums[low];
	do
	{
		while(low<high && nums[high]>k)
		{
			--high;
			count++;
		}
		if(low<high)
		{
			nums[low]=nums[high];
			low++;
			count++;
		}
		while(low<high && nums[low]<k)
		{
			++low;
			count++;
		}
		if(low<high)
		{
			nums[high]=nums[low];
			--high;
			count++;
		}
	}while(low!=high);
	nums[low]=k;
	return low;
}

void qsort(int nums[],int low,int high,int &count)
{
	if(low>=high)
		return;
	int mid = divide(nums,low,high,count);
	qsort(nums,low,mid-1,count);
	qsort(nums,mid+1,high,count);
}

void qsort(int nums[],int size,int &count)
{
	qsort(nums,0,size-1,count);
}

int main()
{
	int n,k,*nums,nums1,count=0;
	cin>>n>>k;
	switch(k)
	{
			case 1:
			{
				Heap hp(n);
				for(int i=0;i<n;++i)
				{
					cin>>nums1;
					hp.enHeap(nums1);
				}
				while(!hp.is_empty())
					hp.deHeap();
				cout<<hp.get_count();
				break;
			}
		case 2:
			{
				nums = new int[n];
				for(int i=0;i<n;++i)
					cin>>nums[i];
				mergesort(nums,n,count);
				cout<<count;
				delete []nums;
				break;
			}
		case 3:
			{
				nums = new int[n];
				for(int i=0;i<n;++i)
					cin>>nums[i];
				qsort(nums,n,count);
				cout<<count;
				delete []nums;
				break;
			}
	}
	
	
	return 0;
}
