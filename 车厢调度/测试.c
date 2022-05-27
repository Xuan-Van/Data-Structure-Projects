#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACKINCREMENT 10 //�洢�ռ��������
#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int SElemType;
typedef int Status;
static SElemType t=1;
typedef struct
{
    SElemType *base;//ջ��ָ��
    SElemType *top;//ջ��ָ��
    int stacksize;//ջ����
}SqStack;

Status InitStack(SqStack *S)//����һ����ջS
{
    S->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base)
        exit(OVERFLOW);//�洢����ʧ��
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status ClearStack(SqStack *S)//��S��Ϊ��ջ
{
	S->top=S->base;
	return ERROR;
}

Status StackEmpty(SqStack *S)//��SΪ��ջ���򷵻�OK�����򷵻�ERROR
{
	if(S->base==S->top)
		return OK;
	else
		return ERROR;		
}

SElemType StackLength(SqStack *S)//����S��Ԫ�ظ�������ջ�ĳ���
{
	return S->top-S->base;
}

Status Push(SqStack *S,SElemType e)//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if(S->top-S->base>=S->stacksize)//ջ����׷�Ӵ洢�ռ�
	{
		S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S->base)
			exit(OVERFLOW);//�洢����ʧ��
		S->top=S->base+S->stacksize;
		S->stacksize+=STACKINCREMENT;	 
	}
	*(S->top++)=e;
	return OK;
}

Status Pop(SqStack *S,SElemType *e)//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

Status Print(SqStack *S)//��ӡ����״̬�仯����
{
    SElemType *p,i,max=0;
	p=S->base;
	while(p!=S->top)//�������
	{
		printf("%d",*p);
		p++;
	}
    printf("  �������:");
    p=S->base;
    while(p!=S->top)//�������״̬�仯����
	{
        for(i=max+1;i<=*p;i++)
            printf("%d�� ",i);
        printf("%d�� ",*p);
        if(max<*p)
            max=*p;
		p++;
	}
	printf("\n");
}

Status Process(SqStack *S,SqStack *Q,SElemType n,SElemType i)//�ҳ���ǰԪ�ؽ�ջ�����п��ܵĲ���
{
    SElemType *e,a;
    e=&a;
    if(i<n)//��Ž�ջ�ݹ� 
    {
        Push(S,i+1);
        Process(S,Q,n,i+1);
        Pop(S,e);
        i--;
    }
    if(!StackEmpty(S))//�ݹ鴦���ջ
    {
        Pop(S,e);
        Push(Q,a);
        Process(S,Q,n,i+1);
        Pop(Q,e);
        Push(S,a);
    }
    if(StackLength(Q)==n&&StackEmpty(S))//������ܵķ���
    {
        printf("��%d�����:",t);
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
        printf("�����복�����б��:");
        scanf("%d",&n);
        printf("������Ϊ:\n");
        t=1;
        Process(S,Q,n,0);
        ClearStack(S);
        ClearStack(Q);
        printf("�Ƿ�������복�����б��: 1:���� 0:�˳�\n");
        scanf("%d",&x);
    }
    system("pause");
    return ERROR;
}