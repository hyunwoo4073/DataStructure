#include <stdio.h>
// 기준 요소 로직 개선
void Swap(int* A, int* B)
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}


int Partition(int DataSet[], int Left, int Right)
{
    // 1. Median-of-Three pivot 선택
    int a = DataSet[Left];
    int b = DataSet[Left+1];
    int c = DataSet[Left+2];

    int PivotIndex;
    if ((a <= b && b <= c) || (c <= b && b <= a))
        PivotIndex = Left + 1;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
        PivotIndex = Left;
    else
        PivotIndex = Left + 2;

    // Pivot을 Left로 이동
    Swap(&DataSet[Left], &DataSet[PivotIndex]);
    int Pivot = DataSet[Left];

    int i = Left + 1;
    int j = Right;

    while (i <= j)
    {
        while (i <= j && DataSet[i] <= Pivot) i++;
        while (i <= j && DataSet[j] >= Pivot) j--;

        if (i < j)
            Swap(&DataSet[i], &DataSet[j]);
    }

    // Pivot을 최종 위치로 이동
    Swap(&DataSet[Left], &DataSet[j]);

    return j;  // Pivot 위치 반환
}

void QuickSort(int DataSet[], int Left, int Right)
{
    if (Left < Right)
    {
        int Index = Partition(DataSet, Left, Right);

        QuickSort(DataSet, Left, Index-1);
        QuickSort(DataSet, Index+1, Right);
    }
}

int main(void)
{
    int DataSet[] = {6, 4, 2, 3, 1, 5};
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    QuickSort(DataSet, 0, Length-1);

    for (i=0; i<Length; i++)
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}