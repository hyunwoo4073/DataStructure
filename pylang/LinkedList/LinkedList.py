class Node:
    def __init__(self, NewNode):
        self.data = NewNode
        self.NextNode = None

class LinkedList:
    def __init__(self):
        self.Head = None

    def AppendNode(self, Data):
        # global Head
        NewNode = Node(Data)

        if self.Head == None:
            self.Head = NewNode
        else:
            Tail = self.Head
            while Tail.NextNode:
                Tail = Tail.NextNode
            
            Tail.NextNode = NewNode
    
    def InsertAfter(self, Current, Data):
        NewNode = Node(Data)
        NewNode.NextNode = Current.NextNode
        Current.NextNode = NewNode

    def InsertBefore(self, Current, Data):
        # global Head
        NewNode = Node(Data)

        if self.Head == None:
            self.Head = NewNode
        elif self.Head == Current:
            NewNode.NextNode = self.Head
            self.Head = NewNode
        else:
            Prev = self.Head
            while Prev is not None and Prev.NextNode != Current:
                Prev = Prev.NextNode
            if Prev is not None:
                Prev.NextNode = NewNode
                NewNode.NextNode = Current

    def InsertNewHead(self, Data):
        # global Head
        NewHead = Node(Data)

        if self.Head == None:
            self.Head = NewHead
        else:
            NewHead.NextNode = self.Head
            self.Head = NewHead

    def RemoveNode(self, Remove):
        # global Head

        if self.Head is Remove:
            self.Head = self.Head.NextNode
        else:
            Current = self.Head
            while Current is not None and Current.NextNode is not Remove:
                Current = Current.NextNode
            if Current is not None:
                Current.NextNode = Remove.NextNode

    def GetNodeAt(self, Location):
        # global Head
        Location -= 1
        Current = self.Head

        while Current is not None and Location >= 0:
            Current = Current.NextNode
            Location -= 1
        
        return Current

    def PrintList(self):
        cur = self.Head
        while cur:
            print(cur.data)
            cur = cur.NextNode

# Head = None  # 전역 변수로 선언

print("\n연결리스트 테스트\n")
ll = LinkedList()
ll.AppendNode(10)
ll.AppendNode(30)
ll.AppendNode(20)
ll.AppendNode(40)
ll.AppendNode(50)

# 출력
# cur = Head
# while cur:
#     print(cur.data)
#     cur = cur.NextNode
ll.PrintList()

print("\n데이터 삽입 후\n")
Current = ll.GetNodeAt(2)
ll.InsertAfter(Current, 3000)
ll.InsertBefore(Current, 5000)

# cur = Head
# while cur:
#     print(cur.data)
#     cur = cur.NextNode
ll.PrintList()

print("\nHead 변경\n")
ll.InsertNewHead(5)
# cur = Head
# while cur:
#     print(cur.data)
#     cur = cur.NextNode
ll.PrintList()

print("\n노드 삭제\n")
remove = ll.GetNodeAt(5)
ll.RemoveNode(remove)
# cur = Head
# while cur:
#     print(cur.data)
#     cur = cur.NextNode
ll.PrintList()