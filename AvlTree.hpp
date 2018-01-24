#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <queue>
#include <iostream>
#include <utility>
#include <cmath>

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
		void InsertData(int data);
		bool IsEmpty();
		int NodeCount();
		
	private:
		TreeNode* _root;
		void _printInOrder(TreeNode* node);
		void _insertNode(TreeNode* node, TreeNode* root);
		bool _rebalance(TreeNode* root);
		int _nodeCount;
};


#endif