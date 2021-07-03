#include "tree.h"
#include "read1.h"

// main function for map2
int main(int argc, char *argv[]) 
{ 
    tree_t *tree;
    // create tree
    tree = make_empty_tree();
    // store data into tree
    tree = store(tree,argv[1]);    
    // search radius and print
    read_and_search_radius(tree,argv[2]);
    freeTree(tree);
    tree = NULL;
    return 0; 
} 