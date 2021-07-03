void *rec_search_radius(node_t *root,double point[],int depth,FILE *fp, int *comp, int *isfound);
void searchRadius(tree_t *tree,double point[],FILE *fp);
void *rec_search_tree(node_t *root,double point[],double nearest[],double *min_diff,int depth, int *comp);
void *searchkdTree(tree_t *tree,double point[],double nearest[]);