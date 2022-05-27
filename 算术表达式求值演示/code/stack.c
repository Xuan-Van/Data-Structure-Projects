#include "stack.h"
int InitStack(OPTR *S)//构造运算符栈
{
    S->base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base) exit(-2);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return 1;
}

int initStack(OPND *S)//构造数字栈
{
    S->base=(double *)malloc(STACK_INIT_SIZE*sizeof(double));
    if(!S->base) exit(-2);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return 1;
}

char GetTop(OPTR *S)//输出运算符栈栈顶元素
{
    if(S->top==S->base) return 0;
    return *(S->top-1);
}

double getTop(OPND *S)//输出数字栈栈顶元素
{
    if(S->top==S->base) return 0;
    return *(S->top-1);
}

int Push(OPTR *S,char e)//元素入运算符栈
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(char *)realloc(S->base,(S->stacksize+STACK_INIT_SIZE*sizeof(char)));
        if(!S->base) exit(-2);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKNCREMENT;
    }
    *S->top++=e;
    return 1;
}

int push(OPND *S,double e)//元素到数字栈
{
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(double*)realloc(S->base,(S->stacksize+STACK_INIT_SIZE*sizeof(double)));
        if(!S->base) exit(-2);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKNCREMENT;
    }
    *S->top++=e;
    return 1;
}

int Pop(OPTR *S,char *e)//元素出运算符栈
{
    if(S->top==S->base) return 0;
    *e=*(--S->top);
    return 1;
}

int pop(OPND *S,double *e)//元素出数字栈
{
    if(S->top==S->base) 
        return 0;
    *e=*(--S->top);
    return 1;
}

int OutPut(OPTR *S)//输出运算符栈
{
    char *p;
    p=S->base;
    fprintf(fp,"OPTR栈: ");
    while(p!=S->top)
    {
        fprintf(fp," %c ",*p);
        p++;
    }
    fprintf(fp,"\n");
}

int outPut(OPND *S)//输出数字栈
{
    double *p;
    p=S->base;
    fprintf(fp,"OPND栈: ");
    while(p!=S->top)
    {
        fprintf(fp," %lf ",*p);
        p++;
    }
    fprintf(fp,"\n");
}