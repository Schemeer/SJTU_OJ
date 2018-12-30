#include<iostream>
#include<cstring>

using namespace std;

class LIST
{
	private:
		char *data;
		int length;
	public:
		LIST(char*);
		~LIST(){delete []data;}
		void list();
		void ins(int,char*);
		void del(int,int);
		bool valid_ins(int);
		bool valid_del(int,int);
		
		
}; 

 
LIST::LIST(char *a)
{
	length = strlen(a);
	data = new char[length+1];
	strcpy(data,a);
}

void LIST::list()
{
	cout<<data<<endl;
}

void LIST::del(int j,int num)
{
	if(valid_del(j,num))
	{
		char *tmp = data;
		length = length-num;
		data = new char[length+1];
		strcpy(data,"");
		strncpy(data,tmp,j-1);
		data[j-1]='\0';
		strcat(data,&tmp[j-1+num]);
		delete []tmp;
	}
	else
		cout<<"Error!"<<endl;
}

void LIST::ins(int j,char *a)
{
	if(valid_ins(j))
	{
		length = length+strlen(a);
		char *tmp = data;
		data = new char[length+1];
		strcpy(data,"");
		strncpy(data,tmp,j-1);
		data[j-1]='\0';
		strcat(data,a);
		strcat(data,&tmp[j-1]);
		delete []tmp;
	}
	else
		cout<<"Error!"<<endl;
}

bool LIST::valid_del(int j,int num)
{
	return (j>0 and j<=length and j+num<=length+1 and num>=0);
}

bool LIST::valid_ins(int j)
{
	return (j>0 and j<=length+1);
}

bool valid_raw1(int i,int num_line)
{
	return (i>0 and i<=num_line);
}

bool valid_raw2(int n1,int n2,int num_line)
{
	return (n1>0 and n2<=num_line and n1<=n2);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	LIST *que[100];
	int num_line = 0,col,raw1,raw2,num;
	char sentence[2001],orders[5],additional_sentence[110],space;
	cin.getline(sentence,2001);
	while(strcmp(sentence,"******") != 0)
	{
		que[num_line] = new LIST(sentence);
		num_line++;
		cin.getline(sentence,2001);
	}
	
	cin>>orders;
	while (true)
	{
		if(strcmp(orders,"ins")==0)
		{
			cin>>raw1>>col;
			cin.get(space);
			cin.getline(additional_sentence,110);
			if(valid_raw1(raw1,num_line))
				que[raw1-1]->ins(col,additional_sentence);
			else
				cout<< "Error!"<<endl;
		}
		if(strcmp(orders,"del")==0)
		{
			cin>>raw1>>col>>num;
			if(valid_raw1(raw1,num_line))
				que[raw1-1]->del(col,num);
			else
				cout<< "Error!"<<endl;
		}
		if(strcmp(orders,"list")==0)
		{
			cin>>raw1>>raw2;
			if(valid_raw2(raw1,raw2,num_line))
				for(int i = raw1-1;i<raw2;++i)
					que[i]->list();
			else
				cout<< "Error!"<<endl;
		}
		if(strcmp(orders,"quit")==0)
		{
			for(int i = 0;i<num_line;++i)
				que[i]->list();
			break;
		}
		cin>>orders;
	}
	return 0;
}
