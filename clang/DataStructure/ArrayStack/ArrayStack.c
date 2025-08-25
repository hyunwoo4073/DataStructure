#include "ArrayStack.h"

void AS_CreateStack(ArrayStack** Stack, int Capacity)
{
    // 스택을 자유 저장소에 생성
    (*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));

    // 입력된 Capacity만큼의 노드를 자유 저장소에 생성
    (*Stack)->Nodes = (Node*)malloc(sizeof(Node)*Capacity);

    // Capacity 및 Top 초기화
    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = -1;
}

void AS_DestroyStack(ArrayStack* Stack)
{
    // 노드를 자유 저장소에서 해제
    free(Stack->Nodes);

    // 스택을 자유 저장소에서 해제
    free(Stack);
}

// 스택이 다 차면 중지
// void AS_Push(ArrayStack* Stack, ElementType Data)
// {   
//     if (AS_IsFull(Stack))
//     {
//         printf("Stack Is Full\n");
//         exit(EXIT_FAILURE);
//     }
    
//     Stack->Top++;
//     Stack->Nodes[Stack->Top].Data = Data;
// }

// 스택의 용량이 모두 소진되었을 때 현재 용량의 30%만큼 더 늘림
void AS_Push(ArrayStack* Stack, ElementType Data)
{   
    if (AS_IsFull(Stack))
    {
        int NewCapacity = Stack->Capacity + (Stack->Capacity * 3)/10;
        if (NewCapacity == Stack->Capacity)
        {
            NewCapacity = Stack->Capacity + 1;
        }

        Node *NewNodes = realloc(Stack->Nodes, NewCapacity * sizeof(Node));

        if (!NewNodes)
        {
            perror("realloc failed");
            exit(EXIT_FAILURE);
        }

        Stack->Nodes = NewNodes;
        Stack->Capacity = NewCapacity;
    }
    
    Stack->Top++;
    Stack->Nodes[Stack->Top].Data = Data;
}

ElementType AS_Pop(ArrayStack* Stack)
{
    int Position = Stack->Top--;
    ElementType val = Stack->Nodes[Position].Data;
    int NewCapacity = (Stack->Capacity * 7)/10;
    if (NewCapacity < 1) {
        NewCapacity = 1;
    }

    if (Position == NewCapacity)
    {
        Node *NewNode = realloc(Stack->Nodes, NewCapacity * sizeof(Node));

        if (NewNode)
        {
            Stack->Nodes = NewNode;
            Stack->Capacity = NewCapacity;
        }
    }

    return val;
}

ElementType AS_Top(ArrayStack* Stack)
{
    return Stack->Nodes[Stack->Top].Data;
}

int AS_GetSize(ArrayStack* Stack)
{
    return Stack->Top+1;
}

int AS_IsEmpty(ArrayStack* Stack)
{
    return (Stack->Top == -1);
}

int AS_IsFull(ArrayStack* Stack)
{   
    return (AS_GetSize(Stack) == Stack->Capacity);
}