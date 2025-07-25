#include "ArrayStack.h"

int  main(void)
{
    int i = 0;
    ArrayStack* Stack = NULL;

    AS_CreateStack(&Stack, 3);

    printf("Capacity: %d, Size: %d, Top: %d\n\n",
    Stack->Capacity, AS_GetSize(Stack), AS_Top(Stack));

    AS_Push(Stack, 3);
    AS_Push(Stack, 37);
    AS_Push(Stack, 11);
    AS_Push(Stack, 12);
    AS_Push(Stack, 15);
    AS_Push(Stack, 17);
    AS_Push(Stack, 18);
    AS_Push(Stack, 19);
    AS_Push(Stack, 100);
    AS_Push(Stack, 500);
    AS_Push(Stack, 1000);

    printf("Capacity: %d, Size: %d, Top: %d\n\n",
    Stack->Capacity, AS_GetSize(Stack), AS_Top(Stack));

    AS_Pop(Stack);
    AS_Pop(Stack);
    AS_Pop(Stack);
    AS_Pop(Stack);
    
    printf("Capacity: %d, Size: %d, Top: %d\n\n",
    Stack->Capacity, AS_GetSize(Stack), AS_Top(Stack));

    int size3 = AS_GetSize(Stack);

    for (i=0; i<size3; i++)
    {
        if (AS_IsEmpty(Stack))
            break;

        printf("Popped: %d, ", AS_Pop(Stack));

        if (!AS_IsEmpty(Stack))
            printf("Current Top: %d\n", AS_Top(Stack));
        else
            printf("Stack Is Empty.\n");
    }
    
    AS_DestroyStack(Stack);

    return 0;
}