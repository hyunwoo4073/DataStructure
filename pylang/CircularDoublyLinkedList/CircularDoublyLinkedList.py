class Node:
    def __init__(self, NewNode):
        self.Data = NewNode
        self.PrevNode = None
        self.NextNode = None

class CircularDoublyLinkedList:
    def __init__(self):
        self.Head = None
        self.Tail = None

    def AppendNode(self, Data):
        NewNode = Node(Data)

        if self.Head is None:
            NewNode.PrevNode = NewNode
            NewNode.NextNode = NewNode
            self.Head = NewNode
            self.Tail = NewNode
            return
        
        NewNode.PrevNode = self.Tail
        NewNode.NextNode = self.Head
        self.Tail.NextNode = NewNode
        self.Head.PrevNode = NewNode
        self.Tail = NewNode

    def InsertAfter(self, Current, Data):
        NewNode = Node(Data)

        if self.Head is None:
            NewNode.PrevNode = NewNode
            NewNode.NextNode = NewNode
            self.Head = NewNode
            self.Tail = NewNode
            return

        NewNode.NextNode = Current.NextNode
        NewNode.PrevNode = Current
        Current.NextNode.PrevNode = NewNode
        Current.NextNode = NewNode
    
        if Current == self.Tail:
            self.Tail = NewNode
        
    def RemoveNode(self, Remove):
        if self.Head is None:
            return

        if self.Head == Remove and self.Head is self.Tail:
            self.Head = None
            self.Tail = None
            return
    
        Remove.PrevNode.NextNode = Remove.NextNode
        Remove.NextNode.PrevNode = Remove.PrevNode

        if Remove is self.Head:
            self.Head = Remove.NextNode
        if Remove is self.Tail:
            self.Tail = Remove.PrevNode
    
    def GetNodeAt(self, Location):
        Location -= 1
        Current = self.Head

        while Current is not None and Location >= 0:
            Current = Current.NextNode
            Location -= 1
        return Current
        
    def PrintList(self):
        if self.Head is None:
            print("List is empty")
            return

        cur = self.Head
        while True:
            print(cur.Data)
            cur = cur.NextNode
            if cur is self.Head:
                break


print("\n순환 연결리스트 테스트\n")
CDl = CircularDoublyLinkedList()
CDl.AppendNode(10)
CDl.AppendNode(30)
CDl.AppendNode(20)
CDl.AppendNode(40)
CDl.AppendNode(50)

CDl.PrintList()

print("\n데이터 삽입 후\n")
Current = CDl.GetNodeAt(2)
CDl.InsertAfter(Current, 3000)
# Dl.InsertBefore(Current, 5000)
CDl.PrintList()

print("\n노드 삭제\n")
remove = CDl.GetNodeAt(5)
CDl.RemoveNode(remove)
CDl.PrintList()