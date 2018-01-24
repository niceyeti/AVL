#include "TreeNode.hpp"

TreeNode::TreeNode()
{
	setData(0);
	SetRight(NULL);
	SetLeft(NULL);
}

TreeNode::TreeNode(int data, TreeNode* left, TreeNode* right)
{
	setData(data);
	SetRight(right);
	SetLeft(left);
}

TreeNode::~TreeNode()
{}

TreeNode* TreeNode::right()
{
	return _right;
}

TreeNode* TreeNode::left()
{
	return _left;
}

void TreeNode::SetRight(TreeNode* right)
{
	_right = right;
}

void TreeNode::SetLeft(TreeNode* left)
{
	_left = left;
}

void setData(int data)
{
	_data = data;
}

int data()
{
	return _data;
}

