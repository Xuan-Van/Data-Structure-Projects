#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量
#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int SElemType;
typedef int Status;
static SElemType t=1;
typedef struct
{
    SElemType *base;//栈底指针
    SElemType *top;//栈顶指针
    int stacksize;//栈容量
}SqStack;

Status InitStack(SqStack *S)//构造一个空栈S
{
    S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base)
        exit(OVERFLOW);//存储分配失败
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status ClearStack(SqStack *S)//把S置为空栈
{
	S->top=S->base;
	return ERROR;
}

Status StackEmpty(SqStack *S)//若S为空栈，则返回OK；否则返回ERROR
{
	if(S->base==S->top)
		return OK;
	else
		return ERROR;		
}

SElemType StackLength(SqStack *S)//返回S的元素个数，即栈的长度
{
	return S->top-S->base;
}

Status Push(SqStack *S,SElemType e)//插入元素e为新的栈顶元素
{
	if(S->top-S->base>=S->stacksize)//栈满，追加存储空间
	{
		S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S->base)
			exit(OVERFLOW);//存储分配失败
		S->top=S->base+S->stacksize;
		S->stacksize+=STACKINCREMENT;	 
	}
	*(S->top++)=e;
	return OK;
}

Status Pop(SqStack *S,SElemType *e)//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

Status Print(SqStack *S)//打印序列状态变化过程
{
    SElemType *p,i,max=0;
	p=S->base;
	while(p!=S->top)//输出序列
	{
		printf("%d",*p);
		p++;
	}
    printf("  具体过程:");
    p=S->base;
    while(p!=S->top)//输出序列状态变化过程
	{
        for(i=max+1;i<=*p;i++)
            printf("%d进 ",i);
        printf("%d出 ",*p);
        if(max<*p)
            max=*p;
		p++;
	}
	printf("\n");
}

Status Process(SqStack *S,SqStack *Q,SElemType n,SElemType i)//找出当前元素进栈后所有可能的操作
{
    SElemType *e,a;
    e=&a;
    if(i<n)//编号进栈递归 
    {
        Push(S,i+1);
        Process(S,Q,n,i+1);
        Pop(S,e);
        i--;
    }
    if(!StackEmpty(S))//递归处理出栈
    {
        Pop(S,e);
        Push(Q,a);
        Process(S,Q,n,i+1);
        Pop(Q,e);
        Push(S,a);
    }
    if(StackLength(Q)==n&&StackEmpty(S))//输出可能的方案
    {
        printf("第%d种情况:",t);
        Print(Q);
        t++;
    }
}

SElemType main()
{
    SElemType n,x=1;
    SqStack *S,*Q,s,q;
    S=&s;
    Q=&q;
    InitStack(S);
    InitStack(Q);
    while(x)
    {      
        printf("请输入车厢序列编号:");
        scanf("%d",&n);
        printf("输出序号为:\n");
        t=1;
        Process(S,Q,n,0);
        ClearStack(S);
        ClearStack(Q);
        printf("是否继续输入车厢序列编号: 1:继续 0:退出\n");
        scanf("%d",&x);
    }
    system("pause");
    return ERROR;
}