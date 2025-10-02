#include <stdio.h>
#include <stdlib.h>

void Merge(int arr[], int left, int mid, int right, int temp[]) {
    int i = left, j = mid+1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // temp -> arr 복사
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

void IterativeMergeSort(int arr[], int n) {
    int* temp = (int*)malloc(sizeof(int) * n);

    // size: 현재 병합할 블록 크기 (1, 2, 4, 8, ...)
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n-1; left += 2*size) {
            int mid = left + size - 1;
            int right = (left + 2*size - 1 < n-1) ? (left + 2*size - 1) : (n-1);

            if (mid < right)  // 병합할 두 구간이 존재하면
                Merge(arr, left, mid, right, temp);
        }
    }

    free(temp);
}

int main(void) {
    int DataSet[] = {334, 6, 4, 2, 3, 1, 5, 117, 12, 34};
    int Length = sizeof(DataSet) / sizeof(DataSet[0]);

    IterativeMergeSort(DataSet, Length);

    for (int i = 0; i < Length; i++)
        printf("%d ", DataSet[i]);
    printf("\n");

    return 0;
}
