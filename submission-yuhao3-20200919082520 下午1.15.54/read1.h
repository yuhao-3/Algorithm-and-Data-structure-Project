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
void read_and_search_radius(tree_t *tree,char *out);