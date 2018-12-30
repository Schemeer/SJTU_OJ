#include<iostream>

using namespace std;

template <class Type>
class BinarySearchTree
{
	private:
	    struct BinaryNode
	    { 
			Type data;
		    BinaryNode *left;
		    BinaryNode *right;
			BinaryNode( const Type & thedata,BinaryNode *lt, BinaryNode *rt )
	    		: data( thedata ), left( lt ), right( rt ) { }
	    };
	 	BinaryNode *root;
	public:
	    BinarySearchTree(BinaryNode *t = NULL) {root = t;}
	    ~BinarySearchTree(){clear(root);}
	    bool find(const Type & x) const;
	    void insert(const Type & x);
	    void remove(const Type & x);
	    void midorder()const;
	    void clear(){clear(root);root = NULL;}
	private:
	    void insert(const Type & x, BinaryNode * & t) const;
	    void remove(const Type & x, BinaryNode * & t) const;
	    bool find(const Type & x, BinaryNode *t) const;
	    void midorder(BinaryNode *root)const;
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
void BinarySearchTree<Type>::insert(const Type & x)
{ 
	insert(x, root); 
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type & x, BinaryNode *&t) const
{  	if( t == NULL ) 
    	t = new BinaryNode(x, NULL, NULL);
    else if(x < t->data)  
		insert(x, t->left);
    else if(t->data < x)  
		insert(x, t->right);
} 
   
template <class Type>
void BinarySearchTree<Type>::remove(const Type & x) 
{
  	remove(x, root);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type & x,BinaryNode * & t) const
{ 
	if( t == NULL )  return;   
  	if( x < t->data )   remove( x, t->left );
    else if( t->data < x )  remove( x, t->right );
	else if( t->left != NULL && t->right != NULL ) 
	{
  		BinaryNode *tmp = t->right;
        while (tmp->left != NULL) tmp = tmp->left; 
        t->data = tmp->data;
        remove( t->data, t->right );
    }
    else  
	{ 
		BinaryNode *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
 } 


template <class Type>
void BinarySearchTree<Type>::midorder()const
{
	midorder(root);
	cout << endl;
} 

template <class Type>
void BinarySearchTree<Type>::midorder(BinaryNode *root)const
{
	if(root==NULL)	return;
	midorder(root->left);
	cout<<root->data<<" ";
	midorder(root->right);
} 

int main()
{
	int n,m,nums,*nums2,k;
	char ope;
	BinarySearchTree<int> bt;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>ope;
		if(ope=='+')
		{
			cin>>m;
			for(int j = 0;j<m;++j)
			{
				cin>>nums;
				if(!bt.find(nums))
					bt.insert(nums);
			}
			bt.midorder();
		}
		if(ope=='-')
		{
			cin>>m;
			for(int j = 0;j<m;++j)
			{
				cin>>nums;
				if(bt.find(nums))
					bt.remove(nums);
			}
			bt.midorder();
		}
		if(ope=='*')
		{
			cin>>m;
			nums2 = new int[m];
			k = 0;
			for(int j = 0;j<m;++j)
			{
				cin>>nums;
				if(bt.find(nums))
					nums2[k++]=nums;
			}
			bt.clear();
			for(int j = 0;j<k;++j)
				bt.insert(nums2[j]);
			delete []nums2;
			bt.midorder();
		}
	}
	return 0;
}
