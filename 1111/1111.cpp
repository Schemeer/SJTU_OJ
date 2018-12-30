#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;


class TRee
{
	private:
		char *data;
		int num_of_node;
		char* pm(char*,char*);
		char* merge(char,char*,char*);
	public:
		TRee(){data = new char[1];}
		~TRee(){delete []data;}
		void build_tree_PM(char *,char*);
};

void TRee::build_tree_PM(char*p,char*m)
{
	int count = 0;
	char*tmp;
	tmp = pm(p,m);
	int len = strlen(tmp);
	delete []data;
	data = new char[len+1];
	for(int i = 1;i<=len;++i)
		data[i]=tmp[i-1];
	delete []tmp;
	for(int i = 1;i<=len&&count<strlen(p);++i)
	{
		if(data[i]=='0')
			cout<<"NULL ";
		else
		{
			count++;
			cout<<data[i]<<" "; 	
		}
	}
}

char* TRee::pm(char*p,char*m)
{
	char node=p[0];
	int len = strlen(p);
	if(len==0)
	{
		char*tmp;
		tmp = new char[1];
		tmp[0]='\0';
		return tmp;
	}
	if(len==1)
	{
		char *tmp;
		tmp = new char[2];
		tmp[0]=p[0];
		tmp[1]='\0';
		return tmp; 
	}
	if(len==2)
	{
		if(p[0]==m[0])
		{
			char*tmp;
			tmp=new char[4];
			tmp[0]=p[0];
			tmp[1]='0';
			tmp[2]=p[1];
			tmp[3]='\0';
			return tmp; 
		}
		char*tmp;
		tmp=new char[3];
		tmp[0]=p[0];
		tmp[1]=p[1];
		tmp[2]='\0';
		return tmp; 			
	}
	char *left,*right;
	char *l1,*l2,*r1,*r2,*t;
	for(int i=0;i<len;++i)
	{
		if(m[i]==node)
		{
			l1=new char[i+1];
			l2=new char[i+1];
			r1=new char[len-i];
			r2=new char[len-i];
			strncpy(l1,p+1,i);
			strncpy(l2,m,i);
			strncpy(r1,p+i+1,len-i-1);
			strncpy(r2,m+i+1,len-i-1);
			l1[i]=l2[i]=r1[len-i-1]=r2[len-i-1]='\0';
			left=pm(l1,l2);
			right=pm(r1,r2);
			t = merge(node,left,right); 
			delete []l1;
			delete []l2;
			delete []r1;
			delete []r2;
			delete []left;
			delete []right;
			return t;
		}
	}
		
}

char* TRee::merge(char node,char *l,char *r)
{
	int len1=strlen(l),len2=strlen(r),count1=0,count2=0,count=1;
	char *tmp;
	tmp = new char[1100];
	tmp[0]=node;
	int i=1;
	bool flag=1;
	while(flag)
	{
		for(int j=0;j<pow(2,i-1);++j)
		{
			if(count1<len1)
				tmp[int(pow(2,i)-1+j)]=l[count1++];
			else
				tmp[int(pow(2,i)-1+j)]='0';
			count++;
			if(count1>=len1&&count2>=len2)
			{
				flag=0;
				break;
			}
				
		}
		if(!flag)
			break;
		for(int j=0;j<pow(2,i-1);++j)
		{
			if(count2<len2)
				tmp[int(pow(2,i)-1+pow(2,i-1)+j)]=r[count2++];
			else
				tmp[int(pow(2,i)-1+pow(2,i-1)+j)]='0';
			count++;
			if(count1>=len1&&count2>=len2)
			{
				flag=0;
				break;
			}
		}
		i++;
	}
	tmp[count]='\0';
	return tmp;
}
int main()
{
	char p[27],m[27];
	cin>>p>>m;
	TRee a;
	a.build_tree_PM(p,m);
	return 0;
} 
