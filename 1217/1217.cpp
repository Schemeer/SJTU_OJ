#include<iostream>

using namespace std;

int main()
{
	int m,n,ms,*ns,j;
	cin >> n;
	ns = new int[n+1];
	for(int i=1;i<=n;i++)
		cin>>ns[i];
	cin >> m;
	for(int i=0;i<m;++i)
	{
		cin>>ms;
		ns[0]=ms;
		for(j = n;ns[j]!=ms;j--);
		if(j!=0)
			cout << "Y" <<endl;
		else
			cout << "N" <<endl;
	}
	
}
