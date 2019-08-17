#include<iostream>
#include<stack>
#include<deque>
#include<unordered_set>
#include<queue>
using namespace std ;


class Node
{
	private:
	int value ;
	Node* left ;
	Node* right ;
	
	public:
		Node(int value)
		{
			this->value  = value ;
			left = right = NULL ;
		}
	friend class BST ;
};

class BST {
	
  private:
	Node* ROOT ;
	int nodeCount;
	
	void inorderTraversalRecursiveHelper(Node*);
	void preorderTraversalRecursiveHelper(Node*);
	void postorderTraversalRecursiveHelper(Node*);
	bool containsHelper(Node*,int);
	Node** getPointerToNodeAndParent(Node*,Node*,int);
	void pathToNode(queue<Node*>, Node*, int);
	
	
	public:
		BST()
		{
			ROOT = NULL ;
			nodeCount = 0 ;
		}
		
		/*Fundamental Operations */
		void createBST(int nums[],int N);
		void insert(int value);
		void remove(int value);
		bool  contains(int value);
		
		
		/*Recursive Traversals*/
		void inorderTraversalRecursive();
		void inorderTraversalNonRecursive();
		void preorderTraversalRecursive();
		
		/*Non Recursive Traversals*/
		void preorderTraversalNonRecursive();
		void postorderTraversalRecursive();
		void postorderTraversalNonRecursive();
		void levelWiseTraversal();
		void zigzagTraversal();
		
	/* Lowest common ancestor */
	int  LCA (int,int);
	/* Maximum path sum*/
	int maxPathSum();
};

void BST::createBST(int nums[],int N)
{
   /*
     The function takes in as input an array of integers which will be used to construct the BST
     e.g. if nums[] = { 5, 7 , 9 , 12 , 20, -1, 6 }
     BST created would be 
            5
           / \
		-1    7
			 / \
			6   9
				\
				 12
				 \
				  20 
   */
   for(int i = 0 ; i < N ; i++ )
   {
   	  if(ROOT==NULL)
   	   ROOT = new Node(nums[0]) ;
   	  else
   	  {
   	     Node* traverse = ROOT ;
		 while(1)
		 {
		    if(nums[i] < traverse->value)
			{
			   if(traverse->left==NULL)
			   {
			      traverse->left = new Node(nums[i]) ;
				  break;	
			   }	
			   else
			      traverse = traverse->left;
			}
			else
			{
			    if(traverse->right==NULL)
				{
					traverse->right = new Node(nums[i]);
					break;
				}
				else
				   traverse = traverse->right;	
			}	
		 }	
	  }
   }
   nodeCount += N ;
}

void BST::insert(int value)
{
	if(ROOT==NULL)
	{
		ROOT =  new Node(value);
		return ;
	}
	Node* traverse = ROOT;
   while(1)
   {
   	  if(value < traverse->value)
   	  {
   	  	if(traverse->left==NULL)
   	  	{
			traverse->left = new Node(value);
			break;
		}
   	  	else
   	  	   traverse = traverse->left;
	   }
	   else
	   {
	   	  if( traverse->right==NULL)
	   	  {
	   	     traverse->right = new Node(value);
			 break;
		  }
		  else
		    traverse = traverse->right;
	   }
   }
   nodeCount++;
}

void BST::inorderTraversalRecursive()
{
	inorderTraversalRecursiveHelper(ROOT);
}
void BST::inorderTraversalRecursiveHelper(Node* root)
{
	if(root!=NULL)
	{
		inorderTraversalRecursiveHelper(root->left);
		cout<<root->value<<" ";
		inorderTraversalRecursiveHelper(root->right);
	}
}
void BST::preorderTraversalRecursive()
{
	preorderTraversalRecursiveHelper(ROOT);
}
void BST::preorderTraversalRecursiveHelper(Node* root)
{
	if(root!=NULL)
	{
		cout<<root->value<<" ";
		preorderTraversalRecursiveHelper(root->left);
		preorderTraversalRecursiveHelper(root->right);
	}
}
void BST::postorderTraversalRecursive()
{
	postorderTraversalRecursiveHelper(ROOT);
}
void BST::postorderTraversalRecursiveHelper(Node* root)
{
	if(root!=NULL)
	{
		postorderTraversalRecursiveHelper(root->left);
		postorderTraversalRecursiveHelper(root->right);
		cout<<root->value<<" ";
	}
}

void BST::inorderTraversalNonRecursive()
{
	if(!ROOT) return;
	
	Node* traverse = ROOT ;
	stack<Node*> auxiliaryStack ;  //empty stack 

    auxiliaryStack.push(ROOT);

	while(!auxiliaryStack.empty())
	{
		while(traverse && traverse->left)
		{
		 auxiliaryStack.push(traverse->left);
		 traverse = traverse->left;
		}
		Node* leftMostNode = auxiliaryStack.top();
		auxiliaryStack.pop();
		cout<<leftMostNode->value<<" ";
		
		traverse = leftMostNode->right ;
		if(traverse)   auxiliaryStack.push(traverse);
    }
}

void BST::preorderTraversalNonRecursive()
{
	if(!ROOT)  return;
	
	Node* traverse = ROOT ;
	stack<Node*> auxiliaryStack ;
	
	auxiliaryStack.push(ROOT);
	
	while(!auxiliaryStack.empty())
	{ 
	   while(traverse){
	 
	      cout<<auxiliaryStack.top()->value<<" ";
		  traverse=traverse->left;
		  if(traverse)
		   auxiliaryStack.push(traverse);
	}
	   
	   Node* leftMostNode = auxiliaryStack.top();
	   auxiliaryStack.pop();
	   
	   traverse = leftMostNode->right;
	   if(traverse)  auxiliaryStack.push(traverse);
	   
	}
}

void BST::postorderTraversalNonRecursive()
{
	if(!ROOT) return;
	
	stack<Node*> auxiliaryStack;
	auxiliaryStack.push(ROOT);
	
	unordered_set<Node*> visited ;
	visited.insert(ROOT);
	
	Node* traverse = ROOT ;
	
	
	while(!auxiliaryStack.empty())
	{
		while(traverse)
		{
			traverse = traverse->left;
			if(traverse){
			 auxiliaryStack.push(traverse);
			 visited.insert(traverse);
		   }
		}
		
		Node* leftMostNode = auxiliaryStack.top();
		traverse = leftMostNode->right ;
		if(!traverse || visited.find(traverse)!=visited.end())
		 {
		  cout<<leftMostNode->value<<" ";
		  auxiliaryStack.pop();
		  traverse = NULL ;
	    }  
		else
		  {
		    auxiliaryStack.push(traverse);
		    visited.insert(traverse);
	      }
	}
	
}

void BST::levelWiseTraversal()
{
	Node* traverse;
	queue<Node*> q ;
	
	q.push(ROOT);
	while(!q.empty())
	{
		traverse = q.front();
		q.pop();
		
		if(traverse->left)
		 q.push(traverse->left);
		
		if(traverse->right)
		  q.push(traverse->right);
		  
		cout<<traverse->value<<" ";
	}
}

void BST::zigzagTraversal()
{
	if(!ROOT)  return ;
	
	deque<Node*> q1 ;
	queue<Node*> q2 ;
	
	Node* leftChild, *rightChild;

	q2.push(ROOT);
	int count = 0 ;
	while(!q1.empty()||!q2.empty())
	{
		while(!q2.empty())
		{
			q1.push_back(q2.front());
			q2.pop();
		}
		if(count%2==0)   
		
		{
			auto push_ptr = q1.end()-1;
			auto print = q1.begin();
			
			while(push_ptr >= q1.begin() && print != q1.end())
			{
				cout<<(*print)->value<<" ";
				print++;
				rightChild = (*push_ptr)->right ;
				if(rightChild)
				  q2.push(rightChild);
				leftChild = (*push_ptr)->left;
				if(leftChild)
				  q2.push(leftChild);
				push_ptr--;
			}
		}
		else
		{
			auto push_ptr = q1.end()-1;
			auto print = q1.begin();
			
			while(print!=q1.end() && push_ptr>=q1.begin())
			{
				cout<<(*print)->value<<" ";
				print++;
				leftChild = (*push_ptr)->left;
				if(leftChild)
				  q2.push(leftChild);
				rightChild = (*push_ptr)->right;
				if(rightChild)
				  q2.push(rightChild);
				push_ptr--;
			}
		}
		q1.clear();
		++count;
	}
}


bool BST::contains(int value)
{
	return containsHelper(ROOT,value);
}
bool BST::containsHelper(Node*r, int value)
{
	if(r==NULL) return false;
	else
	{
		if(value < r->value)  return containsHelper(r->left,value);
		else if (value == r->value)  return true ;
		else  return containsHelper(r->right,value);
	}
}

void BST::pathToNode(queue<Node*> path, Node* r, int node)
{
	if(r==NULL)
	  return ;
	else
	{
		path.push(r);
		if(node < r->value)
		   pathToNode(path,r->left,node);
		else if (node == r->value)
		    return;
		else
		   pathToNode(path,r->right,node);
	}
}


int BST::LCA(int node1, int node2)
{
      queue<Node*> pathToNode1 , pathToNode2;
     
	  pathToNode(pathToNode1,ROOT,node1);
      pathToNode(pathToNode2,ROOT,node2);
      Node* lca = ROOT ;
	  while(true)
	  {
	      Node* n1 = pathToNode1.front();
		  Node* n2 = pathToNode2.front();
		  
		  if(n1->value!=n2->value)
		     break;
		 
		 lca = n1 ;
		 cout<<(lca->value)<<endl;
		 pathToNode1.pop();
		 pathToNode2.pop();
	  }
	  return (lca->value);
	  
}

Node** BST::getPointerToNodeAndParent(Node*r,Node*p, int value)
{
	if(r==NULL || r->value == value )
	{
		Node** output = new Node*[2];
		output[0] = r ;
		output[1] = p ;
		return output;
	}
	else
	{
		if(value < r->value)
		 return getPointerToNodeAndParent(r->left,r,value);
		else
		 return getPointerToNodeAndParent(r->right,r,value);
	}
}

void BST::remove(int value)
{
   Node** node_and_parent = getPointerToNodeAndParent(ROOT,NULL,value);
   Node* root = node_and_parent[0];
   if(!root)  return;
   Node* parent = node_and_parent[1];
   
   if(root->left==NULL && root->right==NULL)
   {
   	  if(parent==NULL)
   	  {
   	  	 delete root;
   	     ROOT = NULL ;
		 return ;	
	  }
	  else if(parent->left==root)
	    parent->left = NULL ;
	  else
	    parent->right = NULL ;
   }
   else if (root->left != NULL && root->right==NULL )
   {
   	  if(parent==NULL)
   	  {
   	    ROOT = root->left;
		delete root ;
		return; 	
	  }
	  else if(parent->left==root)
	     parent->left = root->left;
	  else
	     parent->right = root->left;
   }
   else if(root->left==NULL && root->right!=NULL)
   {
   	  if(parent==NULL)
   	  {
   	     ROOT = root->right;
		 delete root;
		 return;	
	  }
	  else if(parent->left==root)
	    parent->left = root->right ;
	  else
	    parent->right = root->right ;
   }
   else
   {
   	 Node* father = root ;
   	 Node* r = father->right ;
   	 Node* son = r->left ;
   	 
   	 while(son!=NULL)
   	 {
   	    father = r ;
	    r = son ;
		son = son->left;	
	 }
	 
	 if(father!=root)
	 {
	    father->left = r->right;
		r->right = root->right;	
	 }
	 r->left = root->left;
	 
	 if(parent==NULL)
	  ROOT = r ;
	 else
	 {
	 	if(parent->left==root)
	 	  parent->left = r ;
	 	else
	 	  parent->right = r ;
	 }
	 root->left = root->right = NULL ;
	 delete root;
   }
}


int main()
{
	BST tree ;
	int nums[]={8 ,-1 ,-7 ,-10, 24, 10, -6, 17, 28, -3 ,21 ,-8, 27, 23, 11 ,-3, 12, -2, 7, 4};
	int N = sizeof(nums)/sizeof(nums[0]);
	tree.createBST(nums,N);
	
	/*
	          8
	        /   \
	      -1     24
	      / \    / \
	    -7   7  10  28
	    / \  /    \  /
    -10   -6 4    17 27
	   \    \    / \
	   -8   -3  11 21
	         \  \    \
	        -3  12   23
	          \
	          -2
	*/
}

