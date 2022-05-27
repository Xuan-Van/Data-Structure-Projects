#include "stack.h"
int InitStack(OPTR *S)//���������ջ
{
    S->base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base) exit(-2);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return 1;
}

int initStack(OPND *S)//��������ջ
{
    S->base=(double *)malloc(STACK_INIT_SIZE*sizeof(double));
    if(!S->base) exit(-2);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return 1;
}

char GetTop(OPTR *S)//��������ջջ��Ԫ��
{
    if(S->top==S->base) return 0;
    return *(S->top-1);
}

double getTop(OPND *S)//�������ջջ��Ԫ��
{
    if(S->top==S->base) return 0;
    return *(S->top-1);
}

int Push(OPTR *S,char e)//Ԫ���������ջ
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

int push(OPND *S,double e)//Ԫ�ص�����ջ
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

int Pop(OPTR *S,char *e)//Ԫ�س������ջ
{
    if(S->top==S->base) return 0;
    *e=*(--S->top);
    return 1;
}

int pop(OPND *S,double *e)//Ԫ�س�����ջ
{
    if(S->top==S->base) 
        return 0;
    *e=*(--S->top);
    return 1;
}

int OutPut(OPTR *S)//��������ջ
{
    char *p;
    p=S->base;
    fprintf(fp,"OPTRջ: ");
    while(p!=S->top)
    {
        fprintf(fp," %c ",*p);
        p++;
    }
    fprintf(fp,"\n");
}

int outPut(OPND *S)//�������ջ
{
    double *p;
    p=S->base;
    fprintf(fp,"OPNDջ: ");
    while(p!=S->top)
    {
        fprintf(fp," %lf ",*p);
        p++;
    }
    fprintf(fp,"\n");
}