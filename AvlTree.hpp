#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <queue>
#include <iostream>
#include <utility>
#include <cmath>
#include <string>

using namespace std;

#include "TreeNode.hpp"

class AvlTree{
	
	public:
		AvlTree();
		~AvlTree();
		void DeleteTree();
		void PrintInOrder();
		void PrintPretty();
		void PrintBfs();
		void DeleteSubTree(TreeNode* root);
		int SubTreeHeight(TreeNode* node);
		int TreeHeight();
		void InsertNode(TreeNode* node);
		void InsertData(int data);
		bool IsEmpty();
		int NodeCount();
		void PrintPrettyRecursive();
		
	private:
		TreeNode* _root;
		void _printInOrder(TreeNode* node);
		void _insertNode(TreeNode* node, TreeNode* root);
		bool _rebalanceSubTree(TreeNode* root, TreeNode** parentRootPtr);
		void _printPretty(TreeNode* node, int nodeNum, int padSize, int curDepth, int maxDepth, int maxDataWidth);
		int _nodeCount;
};


#endif