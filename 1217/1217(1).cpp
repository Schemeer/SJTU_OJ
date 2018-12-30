#include<iostream>

using namespace std;

int main()
{
	struct ha
	{
		int data;
		bool em;
		ha(int d=0,bool f=0):data(d),em(f){};
	};
	int n,m,nums1,c;
	ha h[10000];
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>nums1;
		c=0;
		while(h[(nums1+c)%10000].em) c++;
		h[(nums1+c)%10000].em=1;
		h[(nums1+c)%10000].data=nums1;
	 } 
	 cin>>m;
	 for(int i=0;i<m;++i)
	 {
	 	cin>>nums1;
	 	c=0;
	 	while(h[(nums1+c)%10000].data!=nums1&&h[(nums1+c)%10000].em) c++;
	 	if(h[(nums1+c)%10000].em)
	 		cout<<"Y"<<endl;
	 	else
	 		cout<<"N"<<endl;
	 }
}
