#include<iostream>


using namespace std;

int A(int m,int n)
{
	if(m == 0)
	{
		return n+1;
	}
	if(n == 0)
	{
		return A(m-1,1);
	}
	return A(m-1,A(m,n-1));
}


int main()
{
	int m = 0,n = 0,result = 0;
	cin >> m >> n;
	result = A(m,n);
	cout << result;
	return 0;
}
