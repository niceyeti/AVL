#include "AvlTree.hpp"

int main(int argc, char** argv)
{
	AvlTree tree();
	
	tree.InsertData(1);
	tree.InsertData(2);
	tree.InsertData(3);
	
	tree.PrintTreeBfs();
	
	return 0;
}