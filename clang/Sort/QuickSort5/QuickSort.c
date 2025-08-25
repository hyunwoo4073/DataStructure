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
    // 1. Median-of-Three pivot 선택 (서브배열의 처음 3개)
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

/* 재귀 대신 스택 사용 */
void QuickSort(int DataSet[], int Left, int Right)
{
    if (Left >= Right) return;

    int StackSize = Right - Left + 1;     // 구간 수만큼이면 충분
    int Stack[StackSize * 2];             // (Left,Right) 쌍을 넣으므로 *2
    int Top = -1;

    // 초기 구간 push
    Stack[++Top] = Left;
    Stack[++Top] = Right;

    while (Top >= 0)
    {
        Right = Stack[Top--];
        Left  = Stack[Top--];

        int Length = Right - Left + 1;
        if (Length <= 1) continue;

        // 길이 2는 바로 정렬 (Partition은 Left+2 접근하므로 호출 금지)
        if (Length == 2) {
            if (DataSet[Left] > DataSet[Right]) Swap(&DataSet[Left], &DataSet[Right]);
            continue;
        }

        int Index = Partition(DataSet, Left, Right);

        // 작은 구간을 먼저 처리하도록 큰 구간을 먼저 push (스택 사용량 절감)
        int LeftSize  = Index - Left;     // [Left, Index-1]
        int RightSize = Right - Index;    // [Index+1, Right]

        if (LeftSize > RightSize) {
            // 왼쪽(큰) 먼저 push, 오른쪽(작은)은 나중에 pop
            if (Left < Index - 1) { Stack[++Top] = Left;        Stack[++Top] = Index - 1; }
            if (Index + 1 < Right) { Stack[++Top] = Index + 1;  Stack[++Top] = Right; }
        } else {
            if (Index + 1 < Right) { Stack[++Top] = Index + 1;  Stack[++Top] = Right; }
            if (Left < Index - 1) { Stack[++Top] = Left;        Stack[++Top] = Index - 1; }
        }
    }
}

int main(void)
{
    int DataSet[] = {6, 4, 2, 3, 1, 5, 80, 100, 0};
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
