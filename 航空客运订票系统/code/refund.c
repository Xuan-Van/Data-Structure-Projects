Status Information()//显示信息
{
    char id[20],choice;
    int i,price,date,count=0;
    Client C;
    printf("请输入您的身份证号:");
    scanf("%s",id);
    printf("序号\t起飞机场\t降落机场\t出发\t抵达\t航班号\t飞机号\t起飞日期\t
    起飞时间\t到达时间\t舱位\t价格\t星期\n");
    for(i=0;i<airnum;i++)
    {
        if(Search(A[i].L,id,&C))
        {
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%02d月%02d号\t%02d:%02d\t\t
            %02d:%02d\t\t",A[i].number,A[i].airport,A[i].nextairport,
            A[i].departure,A[i].destination,A[i].flightNum,A[i].planeNum,
            A[i].month,A[i].day,A[i].hour,A[i].min,A[i].nexthour,A[i].nextmin);
            price=A[i].price;
            if(A[i].L->C.grade=='F') {price*=1.5;printf("头等舱");}
            else if(A[i].L->C.grade=='C') {price*=1.3;printf("商务舱");}
            else printf("经济舱");
            printf("\t%-d元",price);
            date=A[i].date;
            printf("\t%s\n",week[date]);
            count++;
        }
    }
    if(count)
    {
        while(1)
        {
            printf("是否退票(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') Refund(id);
            if(count>1)
            {
                printf("是否继续退票(y|n):");
                scanf(" %c",&choice);
                if(choice=='y') continue;
                else break;
            }
            else break;
        }
                
    }
    else
    {
        printf("未找到该身份证号的相关订票信息,是否继续查找(y|n):");
        scanf(" %c",&choice);
        if(choice=='y') Information();
    }
    return OK;
}

Status Refund(char id[])//退票
{
    int num,i,flag=0;
    char name[12],choice;
    Client C;
    printf("<<<<<<<<<<<<<<<您正在办理退票业务>>>>>>>>>>>\n");
    while(1)
    {
        printf("请选择序号:");
        scanf("%d",&num);
        printf("是否确认退票,请输入您的姓名确认:");
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
            printf("请您稍等,正在为您办理退票!\n");
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
            printf("输入错误,是否重新输入(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') continue;
            else break;
        }
    }     
    printf("未成功退票!\n");
    return OK;
}