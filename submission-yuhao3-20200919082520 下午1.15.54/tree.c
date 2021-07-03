// tree.c  
// insertion function and part of search function are mainly adapted from this website
// https://www.geeksforgeeks.org/k-dimensional-tree/
// tree.c include make tree, insert tree and free tree logic
#include "utils.h"
#include "tree.h"
#include "search.h"
#include "print.h"
#include <regex.h> 

// make empty tree
tree_t *make_empty_tree()
{
    tree_t *tree;
    tree = malloc(sizeof(*tree));
    assert(tree!=NULL);
    tree->root = NULL;
    return tree;
}


// insert the data into node 
tree_t* insert(tree_t *tree, char *data[FIELDNUM],double point[]) 
{ 
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new);
    new->census_year = (char *)malloc(sizeof(char)*(strlen(data[0])+1));
    assert(new->census_year);
    new->block_id = (char *)malloc(sizeof(char)*(strlen(data[1])+1));
    assert(new->block_id);
    new->property_id = (char *)malloc(sizeof(char)*(strlen(data[2])+1));
    assert(new->property_id);
    new->base_property_id = (char *)malloc(sizeof(char)*(strlen(data[3])+1));
    assert(new->base_property_id);
    new->clue_small_area = (char *)malloc(sizeof(char)*(strlen(data[4])+1));
    assert(new->clue_small_area);
    new->trading_name = (char *)malloc(sizeof(char)*(strlen(data[5])+1));
    assert(new->trading_name);
    new->industry_code = (char *)malloc(sizeof(char)*(strlen(data[6])+1));
    assert(new->industry_code);
    new->industry_description = (char *)malloc(sizeof(char)*(strlen(data[7])+1));
    assert(new->industry_description);
    new->location = (char *)malloc(sizeof(char)*(strlen(data[10])+1));
    assert(new->location);
    strcpy(new->census_year,data[0]);
    strcpy(new->block_id,data[1]);
    strcpy(new->property_id,data[2]);
    strcpy(new->base_property_id,data[3]);
    strcpy(new->clue_small_area,data[4]);
    strcpy(new->trading_name,data[5]);
    strcpy(new->industry_code,data[6]);
    strcpy(new->industry_description,data[7]);
    strcpy(new->location,data[10]);
    
    // insert coordinate info into an double array
    for (int i=0; i<2; i++) 
    {
       new->point[i] = point[i]; 
    }
    assert(new->point);
    new->left = new->right = NULL; 
    new->chain = NULL;
    tree->root = insertRec(tree,tree->root,new, point, 0);        

    
    return tree;
} 
  
// split the data and insert the line information into tree
tree_t *split_and_insert_data(tree_t *tree, char *line_data,int num)
{
    char *ptr,*tmp,*tmp2,*attr[FIELDNUM],**broken;
    int i=0,count = 0,attr_num = 0;
    for(i=0;i<FIELDNUM;i++)
    {
        attr[i] = malloc(sizeof(char)*(MAXLENGTH+1));
        assert(attr[i]);
    } 
    
    broken =(char **)malloc(sizeof(*broken)*(INITIALSIZE));
    assert(broken);
    for(i=0;i<INITIALSIZE;i++)
    {
        broken[i] = (char *)malloc(sizeof(*broken)*(MAXLENGTH+1));
        assert(broken[i]);
    }
    
    /*split each line of data by quotation symbol and store into array*/
    ptr = strtok(line_data,"\"");
    int current_size = INITIALSIZE;
    while(ptr !=NULL)
    {
        /*realloc space to store broken part*/
        if(count == current_size)
        {
            current_size *= INITIALSIZE;
            broken = realloc(broken,current_size*(sizeof(*broken)));
            assert(broken);
        }
        // if there is enough space copy into broken array
        if(count < INITIALSIZE )
        {
            strcpy(broken[count],ptr);
            count ++;
        }
        else
        {
            
            broken[count] = malloc(sizeof(*broken)*(MAXLENGTH+1));
            assert(broken[count]);
            strcpy(broken[count],ptr);
            count ++;
        }     
        ptr = strtok(NULL,"\"|\n");
    }
    
    /*separate the broken piece by comma or fix them and  add into attribute array*/
    for(i=0;i<count-1;i++)
    {  /*if there is no broken piece inside this part*/
       if(broken[i][strlen(broken[i])-1] == ',')
       {
           tmp = (char *)malloc(sizeof(char)*(strlen(broken[i])+1)); 
           assert(tmp);
           strcpy(tmp,broken[i]);
           tmp2 = strtok(tmp,",");
           while(tmp2!=NULL)
           {
               strcpy(attr[attr_num],tmp2);
               tmp2 = strtok(NULL,",");
               attr_num ++; 
           }
           free(tmp);
      
       }
       /*if there is broken piece inside the part */
       else
       {
           strcpy(attr[attr_num],broken[i]); 
           while(broken[i][strlen(broken[i])-1] == ' ')
           {
               i++;
               strcat(attr[attr_num],"\"");
               strcat(attr[attr_num],broken[i]);
               strcat(attr[attr_num],"\"");
           }
           attr_num ++;
       }         
    }
    /*direct copy location into attribute*/ 
    for(i=0;i<count;i++)
    {
        if(broken[i][0] == '(' )
        {
            strcpy(attr[10],broken[i]);
        }
    }
   
    // get double type of coordinate
    double points[2];
    points[0] = atof(attr[8]);
    points[1] = atof(attr[9]);
    
    tree = insert(tree,attr,points);
    /*free the malloc space*/
    for(int i=0;i<FIELDNUM;i++)
    {
        free(attr[i]);
    }
    for(int i=0;i<count;i++)
    {
        free(broken[i]);
    }
    free(broken);  
    return tree;
}



// read the given dataset and store each line information into kd-Tree
tree_t *store(tree_t *tree, char *in)
{
    char *line = NULL;
    size_t lineBufferLength = BUFFERSIZE+2;
    FILE *ptr;
    ptr = fopen(in,"r");
    if (ptr == NULL) {
        perror("Error input file name !");
        exit(1);
    } 
    
    int count = 0;
    while(getline(&line, &lineBufferLength, ptr)!= EOF){
        if(count == HEADER)   
        {
            count++;
            continue;
        }
        tree= split_and_insert_data(tree,line,count);
        count++;
    }
    fclose(ptr);
    free(line);
    return tree;
} 


// freeTree fucntion mainly use Recfreetree function below
void freeTree(tree_t *tree)
{
    assert(tree!=NULL);
    RecfreeTree(tree->root);
    free(tree);
}


// recursively free the malloc space from tree allocation
void RecfreeTree(node_t *parent){
    if(! parent){
        return;
    }
    free(parent->census_year);
    free(parent->block_id);
    free(parent->property_id);
    free(parent->base_property_id);
    free(parent->clue_small_area);
    free(parent->trading_name);
    free(parent->industry_code);
    free(parent->industry_description);
    free(parent->location);
    // free chain node if there is one
    if(parent->chain)
    {
        node_t *temp = parent->chain,*prev;
        while(temp)
        {
            prev = temp;
            temp = temp->chain;
            free(prev->census_year);
            free(prev->block_id);
            free(prev->property_id);
            free(prev->base_property_id);
            free(prev->clue_small_area);
            free(prev->trading_name);
            free(prev->industry_code);
            free(prev->industry_description);
            free(prev->location);
            free(prev);
            
        }
        free(temp);
    }
    
    RecfreeTree(parent->left);
    RecfreeTree(parent->right);
    free(parent);
}



// Inserts a new node and returns root of modified tree 
// The parameter depth is used to decide axis of comparison 
node_t *insertRec(tree_t *tree,node_t *root, node_t *new, double point[], unsigned depth) 
{ 
    // Tree is empty? 
    if (root == NULL) 
    {       
       return new; 
    } 
    // Calculate current dimension (cd) of comparison 
    unsigned cd = depth % 2; 
    
    // insert duplicates into chain 
    if(arePointsSame(root->point,point))
    {
        if(!root->chain)
        {
            root->chain = new;
        }
        else
        {
            node_t *temp = root->chain;
            while(temp->chain)
            {
                temp = temp->chain;
            }
            temp->chain = new;
        }
     
    }
    else
    {
        // Compare the new point with root on current dimension 'cd' 
        // and decide the left or right subtree 
        if (point[cd] < (root->point[cd])) 
        {
            root->left  = insertRec(tree,root->left, new, point, depth + 1); 
        }
        else
        {
            root->right = insertRec(tree,root->right, new, point, depth + 1); 
        }
    }

    return root; 

} 


// find the nearest neighbor node and print correspondingly
// same logic for searching
void printRec(node_t* root, double point[],double nearest[], int depth,FILE *fp) 
{ 
    // Base cases 
    if (root == NULL) 
    {
        return; 
    } 
    if (arePointsSame(root->point, nearest)) 
    {
        node_t *tmp = root;
        // print all chain node record
        while(tmp)
        {
            print_results(tmp,point,fp);
            tmp = tmp->chain;
        }
    }
    
    int cd = depth %2;
  
    if (nearest[cd] < root->point[cd])
    {
        return printRec(root->left, point,nearest,depth + 1,fp); 
    }
    else
    {
        return printRec(root->right, point,nearest,depth + 1,fp);  
    }
} 
  

// search and print node, mainly using printRec()
void search_and_print(node_t* root, double point[],double nearest[],FILE *fp) 
{ 
    int depth = 0;
    // Pass current depth as 0 
    printRec(root, point,nearest, depth,fp);
} 