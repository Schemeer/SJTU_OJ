#include<iostream>

using namespace std;

void qsort(int* nums,int begin,int end)
{
	if(begin >= end)
		return;
	int tmp;
	int b=begin,e=end,flag=1;
	while(flag)
	{
		while(nums[b]<=nums[e])
		{
			b++;
			if(b>=e)
			{
				flag=0;
				break;
			}
		}
		if(!flag)
			break;
		tmp=nums[b];
		nums[b]=nums[e];
		nums[e]=tmp;
		while(nums[e]>=nums[b])
		{
			e--;
			if(b>=e)
			{
				flag=0;
				break;
			}
		}
		if(!flag)
			break;
		tmp=nums[b];
		nums[b]=nums[e];
		nums[e]=tmp;
	}
	qsort(nums,begin,b-1);
	qsort(nums,b+1,end);
	
}

int main()
{
	int n,*nums;
	cin>>n;
	nums = new int[n];
	for(int i =0;i<n;++i)
		cin>>nums[i];
	qsort(nums,0,n-1);
	for(int i= 0;i<n;++i)
		cout<<nums[i]<<" ";
} 
