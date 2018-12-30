#include<iostream>
#include<cstring>
using namespace std;

template <class Type>
class BinarySearchTree
{
	private:
	    struct BinaryNode
	    { 
			Type data;
			int time;
		    BinaryNode *left;
		    BinaryNode *right;
			BinaryNode( const Type & thedata,BinaryNode *lt, BinaryNode *rt,int t )
	    		: data( thedata ), left( lt ), right( rt ),time(t) {};
	    };
	 	BinaryNode *root;
	 	int count;
	public:
	    BinarySearchTree(BinaryNode *t = NULL) {root = t;}
	    ~BinarySearchTree(){clear(root);}
	    bool find(const Type & x) const;
	    void insert(const Type & x);
	    void remove(const Type & x);
	    void midorder()const;
	    void clear(){clear(root);root = NULL;}
	    void delleft(const Type & x);
	    void delright(const Type & x);
	    void delinterval(const Type & x,const Type & y);
	    void find_ith(const int &x);
	private:
	    void insert(const Type & x, BinaryNode * & t);
	    void remove(const Type & x, BinaryNode * & t);
	    bool find(const Type & x, BinaryNode *t) const;
	    void midorder(BinaryNode *root)const;
	    void find_ith(const int &x,BinaryNode *t);
	    void delleft(const Type &x,BinaryNode *&t);
	    void delright(const Type &x,BinaryNode *&t);
	    void delinterval(const Type &x,const Type &y,BinaryNode *&t);
	    void clear(BinaryNode *&root)
		{
			if(root==NULL)
				return; 
			if(root->left!=NULL)
				clear(root->left);
			if(root->right!=NULL)
				clear(root->right);
			delete root;
		}
}; 

template <class Type>
bool BinarySearchTree<Type>::find( const Type &x ) const
{ 
	return find(x, root); 
}

template <class Type>
bool BinarySearchTree<Type>::find( const Type & x,BinaryNode *t ) const
{
	if(t == NULL)   
		return false;
    else if(x < t->data)   
		return find(x, t->left);  
    else if(t->data < x)  
		return find(x, t->right);  
	return true;    
} 

template <class Type>
void BinarySearchTree<Type>::find_ith( const int &x )
{ 
	count=0;
	find_ith(x,root);
	if(count<x)
		cout<<"N"<<endl;
}

template <class Type>
void BinarySearchTree<Type>::find_ith( const int &x,BinaryNode *t )
{ 
	if(t==NULL)
		return;
	find_ith(x,t->left);
	for(int i=0;i<t->time;++i)
		if(++count==x)
		{
			cout<<t->data<<endl;
			return;
		}
	find_ith(x,t->right); 
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type & x)
{ 
	insert(x, root); 
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type & x, BinaryNode *&t) 
{  	if( t == NULL ) 
    	t = new BinaryNode(x, NULL, NULL,1);
    else if(x < t->data)  
		insert(x, t->left);
    else if(t->data < x)  
		insert(x, t->right);
	else if(t->data==x)
		t->time++;
} 

template <class Type>
void BinarySearchTree<Type>::remove(const Type & x) 
{
  	remove(x, root);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type & x,BinaryNode * & t)
{
	if( t == NULL )  return;   
  	if( x < t->data )   remove( x, t->left );
    else if( t->data < x )  remove( x, t->right );
	else 
	{
		if(--t->time>=1)
			return;
		if( t->left != NULL && t->right != NULL ) 
		{
			BinaryNode *tmp = t->right;
	        while (tmp->left != NULL) tmp = tmp->left; 
	        t->data = tmp->data;
	        t->time = tmp->time;
	        remove( t->data, t->right );
	    }
	    else  
		{ 
			BinaryNode *oldNode = t;
	        t = ( t->left != NULL ) ? t->left : t->right;
	        delete oldNode;
	    }	
	}
} 

template <class Type>
void BinarySearchTree<Type>::midorder()const
{
	midorder(root);
	cout << endl;
} 

template <class Type>
void BinarySearchTree<Type>::midorder(BinaryNode *t)const
{
	if(t==NULL)	return;
	midorder(t->left);
	for(int i=0;i<t->time;++i)
		cout<<t->data<<" ";
	midorder(t->right);
} 

template <class Type>
void BinarySearchTree<Type>::delleft(const Type & x)
{
	delleft(x,root);
}

template <class Type>
void BinarySearchTree<Type>::delleft(const Type &x,BinaryNode *&t)
{
	if(t==NULL)
		return;
	while(true)
	{
		if(t==NULL)
			return;
		if(t->data>=x)
			break;
		else
			remove(t->data,t);
	}
	if(t->data>=x)
		delleft(x,t->left);
}

template <class Type>
void BinarySearchTree<Type>::delright(const Type & x)
{
	delright(x,root);
}

template <class Type>
void BinarySearchTree<Type>::delright(const Type &x,BinaryNode *&t)
{
	if(t==NULL)
		return;
	while(true)
	{
		if(t==NULL)
			return;
		if(t->data<=x)
			break;
		else
			remove(t->data,t);
	}
	if(t->data<=x)
		delright(x,t->right);
}

template <class Type>
void BinarySearchTree<Type>::delinterval(const Type & x,const Type & y)
{
	if(y-x<=1)
		return;
	delinterval(x,y,root);
}

template <class Type>
void BinarySearchTree<Type>::delinterval(const Type & x,const Type & y,BinaryNode *&t)
{
	if(t==NULL)
		return;
	while(true)
	{
		if(t==NULL)
			return;
		if(t->data>x && t->data<y)
			remove(t->data,t);
		else
			break;
	}
		
	if(t->data<=x)
		delinterval(x,y,t->right);
	if(t->data>=y)
		delinterval(x,y,t->left);
}

int main()
{
	char command[50];
	BinarySearchTree<int> bt; 
	int n,x,y;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>command;
		if(strcmp(command,"insert")==0)
		{
			cin>>x;
			bt.insert(x);
		}
		else if(strcmp(command,"delete")==0)
		{
			cin>>x;
			bt.remove(x);
		}
		else if(strcmp(command,"delete_less_than")==0)
		{
			cin>>x;
			bt.delleft(x); 
		}
		else if(strcmp(command,"delete_greater_than")==0)
		{
			cin>>x;
			bt.delright(x);
		}
		else if(strcmp(command,"delete_interval")==0)
		{
			cin>>x>>y;
			bt.delinterval(x,y);
		}
		else if(strcmp(command,"find")==0)
		{
			cin>>x;
			if(bt.find(x))
				cout<<"Y"<<endl;
			else
				cout<<"N"<<endl;
		}
		else if(strcmp(command,"find_ith")==0)
		{
			cin>>x;
			bt.find_ith(x);
		}
	}
	return 0;
}
