#include "AvlTree.hpp"

AvlTree::AvlTree()
{}

AvlTree::~AvlTree()
{
	DeleteTree(_root);
}

void AvlTree::DeleteTree()
{
	DeleteSubTree(_root);
}

void AvlTree::PrintTreeInOrder()
{
	_printInOrder(_root);
}

void AvlTree::_printInOrder(TreeNode* node)
{
	if(node == NULL)
		return;
	
	_printInOrder(node->left());
	cout << " " << node->data();
	_printInOrder(node->right());
}

void AvlTree::PrintTreeBfs()
{
	int curDepth = 0;
	queue< pair<TreeNode*,int> > nodeQ;	 //first member of pair is node ptr, second is node's depth
	nodeQ.push( pair<TreeNode*,int>(_root,0) );
	
	while(!nodeQ.empty()){
		nodePair = nodeQ.front();
		nodeQ.pop();
		
		cout << "  " << nodePair.first->data();
		if(curDepth < nodePair.second){
			curDepth = nodePair.second;
			cout << endl;
		}
		
		if(nodePair.first->left()){
			nodeQ.push( pair<TreeNode*, int>( nodePair.first->left(), nodePair.second+1 ) );
		}
		if(nodePair.first->right()){
			nodeQ.push( pair<TreeNode*, int>( nodePair.first->right(), nodePair.second+1 ) );
		}
	}
}

void AvlTree::DeleteSubTree(TreeNode* root)
{
	//base case
	if(root == NULL)
		return;
	
	//leaf node, so delete it
	if(root->right() == NULL && root->left() == NULL){
		delete root;
	}
	else{
		DeleteSubTree(root->left());
		DeleteSubTree(root->right());
	}
}

int AvlTree::SubTreeHeight(TreeNode* node)
{
	if(node == NULL)
		return -1;
	
	return max(SubTreeHeight(node->right()) + 1, SubTreeHeight(node->left()) + 1);
}

int AvlTree::TreeHeight()
{
	return SubTreeHeight(_root);
}

void AvlTree::InsertData(int data)
{
	TreeNode * node = new TreeNode(data);
	InsertNode(node);
}

void AvlTree::InsertNode(TreeNode* node)
{
	_insertNode(node, _root);
}

/*
This implements bottom-up re-balancing: node is inserted, then tree is rebalanced up the stack of roots (parent nodes) traversed.
Inserting/rebalancing bears some time/space efficiency tradeoffs, like signal variables like node.height, etc.
It might be the case that one could prove that as long as this is the only insert function ever called on the tree, then
after the first successful Rebalance call, no further calls to rebalance need be made, since the rest of the tree was already
previously balanced up to that point. But I haven't done the proof. This is just programming exercise.
*/
void AvlTree::_insertNode(TreeNode* node, TreeNode* root)
{
	if(node->data() <= root->data()){
		if(root->left()){
			//recurse left
			InsertNode(node, root->left());
		}
		else{
			root->SetLeft(node);
		}
	}
	else{
		if(root->right()){
			//recurse right
			InsertNode(node, root->right());
		}
		else{
			root->SetRight(node);
		}
	}
	
	_rebalanceTree(root); //see header: node is inserted, then every node along insertion path is rebalanced, if needed
}

//Util for rebalancing from a given root of some subtree
bool AvlTree::_rebalance(TreeNode* root)
{
	int rightHeight = SubTreeHeight(root->right());
	int leftHeight = SubTreeHeight(root->left());
	
	if(abs(rightHeight - leftHeight) > 1){
		//run rebalance cases
		cout << "REBALANCING FROM " << root->data() << endl;
	}
}



