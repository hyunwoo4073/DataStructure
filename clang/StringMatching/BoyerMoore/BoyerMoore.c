#include "BoyerMoore.h"
#include <stdlib.h>

int print_table(int* table, int table_size)
{
    for(int i=0; i<table_size; i++)
        if (table[i] > 0)
            printf("'%C':%d, ", (char)i, table[i]);
    printf("\n");
}

int print_GoodSuffTable_table(int* table, int* PosOfBorder, char* Pattern, int table_size)
{
    for(int i=0; i<table_size; i++)
        if (table[i] > 0)
            printf("'%C':%d(%d), ", Pattern[i], table[i], PosOfBorder[i]);
    printf("\n");
}

int BoyerMoore(char* Text, int TextSize, int Start,
               char* Pattern, int PatternSize)
{
    int BadCharTable[128]; // 나쁜 문자열 테이블
    int* GoodSuffTable = (int*)calloc(PatternSize + 1, sizeof(int)); // 착한 접미부 테이블
    int* PosOfBorder = (int*)calloc(PatternSize + 1, sizeof(int)); // 접미부의 가장 넣은 경계의 시작 위치
    int i = Start;
    int j = 0;

    int Position = -1;

    BuildBCT(Pattern, PatternSize, BadCharTable);
    BuildGST(Pattern, PatternSize, PosOfBorder, GoodSuffTable);

    // print_table(BadCharTable, 128);
    // print_GoodSuffTable_table(GoodSuffTable, PosOfBorder, Pattern, PatternSize+1);

    while (i <= TextSize - PatternSize)
    {
        j = PatternSize - 1;

        while (j >= 0 && Pattern[j] == Text[i+j])
            j--;

        if (j < 0)
        {   
            // printf("Match found at i=%d\n", i); // 로깅 추가
            Position = i;
            break;
        }
        else
        {
            i+= Max(GoodSuffTable[j+1], j-BadCharTable[Text[i+j]]);
            // int shift = Max(GoodSuffTable[j+1], j - BadCharTable[(unsigned char)Text[i+j]]);
            // printf("Mismatch at i=%d, j=%d, shifting by %d\n", i, j, shift);
            // i += shift;
        }
    }

    free(PosOfBorder);
    free(GoodSuffTable);

    return Position;
}

void BuildBCT(char* Pattern, int PatternSize, int* BadCharTable)
{
    int i;
    int j;

    for (i=0; i<128; i++)
        BadCharTable[i] = -1;

    for (j=0; j<PatternSize; j++)
        BadCharTable[Pattern[j]] = j;
}

void BuildGST(char* Pattern, int PatternSize, int* PosOfBorder, int* GoodSuffTable)
{
    // Case 1
    int i = PatternSize;
    int j = PatternSize + 1;

    PosOfBorder[i] = j;

    while (i>0) // 패턴의 길이만큼 반복
    {   
        // printf("%s:%d) %s, i:%d, j:%d\n", __FUNCTION__ , __LINE__, Pattern, i,j );
        while (j<=PatternSize && Pattern[i-1] != Pattern[j-1]) // 패턴에서 경계 찾기
        {
            if (GoodSuffTable[j] == 0)
                GoodSuffTable[j] = j-i;

            j = PosOfBorder[j];
        }

        i--;
        j--;

        PosOfBorder[i] = j; // 찾아낸 경계의 시작점 저장
    }

    // Case 2
    j = PosOfBorder[0];

    for (i=0; i<=PatternSize; i++)
    {
        if (GoodSuffTable[i] == 0)
            GoodSuffTable[i] = j; // 이동 거리가 0인 항목에 대해서만 첫 '접미부의 가장 넓은 경계의 시작 위치' 입력(79행 참조)
        
        if (i == j)
            j = PosOfBorder[j];
    }
}

int Max(int A, int B)
{
    if (A > B)
        return A;
    else
        return B;
}