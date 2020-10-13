#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINREASEMENT 10
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

typedef struct{
    char *base;
    char * top;
    int stacksize;
}SqStack;

void InitStack(SqStack * pSqStack);
char Gettop(SqStack * S);
void Push(SqStack * S, char e);
char Pop(SqStack * S);
int In(char c);
int Precede(char a, char b);
int Operate(char a, char theta, char b);
int EvaluateExpression();

int main(){
    printf("%d", EvaluateExpression());
    return 0;
}

//创建一个空栈S
void InitStack(SqStack * pSqStack){
    pSqStack->base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
    if(!pSqStack->base) exit(OVERFLOW);
    pSqStack->top=pSqStack->base;
    pSqStack->stacksize = STACK_INIT_SIZE;
}

//若栈不空则返回S的栈顶元素，否则返回空字符串并报错。
char Gettop(SqStack * S){
    if(S->top == S->base) {
        printf("%s", "STACK_EMPTY_ERROR");
        return ' ';
    }
    char e = *(S->top - 1);
    return e;
}

//插入e为新的栈顶元素
void Push(SqStack * S, char e){
    if(S->top - S->base >= S->stacksize){
        S->base = (char*)realloc(S->base, (S->stacksize + STACKINREASEMENT)*sizeof(char));
        if(!S->base) exit(OVERFLOW);
        S->stacksize += STACKINREASEMENT;
    }
    *(S->top++) = e;
}

//若栈不空则删除栈顶元素，并返回其值，否则返回空字符串并报错。
char Pop(SqStack * S){
    if(S->top == S->base){
        printf("%s", "STACK_EMPTY_ERROR");
        return ' ';
    }
    char e = *(--S->top);
    return e;
}

//判断c是否为运算符，是则返回TRUE,否则返回FALSE
int In(char c){
    char a[] = "+-*/()#";
    int i = 0;
    for(i=0; i<7; i++){
        if(c == a[i]) return TRUE;
    }
    return FALSE;
}

//比较a，b优先级
int Precede(char a, char b){
    int numa;
    switch (a)
    {
    case '+':
        numa = 0;
        break;
    case '-':
        numa = 1;
        break;
    case '*':
        numa = 2;
        break;
    case '/':
        numa = 3;
        break;
    case '(':
        numa = 4;
        break;
    case ')':
        numa = 5;
        break;  
    case '#':
        numa = 6;
        break;
    default:
        break;
    }
    int numb;
    switch (b)
    {
    case '+':
        numb = 0;
        break;
    case '-':
        numb = 1;
        break;
    case '*':
        numb = 2;
        break;
    case '/':
        numb = 3;
        break;
    case '(':
        numb = 4;
        break;
    case ')':
        numb = 5;
        break;  
    case '#':
        numb = 6;
        break;
    default:
        break;
    }
    int n[7][7] = { 1, 1,-1,-1,-1, 1, 1,
                    1, 1,-1,-1,-1, 1, 1,
                    1, 1, 1, 1,-1, 1, 1,
                    1, 1, 1, 1,-1, 1, 1,
                   -1,-1,-1,-1,-1, 0, 0,
                    1, 1, 1, 1, 0, 1, 1,
                   -1,-1,-1,-1,-1, 0, 0 };
    return n[numa][numb];
}

int Operate(char a, char theta, char b){
    int numa = a - '0';
    int numb = b - '0';
    switch (theta)
    {
    case '+':
        return numa + numb;
        break;
    case '-':
        return numa - numb;
        break;
    case '*':
        return numa * numb;
        break;
    case '/':
        return numa / numb;
        break;
    default:
        break;
    }
    return 0;
}

int EvaluateExpression(){
    //算术表达式求值的算符优先算法。OPTR--运算符栈 OPND--运算数栈
    //OP为运算符集合
    SqStack OPTR;
    SqStack OPND;
    InitStack(&OPTR);
    InitStack(&OPND);
    Push(&OPTR, '#');
    char c = getchar();
    char theta,a,b,x;
    while (c!='#'||Gettop(&OPTR)!='#')
    {
        if(!In(c)){
            Push(&OPND, c);
            c = getchar();
        }else
        {
            switch(Precede(Gettop(&OPTR), c)) {
                case -1:
                    Push(&OPTR, c);
                    c = getchar();
                    break;
                case 0:
                    Pop(&OPTR);
                    c = getchar();
                    break;
                case 1:
                    theta = Pop(&OPTR);
                    b = Pop(&OPND);
                    a = Pop(&OPND);
                    Push(&OPND, Operate(a, theta, b)+'0');
                    break;
            }
        }
    }
    return Gettop(&OPND)-'0';
}
