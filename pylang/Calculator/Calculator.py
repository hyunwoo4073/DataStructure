from enum import Enum
from LinkedListStack import LinkedListStack

class Symbol(Enum):
    LEFT_PARENTHESIS  = ord('(')
    RIGHT_PARENTHESIS = ord(')')
    PLUS              = ord('+')
    MINUS             = ord('-')
    MULTIPLY          = ord('*')
    DIVIDE            = ord('/')
    SPACE             = ord(' ')
    OPERAND           = 100
    UNKNOWN           = -1

class Calculator:
    def IsNumber(self, Char: str):
        return ('0' <= Char <= '9') or (Char == '.')

    def GetNextToken(self, Expression: str, StartIndex: int = 0):
        Token = ''
        TokenType = Symbol.UNKNOWN
        i = StartIndex

        if i >= len(Expression):
            return '', Symbol.UNKNOWN, i

        Char = Expression[i]

        if self.IsNumber(Char):
            while i < len(Expression) and self.IsNumber(Expression[i]):
                Token += Expression[i]
                i += 1
            TokenType = Symbol.OPERAND
        else:
            Token = Char
            try:
                TokenType = Symbol(ord(Char))
            except ValueError:
                TokenType = Symbol.UNKNOWN
            i += 1

        return Token, TokenType, i

    def GetPriority(self, Operator, InStack):
        if Operator == '(':
            return 3 if InStack else 0
        elif Operator in ('*', '/'):
            return 1
        elif Operator in ('+', '-'):
            return 2
        else:
            return -1
    
    def IsPriority(self, OperatorInStack, OperatorInToken):
        return (self.GetPriority(OperatorInStack, 1)> self.GetPriority(OperatorInToken, 0))

    def GetPostfix(self, InfixExpression):
        Postfix = ''
        Stack = LinkedListStack()
        Position = 0

        while Position < len(InfixExpression):
            Token, Type_, Position = self.GetNextToken(InfixExpression, Position)
            
            if Type_ == Symbol.OPERAND:
                Postfix += Token + ' '
            elif Type_ == Symbol.RIGHT_PARENTHESIS:
                while not Stack.LLS_IsEmpty():
                    Top = Stack.LLS_Pop()
                    if Top == '(':
                        break
                    Postfix += Top + ''
            else:
                while (not Stack.LLS_IsEmpty() and not self.IsPriority(Stack.LLS_Top(), Token)):
                    Top = Stack.LLS_Pop()
                    if Top != '(':
                        Postfix += Top + ' '
                Stack.LLS_Push(Token)
        
        while not Stack.LLS_IsEmpty():
            Top = Stack.LLS_Pop()
            if Top != '(':
                Postfix += Top + ' '
        
        return Postfix.strip()
    
    def EvaluatePostfix(self, PostfixExpression: str):
        Stack = LinkedListStack()
        Position = 0

        while Position < len(PostfixExpression):
            Token, TokenType, Position = self.GetNextToken(PostfixExpression, Position)

            if TokenType == Symbol.SPACE:
                continue

            if TokenType == Symbol.OPERAND:
                Stack.LLS_Push(Token)
            else:
                Operand2 = float(Stack.LLS_Pop())
                Operand1 = float(Stack.LLS_Pop())
                result = 0.0

                if TokenType == Symbol.PLUS:
                    result = Operand1 + Operand2
                elif TokenType == Symbol.MINUS:
                    result = Operand1 - Operand2
                elif TokenType == Symbol.MULTIPLY:
                    result = Operand1 * Operand2
                elif TokenType == Symbol.DIVIDE:
                    result = Operand1 / Operand2

                Stack.LLS_Push(str(result))

        return float(Stack.LLS_Pop())    

if __name__ == "__main__":
    # calc = Calculator()
    # expression = "123+45.6*(7-2)"

    # idx = 0
    # while idx < len(expression):
    #     token, tokentype, next_idx = calc.GetNextToken(expression, idx)
    #     print(f"Token: '{token}', Type: {tokentype.name}, Next Index: {next_idx}")
    #     idx = next_idx

    # calc = Calculator()
    # expression = "3+(4*5)-6/(1+1)"
    # result = calc.GetPostfix(expression)
    # print("Infix:   ", expression)
    # print("Postfix: ", result)

    calc = Calculator()
    expr = input("수식을 입력하세요 (예: 3+4*2/(1-5)): ")
    postfix = calc.GetPostfix(expr)
    print("후위 표기식:", postfix)
    result = calc.EvaluatePostfix(postfix)
    print("계산 결과:", result)