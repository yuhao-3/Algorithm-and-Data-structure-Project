// search.c used to implement search logic in both stage 1 and stage2
#include "tree.h"
#include "search.h"
#include "utils.h"



// search function logic are mainly adapted and used from code 
// in this website https://www.geeksforgeeks.org/k-dimensional-tree/


// recursively search and store the coordinates of the nearest point
void *rec_search_tree(node_t *root,double point[],double nearest[],double *min_diff,int depth, int *comp)
{
    
    if(root == NULL)
    {     
        return root;
    } 
       
    double distance = getDist(root->point,point);  
    
    // if distance between current node to search point 
    // is less than current minimum distance
    if(distance <= *min_diff)
    {       
        nearest[0] = root->point[0];
        nearest[1] = root->point[1];
        *min_diff = distance;

    }
    // current dimension to decide which way to go
    int cd = depth %2;
    double axis_diff = getAxisDiff(root->point,point,cd);
    
    // if current axis difference is greater than minimum difference
    if(axis_diff > (*min_diff))
    {
        (*comp)++;
        if(point[cd] < root->point[cd])
        {
            rec_search_tree(root->left,point,nearest,&*min_diff,depth + 1,&*comp);
        }
        else
        {
            rec_search_tree(root->right,point,nearest,&*min_diff,depth + 1,&*comp);            
        }
               
    }
    else
    {
        (*comp)++;
        rec_search_tree(root->left,point,nearest,&*min_diff,depth + 1,&*comp);
        rec_search_tree(root->right,point,nearest,&*min_diff,depth + 1,&*comp);
        
    }       
}



// search Kd tree recursively 
void *searchkdTree(tree_t *tree,double point[],double nearest[])
{
    int depth = 0,comp = 0;
    double min_diff = 0;
    min_diff = getDist(tree->root->point,point);   
    rec_search_tree(tree->root,point,nearest,&min_diff,depth, &comp);
    printf("%.8lf %.8lf --> %d\n",point[0],point[1],comp);
}




// recursively search to get the coordinates that within certain radius 
// same logic before while comparing radius instead of minimum distance
void *rec_search_radius(node_t *root,double point[],int depth,FILE *fp, int *comp, int *isfound)
{
    
    if(root == NULL)
    {     
        return root;
    } 
       
    double distance = getDist(root->point,point);  
    
    if(distance <= point[2]*point[2])
    {       
        
        node_t *tmp = root;
        while(tmp)
        {
            print_radius_results(tmp,point,fp);
            tmp = tmp->chain;
        }
        // if found point in radius make flag variable to true
        *isfound = 1;
    }
    int cd = depth %2;
    double axis_diff = getAxisDiff(root->point,point,cd);
    
    if(axis_diff > (point[2]*point[2]))
    {
        (*comp)++;
        if(point[cd] < root->point[cd])
        {
            rec_search_radius(root->left,point,depth + 1,fp,&*comp,&*isfound);
        }
        else
        {
            rec_search_radius(root->right,point,depth + 1,fp,&*comp,&*isfound);            
        }
               
    }
    else
    {
        (*comp)++;
        rec_search_radius(root->left,point,depth + 1,fp,&*comp,&*isfound);
        rec_search_radius(root->right,point,depth + 1,fp,&*comp,&*isfound);        
    }       
}



// search Kd tree recursively mainly use function rec_search_radius()
void searchRadius(tree_t *tree,double point[],FILE *fp)
{
    int depth = 0,comp = 0,isfound = 0;
    rec_search_radius(tree->root,point,depth,fp,&comp,&isfound);
    printf("%lf %lf %lf --> %d\n",point[0],point[1],point[2],comp);
    if(isfound == 0)
    {
        fprintf(fp,"%lf %lf %lf --> NOTFOUND",point[0],point[1],point[2]);
    }
}

