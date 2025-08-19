#include <stdio.h>
#include <string.h>
#include "DoublyLinkedList.h"

void InsertionSort(Node** Head)
{
    if (*Head == NULL) 
        return;

    Node* current = (*Head)->NextNode;

    while (current != NULL)
    {
        Node* next = current->NextNode;
        Node* compare = current->PrevNode;

        while (compare != NULL && compare->Data > current->Data)
        {
            compare = compare->PrevNode;
        }

        if ((compare == NULL && current->PrevNode != NULL) || 
            (compare != current->PrevNode))
        {
            // 제거
            if (current->PrevNode != NULL)
                current->PrevNode->NextNode = current->NextNode;
            if (current->NextNode != NULL)
                current->NextNode->PrevNode = current->PrevNode;

            // 삽입
            if (compare == NULL)
            {
                current->PrevNode = NULL;
                current->NextNode = *Head;
                (*Head)->PrevNode = current;
                *Head = current; // 실제 헤드 변경
            }
            else
            {
                current->NextNode = compare->NextNode;
                current->PrevNode = compare;

                if (compare->NextNode != NULL)
                    compare->NextNode->PrevNode = current;

                compare->NextNode = current;
            }
        }

        current = next;
    }
}

// 리스트 전체 출력 함수
void PrintList(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->Data);
        temp = temp->NextNode;
    }
    printf("\n");
}

void FreeList(Node* head)
{
    Node* current = head;
    while (current != NULL)
    {
        Node* next = current->NextNode;
        DLL_DestroyNode(current);
        current = next;
    }
}

int main(void)
{
    Node* head = NULL;

    int data[] = {10, 9, 2, 6, 9, 3, 111, 222, 333};
    int n = sizeof(data)/sizeof(data[0]);

    for (int i = 0; i < n; i++)
    {
        DLL_AppendNode(&head, DLL_CreateNode(data[i]));
    }

    printf("정렬 전: ");
    PrintList(head);

    InsertionSort(&head);

    printf("정렬 후: ");
    PrintList(head);

    // 메모리 해제
    FreeList(head);
    head = NULL;

    return 0;
}