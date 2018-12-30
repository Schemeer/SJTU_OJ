#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	char a[10],b[10];
	strncpy(a,"abcdefghi",5);
	strncpy(b,"jklmnopqr",4);
	strcat(a,b);
	cout<<a;
	
	
	return 0;
}
