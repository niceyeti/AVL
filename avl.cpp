#include "AvlTree.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
	AvlTree tree;
	
	srand(time(NULL));
	
	for(int i = 0; i < 6; i++){
		tree.InsertData(rand() % 100);
	}
	
	tree.PrintPretty();
	
	cout << endl;
	tree.PrintBfs();
	
	tree.PrintPrettyRecursive();
	
	return 0;
}