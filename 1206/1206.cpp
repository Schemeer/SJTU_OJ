#include<iostream>
#include<cstring>

using namespace std;

template<class T>
class Stack
{	
	private:
		T *Data;
		int Max_size;
		int Top_pin;
		void double_space();
	public:
		Stack(int size = 100){Max_size = size;Top_pin = -1;Data = new T[size];}
		~Stack(){delete [] Data;}
		void push(T);
		T pop();
		T top() const;
		bool is_empty() const;
};

template<class T>
bool Stack<T>::is_empty() const 
{
	return Top_pin==-1;
}


template<class T>
void Stack<T>::push(T d)
{
	if(Top_pin==Max_size-1)
		double_space();
	Data[++Top_pin] = d; 
} 

template<class T>
T Stack<T>::top() const
{
	if(is_empty())
		cout<<"Can't get the top item!"<<endl;
	else
		return Data[Top_pin];
} 

template<class T>
T Stack<T>::pop()
{
	if(is_empty())
		cout<<"Can't pop!"<<endl;
	else
		return Data[Top_pin--];
} 

template<class T>
void Stack<T>::double_space()
{
	Max_size*=2;
	T *tmp = Data;
	Data = new T[Max_size];
	for(int i = 0;i<Top_pin;++i)
		Data[i] = tmp[i];
	delete []tmp;
}

int main()
{
	Stack<int> s;
	bool Judge = 1;
	char a[100] = "";
	while(cin>>a)
	{
		if(strcmp(a,"begin")==0)
				s.push(0);		
		if(strcmp(a,"end")==0)
		{
			bool j = 0;
			while(!s.is_empty())
			{
				if(s.top()==2)
				{
					s.pop();
					s.pop();
				}
				if(s.top()==0)
				{
					j = 1;
					s.pop();
					break;
				}
			}
			if(!j)
			{
				Judge = 0;
				break;
			}
		}
		if(strcmp(a,"if")==0)
			s.push(1);
		if(strcmp(a,"then")==0)
		{
			if(s.top()!=1)
			{
				Judge = 0;
				break;
			}
			else
				s.push(2);
		}	
		if(strcmp(a,"else")==0)
		{
			if(s.top()!=2)
			{
				Judge = 0;
				break;
			}
			else
			{
				s.pop();
				s.pop();
			}
		}
	}
	if(!s.is_empty())
		Judge = 0;
	if(Judge)
		cout<<"Match!";
	else
		cout<<"Error!";
	return 0;
}
