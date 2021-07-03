#include "tree.h"
#include "read.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#define MAXLENGTH 128
#define BUFFERSIZE 512
#define INITIALSIZE 2
#define FIELDNUM 11
#define TRUE 1
#define FALSE 0
#define HEADER 0

// main program for map1 function

int main(int argc, char *argv[]) 
{ 
    tree_t *tree;
    // create tree
    tree = make_empty_tree();
    // store data into tree
    tree = store(tree,argv[1]);  
    // search radius and print
    read_and_search(tree,argv[2]);
    freeTree(tree);
    tree = NULL;
    return 0; 
} 