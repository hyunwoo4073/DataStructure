#include "ExpressionTree.h"
#include <ctype.h>

static int is_op_char(char c)
{
    return (c=='+' || c=='-' || c=='*' || c=='/');
}

// 공백으로 토큰 구분되어 있다고 가정
static int pop_last_token(char* s, char* out, int outsz)
{
    int len = (int)strlen(s);
    int i = len - 1;

    // 뒤쪽 공백 제거
    while (i>=0 && isspace((unsigned char)s[i])) i--;
    if (i < 0) return 0;

    int end = i;
    // 토큰 시작까지 이동
    while (i>=0 && !isspace((unsigned char)s[i])) i--;
    int start = i + 1;

    int tlen = end - start + 1;
    if (tlen >= outsz) tlen = outsz - 1;
    memcpy(out, s+start, tlen);
    out[tlen] = '\0';

    // 원본을 잘라서 다음 호출 때 앞쪽만 보게 함
    s[start] = '\0';
    return 1;
}

// 한자리 수만 계산 가능함
// 수정전
// ETNode* ET_CreateNode(ElementType NewData)
// {
//     ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
//     NewNode->Left = NULL;
//     NewNode->Right = NULL;
//     NewNode->Data = NewData;

//     return NewNode;
// }

// 수정후
ETNode* ET_CreateNode(ElementType NewData)
{
    ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    NewNode->Lexeme = NULL;
    NewNode->IsOperator = is_op_char(NewData) ? 1 : 0;

    return NewNode;
}

// 수정전
// void ET_DestroyNode(ETNode* Node)
// {
//     free(Node);
// }

// 수정후
void ET_DestroyNode(ETNode* Node)
{
    if (!Node) return;
    if (Node->Lexeme) free(Node->Lexeme);
    free(Node);
}

void ET_DestroyTree(ETNode* Root)
{
    if (Root == NULL)
        return;

    ET_DestroyTree(Root->Left);
    ET_DestroyTree(Root->Right);
    ET_DestroyNode(Root);
}

// 추가
static void print_token(ETNode* Node)
{
    if (Node->IsOperator) printf("%c", Node->Data);
    else if (Node->Lexeme) printf("%s", Node->Lexeme);
    else printf("%c", Node->Data);
}

// 수정전
// void ET_PreorderPrintTree(ETNode* Node)
// {
//     if (Node == NULL)
//         return;

//     printf("%c", Node->Data);

//     ET_PreorderPrintTree(Node->Left);
//     ET_PreorderPrintTree(Node->Right);
// }

// 수정후
void ET_PreorderPrintTree(ETNode* Node)
{
    if (Node == NULL)
        return;

    print_token(Node);

    ET_PreorderPrintTree(Node->Left);
    ET_PreorderPrintTree(Node->Right);
}

// 수정전
// void ET_InorderPrintTree(ETNode* Node)
// {
//     if (Node == NULL)
//         return;

//     printf("(");
//     ET_InorderPrintTree(Node->Left);

//     printf("%c", Node->Data);

//     ET_InorderPrintTree(Node->Right);
//     printf(")");
// }

// 수정후
void ET_InorderPrintTree(ETNode* Node)
{
    if (Node == NULL)
        return;

    printf("(");
    ET_InorderPrintTree(Node->Left);

    print_token(Node);

    ET_InorderPrintTree(Node->Right);
    printf(")");
}


// 수정전
// void ET_PostorderPrintTree(ETNode* Node)
// {
//     if (Node == NULL)
//         return;

//     ET_PostorderPrintTree(Node->Left);
//     ET_PostorderPrintTree(Node->Right);
//     printf("%c", Node->Data);
// }

// 수정후
void ET_PostorderPrintTree(ETNode* Node)
{
    if (Node == NULL)
        return;

    ET_PostorderPrintTree(Node->Left);
    ET_PostorderPrintTree(Node->Right);
    print_token(Node);
}

// 수정전
// void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
// {
//     int len = strlen(PostfixExpression);
//     char Token = PostfixExpression[len - 1];
//     PostfixExpression[len - 1] = '\0';

//     switch (Token)
//     {   
//         // 연산자인 경우
//         case '+': case '-': case '*': case '/':
//             (*Node) = ET_CreateNode(Token);
//             ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
//             ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
//             break;

//         // 피연산자인 경우
//         default:
//             (*Node) = ET_CreateNode(Token);
//             break;
//     }
// }

// 수정후
static char* my_strdup_local(const char* s) {
    size_t n = strlen(s) + 1;
    char* p = (char*)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
{
    if (!Node || !PostfixExpression) return;

    // 뒤 공백 제거
    int len = (int)strlen(PostfixExpression);
    while (len>0 && isspace((unsigned char)PostfixExpression[len-1])) {
        PostfixExpression[--len] = '\0';
    }
    if (len == 0) { *Node = NULL; return; }

    // 공백 존재 여부 판단
    int has_space = 0;
    for (int i=0; i<len; i++) {
        if (isspace((unsigned char)PostfixExpression[i])) { has_space = 1; break; }
    }

    if (has_space) {
        // 공백 구분(다자리수/음수/식별자 지원)
        char tok[256];
        if (!pop_last_token(PostfixExpression, tok, sizeof(tok))) {
            *Node = NULL; return;
        }
        if (strlen(tok) == 1 && is_op_char(tok[0])) {
            *Node = ET_CreateNode(tok[0]); // 연산자
            ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
            ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
        } else {
            *Node = ET_CreateNode(0);      // 피연산자
            (*Node)->IsOperator = 0;
            (*Node)->Lexeme = my_strdup_local(tok);
        }
    } else {
        // 공백 없음(모두 단일 문자 토큰으로 처리)
        char token = PostfixExpression[len-1];
        PostfixExpression[len-1] = '\0';

        if (is_op_char(token)) {
            *Node = ET_CreateNode(token);  // 연산자
            ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
            ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
        } else {
            *Node = ET_CreateNode(token);  // 피연산자(단일 문자)
            // Lexeme는 NULL, IsOperator=0(ET_CreateNode에서 설정)
        }
    }
}

// 수정후
double ET_Evaluate(ETNode* Tree)
{
    if (Tree == NULL) return 0.0;

    if (Tree->IsOperator) {
        double Left  = ET_Evaluate(Tree->Left);
        double Right = ET_Evaluate(Tree->Right);
        switch (Tree->Data) {
            case '+': return Left + Right;
            case '-': return Left - Right;
            case '*': return Left * Right;
            case '/': return Right == 0 ? 0.0 : (Left / Right);
            default:  return 0.0;
        }
    } else {
        // 피연산자: Lexeme 우선, 없으면 단일 문자 fallback
        if (Tree->Lexeme && *Tree->Lexeme != '\0')
            return atof(Tree->Lexeme);

        char Temp[2] = {0,};
        Temp[0] = (Tree->Data ? Tree->Data : '0');
        return atof(Temp);
    }
}

// 수정전
// double ET_Evaluate(ETNode* Tree)
// {
//     char Temp[2];

//     double Left = 0;
//     double Right = 0;
//     double Result = 0;

//     if (Tree == NULL)
//         return 0;

//     switch (Tree->Data)
//     {
//         // 연산자인 경우
//         case '+': case '-': case '*': case '/':
//             Left = ET_Evaluate(Tree->Left);
//             Right = ET_Evaluate(Tree->Right);

//                 if (Tree->Data == '+') Result = Left + Right;
//                 else if (Tree->Data == '-') Result = Left - Right;
//                 else if (Tree->Data == '*') Result = Left * Right;
//                 else if (Tree->Data == '/') Result = Left / Right;

//                 break;
        
//         // 피연산자인 경우
//         default:
//         memset(Temp, 0, sizeof(Temp));
//         Temp[0] = Tree->Data;
//         Result = atof(Temp);
//         break;
//     }

//     return Result;
// }

// 수정후
// double ET_Evaluate(ETNode* Tree)
// {
//     if (Tree == NULL) return 0.0;

//     if (Tree->IsOperator) {
//         double Left  = ET_Evaluate(Tree->Left);
//         double Right = ET_Evaluate(Tree->Right);
//         switch (Tree->Data) {
//             case '+': return Left + Right;
//             case '-': return Left - Right;
//             case '*': return Left * Right;
//             case '/': return Right == 0 ? 0.0 : (Left / Right);
//             default:  return 0.0;
//         }
//     } else {
//         // 피연산자: Lexeme 우선, 없으면 단일 문자 fallback
//         if (Tree->Lexeme && *Tree->Lexeme != '\0')
//             return atof(Tree->Lexeme);

//         char Temp[2] = {0,};
//         Temp[0] = (Tree->Data ? Tree->Data : '0');
//         return atof(Temp);
//     }
// }
