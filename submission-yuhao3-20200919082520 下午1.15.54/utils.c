#include "utils.h"
// utils.c has some function used in searching inserting
// for compare points and get distance purpose


// check if two pair of coordinates are the same
int arePointsSame(double point1[], double point2[]) 
{ 
    // Compare individual pointinate values 
    for (int i = 0; i < 2; ++i) 
        if (point1[i] != point2[i]) 
            return 0; 
  
    return 1; 
} 

// return distance square between two point 
double getDist(double point1[],double point2[])
{
    return (point1[0]-point2[0])*(point1[0]-point2[0])+(point1[1]-point2[1])*(point1[1]-point2[1]);
}

// return distance of point and the axis difference of current root coordiantes
double getAxisDiff(double point1[],double point2[],int cd)
{

    return (point1[cd]-point2[cd])*(point1[cd]-point2[cd]);
}
