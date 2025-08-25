#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;

// 수정전
// typedef struct tagETNode
// {
//     struct tagETNode* Left;
//     struct tagETNode* Right;

//     ElementType Data;
// } ETNode;

// 수정후
typedef struct tagETNode
{
    struct tagETNode* Left;
    struct tagETNode* Right;

    ElementType Data;
    int IsOperator; // 1: 연산자 노드, 0: 피연산자 노드
    char* Lexeme; // 피연산자 문자열(다지리/식별자), 연산자면 NULL
} ETNode;

ETNode* ET_CreateNode(ElementType NewData);
void ET_DestroyNode(ETNode* Node);
void ET_DestroyTree(ETNode* Root);

void ET_PreorderPrintTree(ETNode* Node);
void ET_InorderPrintTree(ETNode* Node);
void ET_PostorderPrintTree(ETNode* Node);
void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node);
double ET_Evaluate(ETNode* Tree);

#endif
