#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>
#include<conio.h>
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKNCREMENT 10 //存储空间分配增量
FILE *fp; //定义文件指针
typedef struct
{
    char *base;
    char *top;
    int stacksize;
}OPTR; //运算符栈
typedef struct
{
    double *base;
    double *top;
    int stacksize;
}OPND;//数字栈
int InitStack(OPTR *S); //构造运算符栈
int initStack(OPND *S); //构造数字栈
char GetTop(OPTR *S); //输出运算符栈栈顶元素
double getTop(OPND *S); //输出数字栈栈顶元素
int Push(OPTR *S,char e); //元素入运算符栈
int push(OPND *S,double e); //元素到数字栈
int Pop(OPTR *S,char *e); //元素出运算符栈
int pop(OPND *S,double *e); //元素出数字栈
int OutPut(OPTR *S); //输出运算符栈
int outPut(OPND *S); //输出数字栈