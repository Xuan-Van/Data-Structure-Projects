Status Information()//��ʾ��Ϣ
{
    char id[20],choice;
    int i,price,date,count=0;
    Client C;
    printf("�������������֤��:");
    scanf("%s",id);
    printf("���\t��ɻ���\t�������\t����\t�ִ�\t�����\t�ɻ���\t�������\t���ʱ��\t����ʱ��\t��λ\t�۸�\t����\n");
    for(i=0;i<airnum;i++)
    {
        if(Search(A[i].L,id,&C))
        {
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%02d��%02d��\t%02d:%02d\t\t%02d:%02d\t\t",A[i].number,A[i].airport,A[i].nextairport,A[i].departure,A[i].destination,A[i].flightNum,A[i].planeNum,A[i].month,A[i].day,A[i].hour,A[i].min,A[i].nexthour,A[i].nextmin);
            price=A[i].price;
            if(A[i].L->C.grade=='F') {price*=1.5;printf("ͷ�Ȳ�");}
            else if(A[i].L->C.grade=='C') {price*=1.3;printf("�����");}
            else printf("���ò�");
            printf("\t%-dԪ",price);
            date=A[i].date;
            printf("\t%s\n",week[date]);
            count++;
        }
    }
    if(count)
    {
        while(1)
        {
            printf("�Ƿ���Ʊ(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') Refund(id);
            if(count>1)
            {
                printf("�Ƿ������Ʊ(y|n):");
                scanf(" %c",&choice);
                if(choice=='y') continue;
                else break;
            }
            else break;
        }
                
    }
    else
    {
        printf("δ�ҵ������֤�ŵ���ض�Ʊ��Ϣ,�Ƿ��������(y|n):");
        scanf(" %c",&choice);
        if(choice=='y') Information();
    }
    return OK;
}

Status Refund(char id[])//��Ʊ
{
    int num,i,flag=0;
    char name[12],choice;
    Client C;
    printf("<<<<<<<<<<<<<<<�����ڰ�����Ʊҵ��>>>>>>>>>>>\n");
    while(1)
    {
        printf("��ѡ�����:");
        scanf("%d",&num);
        printf("�Ƿ�ȷ����Ʊ,��������������ȷ��:");
        scanf("%s",name);
        for(i=0;i<airnum;i++)
        {
            if(num==A[i].number)
            {
                List L=A[i].L->next;
                while(L!=NULL)
                {
                    if(strcmp(name,L->C.name)==0&&strcmp(id,L->C.ID)==0)
                    {
                        C=L->C;
                        flag=1;
                        break;
                    }
                    L=L->next;
                }
            }
        }
        if(flag)
        {
            printf("�����Ե�,����Ϊ��������Ʊ!\n");
            Delete(A[num-1].L,C);
            if(!QueueEmpty(&(A[num-1].Q)))
            {
                Client E;
                if(CheckQueue(&(A[num-1].Q),C.grade,&E)==0) AirlineBack(&A[num-1],C.grade);
                else OrderInSert(A[num-1].L,E);
            }
            else
            {
                AirlineBack(&A[num-1],C.grade);
                return OK;
            }
        }
        else
        {
            printf("�������,�Ƿ���������(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') continue;
            else break;
        }
    }     
    printf("δ�ɹ���Ʊ!\n");
    return OK;
}