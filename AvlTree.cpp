#include "AvlTree.hpp"

AvlTree::AvlTree()
{
	_root = NULL;
	_nodeCount = 0;
}

AvlTree::~AvlTree()
{
	DeleteTree();
}

void AvlTree::DeleteTree()
{
	DeleteSubTree(_root);
}

bool AvlTree::IsEmpty()
{
	return _nodeCount == 0;
}

void AvlTree::PrintInOrder()
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

void AvlTree::PrintBfs()
{
	int curDepth = 0;
	queue< pair<TreeNode*,int> > nodeQ;	 //first member of pair is node ptr, second is node's depth
	nodeQ.push( pair<TreeNode*,int>(_root,0) );
	
	while(!nodeQ.empty()){
		pair<TreeNode*,int>& nodePair = nodeQ.front();
		
		if(curDepth < nodePair.second){
			curDepth = nodePair.second;
			cout << endl;
		}
		cout << "  " << nodePair.first->data();
		
		if(nodePair.first->left()){
			nodeQ.push( pair<TreeNode*, int>( nodePair.first->left(), nodePair.second+1 ) );
		}
		if(nodePair.first->right()){
			nodeQ.push( pair<TreeNode*, int>( nodePair.first->right(), nodePair.second+1 ) );
		}
		
		//pop first in line
		nodeQ.pop();
	}
}

void AvlTree::PrintPrettyRecursive()
{
	int dataWidth = 2;
	int height = SubTreeHeight(_root);
	int lineWidth = (2 << height) * dataWidth + (2 << height) - 1;
	int padSize = (lineWidth-dataWidth)/2;
	
	cout << "\nPretty recursive, pad size: " << padSize << endl;
	_printPretty(_root, 1, padSize, 1, height+1, dataWidth);
}

void AvlTree::_printPretty(TreeNode* node, int nodeNum, int padSize, int curDepth, int maxDepth, int maxDataWidth)
{
	if(curDepth > maxDepth){
		return;
	}
	
	//print left padding
	for(int i = 0; i < padSize; i++)
		cout << " ";

	//print data, if node not null
	if(node != NULL){
		for(int i = 0; i < (maxDataWidth - to_string(node->data()).length()); i++) //pad the data
			cout << " ";
		cout << node->data();
	}
	else{
		for(int i = 0; i < maxDataWidth; i++)
			cout << " ";
	}
	
	//print trailing pad if node is (2^(d+1) - 1)th node, or one less than a power of two, counting root node as 1
	if(((nodeNum+1) & (nodeNum))  == 0){ //power of 2 check for positive integers: (x & (x-1) == 0)
		for(int i = 0; i < padSize; i++)
			cout << " ";
		cout << " pad: " << padSize <<  endl;
	}
	
	if(node != NULL){
		_printPretty(node->left(), nodeNum*2, (padSize-maxDataWidth)/2, curDepth+1, maxDepth, maxDataWidth);
		_printPretty(node->right(), nodeNum*2+1, (padSize-maxDataWidth)/2, curDepth+1, maxDepth, maxDataWidth);
	}
	else{
		_printPretty(NULL, nodeNum*2, (padSize-maxDataWidth)/2, curDepth+1, maxDepth, maxDataWidth);
		_printPretty(NULL, nodeNum*2+1, (padSize-maxDataWidth)/2, curDepth+1, maxDepth, maxDataWidth);		
	}
}

//Prints a pretty tree; this function uses a complete-tree queue-bfs representation, which will explode for tree heights greater than 32 (over height 8 wouldn't be readable anyway)
void AvlTree::PrintPretty()
{
	int curDepth, lineWidth, dataWidth, height, nodeCount, padSpaces;
	queue<TreeNode*> nodeQ;	 //first member of pair is node ptr, second is node's depth
	nodeQ.push(_root);
	height = SubTreeHeight(_root);
	dataWidth = 2;
	nodeCount = 0;
	curDepth = 0;
	lineWidth = (2 << height) * dataWidth + (2 << height) - 1;  //max number of nodes at bottom level, times data width, plus equally divided single spaces between them	
	
	cout << "lineWidth: " << lineWidth << "  height: " << height << endl;
	
	while(curDepth < height){
		TreeNode* node = nodeQ.front();
		nodeQ.pop();
		
		if((nodeCount % 2) == 0){
			cout << endl; //terminate last line
			//number of spaces between nodes at this level: spaces equally divided between node data of dataWidth size
			padSpaces = (lineWidth - ((2 << curDepth) * dataWidth)) / (2 << curDepth);
			curDepth++;
			//print first pad, which isn't associated with any node
			for(int i = 0; i < padSpaces; i++)
				cout << " ";
			
		}
		
		//print this node's data (if any, spaces if not), with padding
		if(node){
			for(int i = 0; i < dataWidth-(node->data() / 10); i++)
				cout << " ";
			cout << node->data();
		}
		else{
			for(int i = 0; i < dataWidth; i++)
				cout << " ";
		}
		//print trailing padding after this node
		for(int i = 0; i < padSpaces; i++)
			cout << " ";

		//push items onto q
		if(node){
			nodeQ.push(node->left());
			nodeQ.push(node->right());
		}
		else{
			nodeQ.push(NULL);
			nodeQ.push(NULL);
		}
		
		nodeCount++;
	}
	
	cout << endl; //output the final, buffered line
}

void AvlTree::DeleteSubTree(TreeNode* root)
{
	//base case
	if(root == NULL)
		return;
	
	//leaf node, so delete it
	if(root->right() == NULL && root->left() == NULL){
		delete root;
		_nodeCount--;
	}
	else{
		DeleteSubTree(root->left());
		DeleteSubTree(root->right());
	}
}

int AvlTree::SubTreeHeight(TreeNode* node)
{
	if(node == NULL || (node->left() == NULL && node->right() == NULL))
		return 0;
	
	return max(SubTreeHeight(node->right()), SubTreeHeight(node->left())) + 1;
}

int AvlTree::TreeHeight()
{
	return SubTreeHeight(_root);
}

void AvlTree::InsertData(int data)
{
	TreeNode* node = new TreeNode(data);
	InsertNode(node);
}

void AvlTree::InsertNode(TreeNode* node)
{
	if(_root == NULL){ //empty tree: set _root to node
		_root = node;
	}
	else{
		_insertNode(node, _root);
	}
}

int AvlTree::NodeCount()
{
	return _nodeCount;
}

/*
This implements bottom-up re-balancing: node is inserted, then tree is rebalanced up the stack of roots (parent nodes) traversed.
Inserting/rebalancing bears some time/space efficiency tradeoffs, like signal variables like node.height, etc.
It might be the case that one could prove that as long as this is the only insert function ever called on the tree, then
after the first successful Rebalance call, no further calls to rebalance need be made, since the rest of the tree was already
previously balanced up to that point. But I haven't done the proof. This is just programming exercise.

@rootParent: An easy oversight, the parent of some subtree's root is required to rebalance a tree when adjusting pointers to some imbalanced root
*/
void AvlTree::_insertNode(TreeNode* node, TreeNode* root)
{	
	if(node->data() <= root->data()){
		if(root->left()){
			//recurse left
			_insertNode(node, root->left());
			_rebalanceSubTree(root->left(), root->LeftPtrPtr()); //see header: node is inserted, then every node along insertion path is rebalanced, if needed
		}
		else{
			root->SetLeft(node);
			_nodeCount++;
		}
	}
	else{
		if(root->right()){
			//recurse right
			_insertNode(node, root->right());
			_rebalanceSubTree(root->right(), root->RightPtrPtr()); //see header: node is inserted, then every node along insertion path is rebalanced, if needed
		}
		else{
			root->SetRight(node);
			_nodeCount++;
		}
	}
}

/*Util for rebalancing from a given root of some subtree

@parentRootPtr: The parent of root is required so that its pointer to the root can be adjusted on rotations. But instead of
passing the parent node pointer itself, all that is directly needed is the address of its pointer to the child, so we don't have to check
which of its children is root. 
*/
bool AvlTree::_rebalanceSubTree(TreeNode* root, TreeNode** parentRootPtr)
{
	int rightHeight = SubTreeHeight(root->right());
	int leftHeight = SubTreeHeight(root->left());
	
	cout << "L-Height: " << leftHeight << endl;
	cout << "R-Height: " << rightHeight << endl;
	
	if(abs(rightHeight - leftHeight) > 1){    //it may be the case that as long as _rebalance is called consistently every insert, this difference is exactly 2 when rebalancing is required, no more
		//run rebalance cases
		cout << "REBALANCING FROM " << root->data() << endl;

		//left subtree is deeper
		if(leftHeight > rightHeight){
			int leftGrandchildHeight = SubTreeHeight(root->left()->left());
			int rightGrandchildHeight = SubTreeHeight(root->left()->right());
			TreeNode* leftChild = root->left();
			
			if(leftGrandchildHeight > rightGrandchildHeight){  //case 1: single rotation, left subtree and left child subtree
				*parentRootPtr = leftChild;
				root->SetLeft( leftChild->right() );
				leftChild->SetRight(root);
			}
			else{  //case 2: double rotation, left subtree, right child subtree.
				cout << "DOUBLE" << endl;
				TreeNode* innerLeft = root->left()->right();
				leftChild->SetRight(innerLeft->left());
				root->SetLeft(innerLeft->right());
				innerLeft->SetLeft(leftChild);
				innerLeft->SetRight(root);
			}
		}
		else{
			int leftGrandchildHeight = SubTreeHeight(root->right()->left());
			int rightGrandchildHeight = SubTreeHeight(root->right()->right());
			TreeNode* rightChild = root->right();

			if(rightGrandchildHeight > leftGrandchildHeight){  //case 1: single rotation, left subtree and left child subtree

				*parentRootPtr = rightChild;
				root->SetRight( rightChild->left() );
				rightChild->SetLeft(root);
			}
			else{  //case 2: double rotation, left subtree, right child subtree
				cout << "DOUBLE" << endl;
				TreeNode* innerRight = rightChild->left();
				rightChild->SetLeft(innerRight->right());
				root->SetRight(innerRight->left());
				innerRight->SetRight(rightChild);
				innerRight->SetLeft(root);
			}
		}
	}
}




