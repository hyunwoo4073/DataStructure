class Node:
    def __init__(self, NewNode):
        self.data = NewNode
        self.NextNode = None

class LinkedList:   
    def AppendNode(self, Data):
        global Head
        NewNode = Node(Data)

        if Head == None:
            Head = NewNode
        else:
            Tail = Head
            while Tail.NextNode:
                Tail = Tail.NextNode
            
            Tail.NextNode = NewNode
    
    def InsertAfter(self, Current, Data):
        NewNode = Node(Data)
        NewNode.NextNode = Current.NextNode
        Current.NextNode = NewNode

    def GetNodeAt(self, Location):
        global Head
        Location -= 1
        Current = Head

        while Current is not None and Location >= 0:
            Current = Current.NextNode
            Location -= 1
        
        return Current

Head = None  # 전역 변수로 선언

ll = LinkedList()
ll.AppendNode(10)
ll.AppendNode(30)
ll.AppendNode(20)
ll.AppendNode(40)
ll.AppendNode(50)

# 출력
cur = Head
while cur:
    print(cur.data)
    cur = cur.NextNode

print("데이터 삽입 후")
Current = ll.GetNodeAt(2)
ll.InsertAfter(Current, 3000)

cur = Head
while cur:
    print(cur.data)
    cur = cur.NextNode

            