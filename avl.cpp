#include "AvlTree.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
	AvlTree tree;
	
	srand(time(NULL));
	
	for(int i = 0; i < 7; i++){
		tree.InsertData(rand() % 10);
	}
	
	tree.PrintTreeBfs();
	
	return 0;
}