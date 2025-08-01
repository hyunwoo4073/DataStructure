class Node:
    def __init__(self, Data):
        self.Data = Data
        self.NextNode = None

class LinkedListStack:
    def __init__(self):
        self.Top = None

    def LLS_Push(self, Data):
        NewNode = Node(Data)
        NewNode.NextNode = self.Top
        self.Top = NewNode

    def LLS_Pop(self):
        if self.Top is None:
            raise Exception("Stack Underflow")
        
        Data = self.Top.Data
        self.Top = self.Top.NextNode
        return Data

    def LLS_IsEmpty(self):
        return self.Top is None

    def LLS_GetSize(self):
        Count = 0
        Current = self.Top
        while Current is not None:
            Count += 1
            Current = Current.NextNode
        return Count

    def LLS_Top(self):
        if self.Top is None:
            return None
        return self.Top.Data

if __name__ == "__main__":
    stack = LikedListStack()

    # Push 테스트
    print("Push: 10")
    stack.LLS_Push(10)
    print("Push: 20")
    stack.LLS_Push(20)
    print("Push: 30")
    stack.LLS_Push(30)

    # Size 확인
    print("Size:", stack.LLS_GetSize())  # 3

    # Pop 테스트
    print("Pop:", stack.LLS_Pop())  # 30
    print("Pop:", stack.LLS_Pop())  # 20

    # Size 다시 확인
    print("Size after pop:", stack.LLS_GetSize())  # 1

    # Empty 체크
    print("Is empty?", stack.LLS_IsEmpty())  # False

    # 마지막 요소 Pop
    print("Pop:", stack.LLS_Pop())  # 10
    print("Is empty now?", stack.LLS_IsEmpty())  # True

    # Underflow 테스트
    try:
        stack.LLS_Pop()
    except Exception as e:
        print("Exception:", e)