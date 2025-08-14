#include "Point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 리턴값이
// < 0 이면, _elem1이 _elem2보다 작다.
// = 0 이면, _elem1이 _elem2와 같다.
// > 0 이면, _elem1이 _elem2보다 크다.
int ComparePoint(const void *_elem1, const void *_elem2)
{
    const Point* elem1 = (const Point *)_elem1;
    const Point* elem2 = (const Point *)_elem2;

    if (elem1->point > elem2->point)
        return 1;
    else if (elem1->point < elem2->point)
        return -1;
    else
        return 0;
}


int main(void)
{
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    qsort((void*)DataSet, Length, sizeof (Point), ComparePoint);

    int n = 14142;
    printf("14142번째 고객 id : %d, point : %.2f\n", DataSet[n-1].id, DataSet[n-1].point);


    return 0;
}