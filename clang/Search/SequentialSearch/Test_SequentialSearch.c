#include "SequentialSearch.h"

void Swap(int* A, int* B)
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}

Node* SLL_SequentialSearch(Node* Head, int Target)
{
    Node* Current = Head; 
    Node* Match	= NULL;

    while ( Current != NULL )
    {
        if ( Current->Data == Target )
        {
            Match = Current; 
            break;
        }
        else
            Current = Current->NextNode;
    }

    return Match;
}

Node* SLL_MoveToFront(Node** Head, int Target)
{
    Node* Current	= (*Head); 
    Node* Previous = NULL; 
    Node* Match	= NULL;

    while ( Current != NULL )
    {
        if ( Current->Data == Target )
        {
            Match = Current;
            if ( Previous != NULL )
            {
                //	자신의 앞 노드와 다음 노드를 연결
                Previous->NextNode = Current->NextNode;

                //	자신을 리스트의 가장 앞으로 옮기기
                Current->NextNode = (*Head);
                (*Head) = Current;
            }
            break;
        }
        else
        {
            Previous = Current;
            Current	= Current->NextNode;
        }
    }
    return Match;
}

Node* SLL_Transpose(Node** Head, int Target)
{
    Node* Current	= (*Head);
    Node* PPrevious	= NULL; //	이전 노드의 이전 노드
    Node* Previous	= NULL; //	이전 노드
    Node* Match	= NULL;

    while ( Current != NULL )
    {
        if ( Current->Data == Target )
        {
            Match = Current;
            if ( Previous != NULL )
            {
                if ( PPrevious != NULL ) 
                    PPrevious->NextNode = Current;
                else
                    (*Head) = Current;

                Previous->NextNode = Current->NextNode;
                Current->NextNode = Previous;
            }
            break;
        }
        else
        {
            if ( Previous != NULL ) 
                PPrevious = Previous;

            Previous = Current;
            Current	= Current->NextNode;
        }
    }
    return Match;
}

// 계수법 연결리스트
Node* SLL_FrequencyCount(Node** Head, int Target)
{
    Node* Current = (*Head);
    Node* Previous = NULL;
    Node* Match = NULL;

    // 탐색
    while (Current != NULL)
    {
        if (Current->Data == Target)
        {
            Match = Current;
            break;
        }
        Previous = Current;
        Current = Current->NextNode;
    }

    if (Match == NULL)
        return NULL;
    
    // 빈도 증가
    Match->Frequency++;

    // 현재 자리에서 분리
    if (Previous != NULL)
        Previous->NextNode = Match->NextNode;
    else
        (*Head) = Match->NextNode;

    // 재삽입 위치 탐색(빈도 내림차순, 동일 빈도는 안정적으로 뒤에 배치: >= 비교)
    Node* InsertPrev = NULL;
    Node* InsertPos = (*Head);
    while (InsertPos != NULL && InsertPos->Frequency >= Match->Frequency)
    {
        InsertPrev = InsertPos;
        InsertPos = InsertPos->NextNode;
    }

    // 재삽입
    Match->NextNode = InsertPos;
    if (InsertPrev != NULL)
        InsertPrev->NextNode = Match;
    else
        (*Head) = Match;

    return Match;
}

// 계수법 배열
int ARR_FrequencyCount(int DataSet[], int Freq[], int Length, int Target)
{
    for (int i=0; i<Length; i++)
    {
        if (DataSet[i] == Target)
        {
            Freq[i]++; // 빈도 증가
            int j = i; // Freq 내림차순 유지
            while (j > 0 && Freq[j] > Freq[j-1])
            {
                Swap(&DataSet[j], &DataSet[j-1]);
                Swap(&Freq[j], &Freq[j-1]);
                j--;
            }
            return j;
        }
    }
    return -1; // 못 찾았을 경우
}

int main( void )
{
    int   i       = 0;
    int   Count   = 10;
    Node* List    = NULL;
    Node* Current = NULL;
    Node* NewNode = NULL;
    Node* Match   = NULL;

    int   InitValue[10] = {1, 2, 6, 10, 4, 9, 5, 3, 8, 7};

    //  리스트 초기화
    for ( i = 0; i<Count; i++ )
    {
        NewNode = SLL_CreateNode(InitValue[i]);
        SLL_AppendNode(&List, NewNode);
    }

    // 순차 탐색
    printf("Simple Sequential Search...\n");
    
    Match =  SLL_SequentialSearch(List, 9);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 전진 이동법
    printf("Move To Front...\n");

    Match =  SLL_MoveToFront(&List, 4);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 전위법
    printf("Transpose...\n");

    Match =  SLL_Transpose(&List, 7);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 계수법 (Linked List) 
    printf("Frequency Count (Linked List)...\n");
    for (int k = 0; k < 5; ++k)       // 9를 여러 번 조회해 빈도 올려보기
    {
        Match = SLL_FrequencyCount(&List, 9);
        if (Match) printf("Hit 9 -> Freq=%d\n", Match->Frequency);
    }

    //계수법 (Array)
    printf("Frequency Count (Array)...\n");
    int DataSet2[10] = {1, 2, 6, 10, 4, 9, 5, 3, 8, 7};
    int Freq[10]     = {0};
    int pos = ARR_FrequencyCount(DataSet2, Freq, 10, 9);
    printf("Hit 9 -> pos=%d, Freq=%d\n", pos, Freq[pos]);
    pos = ARR_FrequencyCount(DataSet2, Freq, 10, 9);
    printf("Hit 9 -> pos=%d, Freq=%d\n", pos, Freq[pos]);

    //  모든 노드를 메모리에서 제거     
    printf("Destroying List...\n");

    for ( i = 0; i<Count; i++ )
    {
        Current = SLL_GetNodeAt(List, 0);

        if ( Current != NULL ) 
        {
            SLL_RemoveNode(&List, Current);
            SLL_DestroyNode(Current);
        }
    }

    return 0;
}