#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <iostream>

//A binary tree node class
class TreeNode
{
	public:
		TreeNode();
		TreeNode(int data = 0, TreeNode* left = NULL, TreeNode* right = NULL);
		~TreeNode();
		TreeNode* right();
		TreeNode* left();
		int data();
		void setData(int data);
		void SetLeft(TreeNode* left);
		void SetRight(TreeNode* right);
	private:
		int _data;
		TreeNode* _left;
		TreeNode* _right;
};

#endif