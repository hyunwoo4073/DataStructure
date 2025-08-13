// #include <stdio.h>
// #include <stdbool.h>

// void BubbleSort(int DataSet[], int Length)
// {
//     int i = 0;
//     int j = 0;
//     int temp = 0;

//     for (i=0; i<Length-1; i++)
//     {   
//         bool swapped = false;
//         for ( j=0; j<Length-(i+1); j++)
//         {
//             if (DataSet[j] > DataSet[j+1])
//             {
//                 temp = DataSet[j+1];
//                 DataSet[j+1] = DataSet[j];
//                 DataSet[j] = temp;
//                 swapped = true;
//             }
//         }
//         if (!swapped)
//             break;
//     }
// }

// int main(void)
// {
//     int DataSet[] = {6, 4, 2, 3, 1, 5};
//     int Lenth = sizeof DataSet / sizeof DataSet[0];
//     int i = 0;

//     BubbleSort(DataSet, Lenth);

//     for (i=0; i<Lenth; i++)
//     {
//         printf("%d ", DataSet[i]);
//     }

//     printf("\n");

//     return 0;
// }

#include <stdio.h>
#include <stdbool.h>

static void print_array(const int *a, int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

/* 스왑 + (옵션)출력 */
static inline void swap_and_trace(int a[], int i, int j, int n, bool trace) {
    int t = a[i]; a[i] = a[j]; a[j] = t;
    if (trace) {
        printf("swap (%d,%d): ", i, j);
        print_array(a, n);
    }
}

void BubbleSort(int a[], int n, bool trace)
{
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j+1]) {
                swap_and_trace(a, j, j+1, n, trace);  // ← 스왑 발생 시만 출력
                swapped = true;
            }
        }
        if (!swapped) break; // 이미 정렬됨 → 조기 종료
    }
}

int main(void)
{
    int DataSet[] = {1, 2, 3, 4, 5, 6};
    int Length = sizeof DataSet / sizeof DataSet[0];

    printf("[초기] ");
    print_array(DataSet, Length);

    BubbleSort(DataSet, Length, /*trace=*/true);   // ← 필요 없으면 false로

    printf("[결과] ");
    print_array(DataSet, Length);
    return 0;
}