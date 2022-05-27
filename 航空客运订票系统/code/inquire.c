Status Query()//航线查询
{
    while(1)
    {
        char place1[15],place2[15],choice;
        int i,count=0;
        printf("请输入起飞地:");
        scanf("%s",place1);
        printf("请输入目的地:");
        scanf("%s",place2);
        //printf("出发\t抵达\t航班号\t航空公司\t起飞日期\t起飞时间\t到达时间\t头等舱\t
        //商务舱\t经济舱\t起步价\t余票量\t星期\t\n"); 
        for(i=0;i<airnum;i++)
        {
            if(strcmp(place1,A[i].departure)==0&&
            strcmp(place2,A[i].destination)==0&&A[i].F+A[i].C+A[i].Y>0)
            {
                //PrintAirline(&A[i]);
                count++;
            }
        }
        if(count>0)
        {   
            printf("最近共有%d趟航班从%s直接飞往%s\n",count,place1,place2);
            printf("是否订票(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') Booking(place1,place2);
        }
        else
        {
            printf("最近没有从%s直接飞往%s的航班\n",place1,place2); 
            printf("是否考虑中转航班(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') Booking(place1,place2);
        }
        printf("是否继续查询(y|n):");
        scanf(" %c",&choice);
        if(choice=='y') continue;
        else break;
    }
    return OK;
}

Status Booking(char place1[15],char place2[15])//订票
{
    printf("<<<<<<<<<<<<<<<您正在办理订票业务>>>>>>>>>>>\n");
    while(1)
    {
        int m,n,i,k,count=0;
        char choice;
        printf("请输入日期(00-00):");
        scanf("%d-%d",&m,&n);
        printf("序号\t出发\t抵达\t航班号\t航空公司\t起飞日期\t起飞时间\t到达时间\t
        头等舱\t商务舱\t经济舱\t起步价\t余票量\t星期\t\n");
        for(i=0;i<airnum;i++)
        {
            if(m==A[i].month&&n==A[i].day&&strcmp(place1,A[i].departure)==0&&
            strcmp(place2,A[i].destination)==0)
            {
                printf("%d\t",A[i].number);
                PrintAirline(&A[i]);
                count++;
            }
        }
        k=Transit(place1,place2,m,n);
        count+=k;
        if(count>0)
        {
            if(k)
            {
                printf("是否选择中转航班(y|n):");
                scanf(" %c",&choice);
                if(choice=='y') TransitNum(k);
                else Number();
            }
            else Number();
        }
        else printf("最近没有%d月%d日的目标航班\n",m,n);
        printf("是否退出订票(y|n):");
        scanf(" %c",&choice);
        if(choice=='n') continue;
        else break;
    }
    return OK;
}

Status Number()//选择序号
{
    int i,flag=0;
    char choice;
    while(1)
    {
        int num;
        printf("请输入订票序号:");
        scanf("%d",&num);
        for(i=0;i<airnum;i++)
        {
            if(num==A[i].number)
            {   
                flag=1;
                break;
            }
        }
        if(flag)
        {
            printf("|头等舱%d席|商务舱%d席|经济舱%d席|\n",A[i].F,A[i].C,A[i].Y);
            printf("是否下单(y|n):");
            scanf(" %c",&choice);
            if(choice=='y')
            {   
                PlaceOrder(&A[i]);
                break;
            }
            else break;
        }
        else
        {
            printf("\n是否愿意选择该日期的其他航班(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') continue;
            else break;
        }
    }
    return OK;
}

Status PlaceOrder(Airline *B)//下单
{
    char choice;
    Client C,E;
    int count;
    while(1)
    {
        printf("请输入订票数:");
        scanf("%d",&count);
        if(B->F+B->C+B->Y<=count)
        {
            printf("当前余票%d张,是否重新输入订票数(y|n):",B->F+B->C+B->Y);
            scanf(" %c",&choice);
            if(choice=='y') continue;
            else
            {
                printf("人数过多,请考虑其他航班\n");
                return OK;
            }
        }
        else if(count<=0)
        {
            printf("输入错误!\n");
            continue;
        }
        else break;
    }
    while(count)
    {
        int flag=0;
        printf("请输入你想预订的舱位等级( 头等舱 F | 商务舱 C | 经济舱 Y ):");
        scanf(" %c",&C.grade);
        switch(C.grade)
        {
            case 'F':if(B->F==0) printf("当前没有头等舱席位\n");else {B->F--;flag=1;}break;
            case 'C':if(B->C==0) printf("当前没有商务舱席位\n");else {B->C--;flag=1;}break;
            case 'Y':if(B->Y==0) printf("当前没有经济舱席位\n");else {B->Y--;flag=1;}break;
            default:printf("输入有误!\n");flag=2;break;
        }
        if(flag==1)
        {
            while(1)
            {
                FillBlank(&C);
                if(Search(B->L,C.ID,&E))
                {
                    printf("身份证号为%s的顾客已下单本次航班,是否重新录入顾客信息(y|n):",
                    C.ID);
                    scanf(" %c",&choice);
                    if(choice=='y') continue;
                    else break;
                }
                else
                {
                    if(Conflict(C.ID,B))
                    {
                        OrderInSert(B->L,C);
                        printf("您成功订票!\n");
                        break;
                    }
                    else
                    {
                        printf("\n本次订单与您的这次订单时间冲突,请选择其他航班!\n");
                        break;
                    }
                }
            }
        }
        else if(flag>1) break;
        else
        {
            printf("是否继续愿意登记候补(y|n):");
            scanf(" %c",&choice);
            if(choice=='y')
            {
                FillBlank(&C);
                EnQueue(&(B->Q),C);
                printf("您目前在排队候补!\n");
            }
            else
            {
                printf("是否重新选择席位(y|n):");
                scanf(" %c",&choice);
                if(choice=='y') continue;
                else break;
            }
        }
        count--;
    }
    return ERROR;
}

Status FillBlank(Client *C)//客户信息录入系统
{
    printf("请填写个人信息:\n");
    printf("请输入您的姓名:");
    scanf("%s",C->name);
    printf("请输入您的身份证号码:");
    scanf("%s",C->ID);
    return OK;
}

Status Transit(char place1[],char place2[],int m,int n)//订单中转
{
    int i,j,k=0;
    printf("\n中转号\t出发\t中转\t抵达\t起飞日期\t起飞时间\t到达时间\t中转日期\t
    中转起飞时间\t中转到达时间\n");
    for(i=0;i<airnum;i++)
    {
        if(strcmp(A[i].departure,place1)==0&&A[i].month==m&&A[i].day==n)
        {
            for(j=0;j<airnum;j++)
            {
                if(strcmp(A[i].destination,A[j].departure)==0&&Day(&A[i],&A[j])==1
                &&strcmp(A[j].destination,place2)==0)
                {
                    printf("%d\t",k+1);
                    printf("%s\t%s\t%s\t",A[i].departure,A[i].destination,
                    A[j].destination);
                    printf("%02d月%02d日\t%02d:%02d\t\t%02d:%02d\t\t%02d月%02d日\t
                    %02d:%02d\t\t%02d:%02d\n",A[i].month,A[i].day,A[i].hour,A[i].min,
                    A[i].nexthour,A[i].nextmin,A[j].month,A[j].day,A[j].hour,A[j].min,
                    A[j].nexthour,A[j].nextmin);
                    transit[0][k]=A[i];
                    transit[1][k]=A[j];
                    k++;
                }
            }
        }
    }
    if(k) printf("共有%d趟中转航班\n",k);
    else printf("没有中转航班!\n");
    return k;
}

Status Day(Airline *B,Airline *D)//判断中转时到达时间和起飞时间是否在同一天
{
    int day;
    if(B->nexthour>=B->hour) day=B->day;
    else day=B->day+1;
    if(MonthDays(B->month,day)==MonthDays(D->month,D->day))
    {
        if(B->nexthour+1<D->hour) return OK;
        else if(B->nexthour+1==D->hour)
        {
            if(B->nextmin<D->min) return OK;
        }
    }
    return ERROR;
}

Status MonthDays(int month,int day)//计算日期在一年中的天数
{
    int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int i,days=0;
    for(i=0;i<month-1;i++)
        days+=months[i];
    days+=day;
    return days;
}

Status TransitNum(int k)//中转订票
{
    int i,x;
    char choice;
    printf("请注意中转时间,以防误机!\n");
    while(1)
    {
        printf("请输入中转号:");
        scanf("%d",&x);
        if(x<=k&&x>=1)
        {
            printf("序号\t出发\t抵达\t航班号\t航空公司\t起飞日期\t起飞时间\t到达时间\t
            头等舱\t商务舱\t经济舱\t起步价\t余票量\t星期\t\n");
            printf("%d\t",transit[0][x-1].number);
            PrintAirline(&transit[0][x-1]);
            printf("%d\t",transit[1][x-1].number);
            PrintAirline(&transit[1][x-1]);
            Number();
            Number();
            break;
        }
        else
        {
            printf("输入有误,是否重新输入(y|n):");
            if(choice=='y') continue;
            else break;
        }
    }
    return OK;
}

Status Conflict(char id[],Airline *B)//判断订票时间是否冲突
{
    int i;
    Client E;
    for(i=0;i<airnum;i++)
    {
        if(Search(A[i].L,id,&E))
        {
            if(DayConflit(B,&A[i]))
            {
                printf("出发:%s\t抵达:%s\t起飞日期:%02d月%02d日\t起飞时间:%02d:%02d\t
                到达时间:%02d:%02d\t",A[i].departure,A[i].destination,A[i].month,
                A[i].day,A[i].hour,A[i].min,A[i].nexthour,A[i].nextmin);
                return ERROR;
            }
        }
    }
    return OK;
}

Status DayConflit(Airline *B,Airline *D)//判断时间冲突
{
    int min1[2],min2[2];
    TranMin(B,min1);
    TranMin(D,min2);
    if(min1[0]<min2[0]&&min1[1]>min2[0]||min2[0]<min1[0]&&min2[1]>min1[0]) return OK;
    return ERROR;
}

Status TranMin(Airline *B,int min[2])//时间转换分钟
{
    int hour;
    min[0]=24*60*MonthDays(B->month,B->day)+B->hour*60+B->min;
    if(B->hour>=B->nexthour) hour=B->nexthour+24;
    else hour=B->nexthour;
    min[1]=24*60*MonthDays(B->month,B->day)+hour*60+B->nextmin;
    return OK;
}