#include <queue>
#include <iostream>
#include <utility>

using namespace std;

#include "TreeNode.hpp"

class AvlTree{
	
	public:
		AvlTree();
		~AvlTree();
		void DeleteTree();
		void PrintTreeInOrder();
		void PrintTreeBfs();
		void DeleteSubTree(TreeNode* root);
		int SubTreeHeight(TreeNode* node);
		int TreeHeight();
		void InsertNode(TreeNode* node);

	private:
		TreeNode* _root;
		void _printInOrder(TreeNode* node);
		void _insertNode(TreeNode* node, TreeNode* root);
		bool _rebalance(TreeNode* root);
		
		
};