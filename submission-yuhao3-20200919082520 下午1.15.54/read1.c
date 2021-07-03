// read1.c are mainly used for read stdin and search radius in stage 2
#include "tree.h"
#include "search.h"
void read_and_search_radius(tree_t *tree,char *out)
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
    double point[STAGETWOINPUT];
    while(getline(&input,&lineBufferLength,stdin)!= EOF)
    {
        // split x-y coordinate and radius and transform into double        
        ptr = strtok(input," ");
        point[0] = atof(ptr);
        ptr = strtok(NULL," |\n");
        point[1] = atof(ptr); 
        ptr = strtok(NULL," |\n");
        point[2] = atof(ptr);
        // search the data within radius
        searchRadius(tree,point,fp); 
    }

    fclose(fp);
    free(input);
    return;          
}    