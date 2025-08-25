// #include "ExpressionTree.h"

// int main(void)
// {
//     ETNode* Root = NULL;

//     char PostfixExpression[20] = "71*52-/";
//     ET_BuildExpressionTree(PostfixExpression, &Root);

//     // 트리 출력
//     printf("Preorder ...\n");
//     ET_PreorderPrintTree(Root);
//     printf("\n\n");

//     printf("Inorder ...\n");
//     ET_InorderPrintTree(Root);
//     printf("\n\n");

//     printf("Postorder ...\n");
//     ET_PostorderPrintTree(Root);
//     printf("\n\n");

//     printf("Evaluation Result : %f \n", ET_Evaluate(Root));

//     // 트리 소멸
//     ET_DestroyTree(Root);

//     return 0;
// }

#include "ExpressionTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void run_postfix(const char* title, const char* postfix)
{
    // ET_BuildExpressionTree가 문자열을 수정하므로, 가변 버퍼에 복사
    char buf[512];
    strncpy(buf, postfix, sizeof(buf));
    buf[sizeof(buf)-1] = '\0';

    ETNode* root = NULL;
    ET_BuildExpressionTree(buf, &root);

    printf("== %s ==\n", title);
    printf("Expr : %s\n", postfix);
    printf("Pre  : "); ET_PreorderPrintTree(root);  printf("\n");
    printf("In   : "); ET_InorderPrintTree(root);   printf("\n");
    printf("Post : "); ET_PostorderPrintTree(root); printf("\n");
    printf("Eval : %.6f\n\n", ET_Evaluate(root));

    ET_DestroyTree(root);
}

int main(void)
{
    // 1) 공백 없는 한 자리 후위표기식 (네가 쓰던 형식)
    //    7 1 * 5 2 - /  => ((7*1)/(5-2)) = 2.333333...
    run_postfix("Single-digit (no spaces)", "71*52-/");

    // 2) 공백 구분 다자리 수
    //    (15 + 7) * (3 - 2) / 5 = 4.4
    run_postfix("Multi-digit", "15 7 + 3 2 - * 5 /");

    // 3) 음수 포함
    //    (-12 * 3) + 4 = -32
    run_postfix("Negative numbers", "-12 3 * 4 +");

    // 4) 실수 포함
    //    (3.5 / 2.0) * (-1) = -1.75
    run_postfix("Floating-point", "3.5 2.0 / -1 *");

    // 5) 또 다른 다자리 예시
    //    100 + (20 / 5) = 104
    run_postfix("Multi-digit #2", "100 20 5 / +");

    return 0;
}

