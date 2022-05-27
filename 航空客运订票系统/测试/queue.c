Status InitQueue(Queue *Q)//����һ���ն���
{
    Q->front=(List)malloc(1*sizeof(node));
    if(!Q->front) exit(OVERFLOW);
    Q->rear=Q->front;
    Q->front->next=NULL;
    return OK;
}

Status EnQueue(Queue*Q,Client E)//����Ԫ��EΪQ���µĶ�βԪ��
{
    List new=(List)malloc(sizeof(node));
    if(!new) exit(OVERFLOW);
    new->C=E;
    new->next=NULL;
    Q->rear->next=new;
    Q->rear=new;
    return OK;
}

Status DeQueue(Queue *Q,Client *E)//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���E������ֵ��������OK�����򷵻�ERROR
{
    if(Q->front==Q->rear) return ERROR;
    List head=Q->front->next;
    *E=head->C;
    Q->front->next=head->next;
    if(Q->rear==head) Q->rear=Q->front;
    free(head);
    return OK;
}

Status QueueEmpty(Queue *Q)//������QΪ�ն��У��򷵻�OK�����򷵻�ERROR
{
    if(Q->front==Q->rear) return OK;
    return ERROR;
}

Status CheckQueue(Queue *Q,char space,Client *E)//�����Ʊ�Ƿ�����򲹿ͻ����󣬲��ŶӺ�
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