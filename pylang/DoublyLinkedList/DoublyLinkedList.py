class Node:
    def __init__(self, NewNode):
        self.Data = NewNode
        self.PrevNode = None
        self.NextNode = None

class DoublyLinkedList:
    def __init__(self):
        self.Head = None
        self.Tail = None

    def AppendNode(self, Data):
        NewNode = Node(Data)

        if self.Head is None:
            self.Head = self.Tail = NewNode
        else:
            self.Tail.NextNode = NewNode
            NewNode.PrevNode = self.Tail
            self.Tail = NewNode

    def InsertAfter(self, Current, Data):
        NewNode = Node(Data)

        NewNode.NextNode = Current.NextNode
        NewNode.PrevNode = Current

        if Current.NextNode is not None:
            Current.NextNode.PrevNode = NewNode
        Current.NextNode = NewNode

        if self.Tail == Current:
            self.Tail = NewNode

    def InsertBefore(self, Current, Data):
        NewNode = Node(Data)

        if self.Head is None:
            self.Head = NewNode
            return
        
        if self.Head == Current:
            NewNode.NextNode = self.Head
            self.Head.PrevNode = NewNode
            self.Head = NewNode
            return
        
        NewNode.NextNode = Current
        NewNode.PrevNode = Current.PrevNode
        Current.PrevNode.NextNode = NewNode
        Current.PrevNode = NewNode
        

    def RemoveNode(self, Remove):
        if self.Head == Remove:
            self.Head = Remove.NextNode
            
            if self.Head:
                self.Head.PrevNode = None
        
        else:
            if Remove.PrevNode is not None:
                Remove.PrevNode.NextNode = Remove.NextNode
            if Remove.NextNode is not None:
                Remove.NextNode.PrevNode = Remove.PrevNode
        
    def GetNodeAt(self, Location):
        Location -= 1
        Current = self.Head

        while Current is not None and Location >= 0:
            Current = Current.NextNode
            Location -= 1
        return Current

    def PrintList(self):
        cur = self.Head
        while cur:
            print(cur.Data)
            cur = cur.NextNode


print("\n연결리스트 테스트\n")
Dl = DoublyLinkedList()
Dl.AppendNode(10)
Dl.AppendNode(30)
Dl.AppendNode(20)
Dl.AppendNode(40)
Dl.AppendNode(50)

Dl.PrintList()

print("\n데이터 삽입 후\n")
Current = Dl.GetNodeAt(2)
Dl.InsertAfter(Current, 3000)
Dl.InsertBefore(Current, 5000)
Dl.PrintList()


print("\n노드 삭제\n")
remove = Dl.GetNodeAt(5)
Dl.RemoveNode(remove)
Dl.PrintList()