#include "tree.h"
#include "search.h"

// this function is read keys from stdout in stage 1
// and do corresponding search
void read_and_search(tree_t *tree, char *out)
{
    char *ptr;
    char *input = NULL;
    size_t lineBufferLength = BUFFERSIZE+2;
    FILE *fp;
    fp = fopen(out,"w+");
    
    if (fp == NULL) {
        perror("Error output file name !");
        exit(1);
    }

    double point[STAGEONEINPUT],nearest[STAGEONEINPUT];
    while(getline(&input,&lineBufferLength,stdin)!= EOF)
    {
        // split x-y coordinate and transform into double        
        nearest[0] = tree->root->point[0];
        nearest[1] = tree->root->point[1];
        // get input data
        ptr = strtok(input," ");
        point[0] = atof(ptr);
        ptr = strtok(NULL," |\n");
        point[1] = atof(ptr); 
        // find location of the nearest neighbor
        searchkdTree(tree,point,nearest);
        // find nearest neighbor node and print
        search_and_print(tree->root,point,nearest,fp);
        
    }

    fclose(fp);
    free(input);
    return;          
}    