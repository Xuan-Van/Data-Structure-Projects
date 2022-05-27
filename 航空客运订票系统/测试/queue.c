Status InitQueue(Queue *Q)//构造一个空队列
{
    Q->front=(List)malloc(1*sizeof(node));
    if(!Q->front) exit(OVERFLOW);
    Q->rear=Q->front;
    Q->front->next=NULL;
    return OK;
}

Status EnQueue(Queue*Q,Client E)//插入元素E为Q的新的队尾元素
{
    List new=(List)malloc(sizeof(node));
    if(!new) exit(OVERFLOW);
    new->C=E;
    new->next=NULL;
    Q->rear->next=new;
    Q->rear=new;
    return OK;
}

Status DeQueue(Queue *Q,Client *E)//若队列不空，则删除Q的队头元素，用E返回其值，并返回OK；否则返回ERROR
{
    if(Q->front==Q->rear) return ERROR;
    List head=Q->front->next;
    *E=head->C;
    Q->front->next=head->next;
    if(Q->rear==head) Q->rear=Q->front;
    free(head);
    return OK;
}

Status QueueEmpty(Queue *Q)//若队列Q为空队列，则返回OK；否则返回ERROR
{
    if(Q->front==Q->rear) return OK;
    return ERROR;
}

Status CheckQueue(Queue *Q,char space,Client *E)//检查退票是否满足候补客户需求，并排队候补
{
    Queue S;
    InitQueue(&S);
    int flag=0;
    while(!QueueEmpty(Q))
    {
        Client D;
        DeQueue(Q,&D);
        if(D.grade==space)
        {
            *E=D;
            flag=1;
            space='\0';
        }
        else
            EnQueue(&S,D);
    }
    *Q=S;
    if(flag==0) return ERROR;
    return OK;
}