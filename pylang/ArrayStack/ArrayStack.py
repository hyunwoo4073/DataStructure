class Node:
    def __init__(self, Data):
        self.Data = Data

class ArrayStack:
    def __init__(self, Capacity):
        self.Capacity = Capacity
        self.Top = -1
        self.Nodes = [None] * Capacity
    
    # def AS_Push(self, Data):
    #     if self.AS_IsFull():
    #         raise Exception("Stack Overflow")
  
    #     self.Top += 1
    #     self.Nodes[self.Top] = Data

    def AS_Push(self, Data):
        if self.AS_IsFull():
            extra = int(self.Capacity * 0.3)
            if extra == 0:
                extra = 1
            self.Nodes += [None] * extra
            self.Capacity += extra
  
        self.Top += 1
        self.Nodes[self.Top] = Data
    
    # def AS_Pop(self):
    #     if self.AS_IsEmpty():
    #         raise Exception("Stack Underflow")
    #     data = self.Nodes[self.Top]
    #     self.Top -= 1
    #     return data

    def AS_Pop(self):
        if self.AS_IsEmpty():
            raise Exception("Stack Underflow")

        Val = self.Nodes[self.Top]
        self.Nodes[self.Top] = None
        self.Top -= 1

        Current_size = self.AS_GetSize()

        if Current_size == int(self.Capacity * 0.7):
            New_Capacity = Current_size
            self.Nodes = self.Nodes[:New_Capacity]
            self.Capacity = New_Capacity

        return Val

    def AS_GetSize(self):
        return self.Top + 1 

    def AS_IsEmpty(self):
        return self.Top == -1
    
    def AS_IsFull(self):
        return self.AS_GetSize() == self.Capacity

# AS = ArrayStack(4)
# AS.AS_Push(1)
# AS.AS_Push(2)
# AS.AS_Push(3)
# AS.AS_Push(4)
# AS.AS_Push(5)

# print(AS.AS_Pop())
# print(AS.AS_Pop())
# print(AS.AS_Pop())
# print(AS.AS_Pop())
# print(AS.AS_Pop())


AS = ArrayStack(15)
for i in range(15):
    AS.AS_Push(i)

print("Before pop:", AS.Capacity)  # 10

# pop 1개 하면 Top = 9 → size = 9 → pass
# ...
# pop 3개 → size = 7 → 줄어듦
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())
print(AS.AS_Pop())



print("After pop:", AS.Capacity)  # 7