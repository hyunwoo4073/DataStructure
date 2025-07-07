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

    def InsertBefore(self, Current, Data):
        global Head
        NewNode = Node(Data)

        if Head == None:
            Head = NewNode
        elif Head == Current:
            NewNode.NextNode = Head
            Head = NewNode
        else:
            Prev = Head
            while Prev is not None and Prev.NextNode != Current:
                Prev = Prev.NextNode
            if Prev is not None:
                Prev.NextNode = NewNode
                NewNode.NextNode = Current

    def InsertNewHead(self, Data):
        global Head
        NewHead = Node(Data)

        if Head == None:
            Head = NewHead
        else:
            NewHead.NextNode = Head
            Head = NewHead

    def RemoveNode(self, Remove):
        global Head

        if Head is Remove:
            Head = Head.NextNode
        else:
            Current = Head
            while Current is not None and Current.NextNode is not Remove:
                Current = Current.NextNode
            if Current is not None:
                Current.NextNode = Remove.NextNode

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

print("\n데이터 삽입 후\n")
Current = ll.GetNodeAt(2)
ll.InsertAfter(Current, 3000)
ll.InsertBefore(Current, 5000)

cur = Head
while cur:
    print(cur.data)
    cur = cur.NextNode

print("Head 변경\n")
ll.InsertNewHead(5)
cur = Head
while cur:
    print(cur.data)
    cur = cur.NextNode

print("\n노드 삭제\n")
remove = ll.GetNodeAt(5)
ll.RemoveNode(remove)
cur = Head
while cur:
    print(cur.data)
    cur = cur.NextNode