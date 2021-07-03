#include "tree.h"
#include "print.h"

// this function is used to print stage 1 result
void print_results(node_t *p,double point[], FILE *fp)
{
    fprintf(fp,"%.8lf %.8lf -->",point[0],point[1]);
    fprintf(fp," Census year: %s ||",p->census_year);
    fprintf(fp," Block ID: %s ||",p->block_id);
    fprintf(fp," Property ID: %s ||",p->property_id);
    fprintf(fp," Base property ID: %s ||",p->base_property_id);
    fprintf(fp," CLUE small area: %s ||",p->clue_small_area);
    fprintf(fp," Trading Name: %s ||",p->trading_name);
    fprintf(fp," Industry (ANZSIC4) code: %s ||",p->industry_code);   
    fprintf(fp," Industry (ANZSIC4) description: %s ||",p->industry_description); 
    fprintf(fp," x coordinate: %lf ||",p->point[0]);   
    fprintf(fp," y coordinate: %lf ||",p->point[1]);
    fprintf(fp," Location: %s || \n", p->location);        
}


// this function is used to print stage 2 results
void print_radius_results(node_t *p,double point[], FILE *fp)
{
    fprintf(fp,"%lf %lf %lf -->",point[0],point[1],point[2]);
    fprintf(fp," Census year: %s ||",p->census_year);
    fprintf(fp," Block ID: %s ||",p->block_id);
    fprintf(fp," Property ID: %s ||",p->property_id);
    fprintf(fp," Base property ID: %s ||",p->base_property_id);
    fprintf(fp," CLUE small area: %s ||",p->clue_small_area);
    fprintf(fp," Trading Name: %s ||",p->trading_name);
    fprintf(fp," Industry (ANZSIC4) code: %s ||",p->industry_code);   
    fprintf(fp," Industry (ANZSIC4) description: %s ||",p->industry_description); 
    fprintf(fp," x coordinate: %lf ||",p->point[0]);   
    fprintf(fp," y coordinate: %lf ||",p->point[1]);
    fprintf(fp," Location: %s || \n", p->location);        
}



