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
#define STAGEONEINPUT 2
#define STAGETWOINPUT 3

//tree.h
typedef struct node node_t;
typedef struct tree tree_t;
struct node
{
    char *census_year;
    char *block_id;
    char *property_id;
    char *base_property_id;
    char *clue_small_area;
    char *trading_name;
    char *industry_code;
    char *industry_description;
    char *location;
    double point[2];
    node_t *left,*right;
    node_t *chain;
};

struct tree
{
    node_t *root;
};

tree_t* insert(tree_t *tree, char *data[11],double point[]);
tree_t *split_and_insert_data(tree_t *tree, char *line_data,int num);
tree_t *store(tree_t *tree, char *in);
node_t *insertRec(tree_t *tree,node_t *root, node_t *new, double point[], unsigned depth);
tree_t *make_empty_tree(); 
void RecfreeTree(node_t *parent);
void freeTree(tree_t *tree);
void printRec(node_t* root, double point[],double nearest[], int depth,FILE *fp);
void search_and_print(node_t* root, double point[],double nearest[],FILE *fp);