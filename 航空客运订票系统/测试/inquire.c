Status Query()//���߲�ѯ
{
    while(1)
    {
        char place1[15],place2[15],choice;
        int i,count=0;
        printf("��������ɵ�:");
        scanf("%s",place1);
        printf("������Ŀ�ĵ�:");
        scanf("%s",place2);
        //printf("����\t�ִ�\t�����\t���չ�˾\t�������\t���ʱ��\t����ʱ��\tͷ�Ȳ�\t�����\t���ò�\t�𲽼�\t��Ʊ��\t����\t\n"); 
        for(i=0;i<airnum;i++)
        {
            if(strcmp(place1,A[i].departure)==0&&strcmp(place2,A[i].destination)==0&&A[i].F+A[i].C+A[i].Y>0)
            {
                //PrintAirline(&A[i]);
                count++;
            }
        }
        if(count>0)
        {   
            printf("�������%d�˺����%sֱ�ӷ���%s\n",count,place1,place2);
            printf("�Ƿ�Ʊ(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') Booking(place1,place2);
        }
        else
        {
            printf("���û�д�%sֱ�ӷ���%s�ĺ���\n",place1,place2); 
            printf("�Ƿ�����ת����(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') Booking(place1,place2);
        }
        printf("�Ƿ������ѯ(y|n):");
        scanf(" %c",&choice);
        if(choice=='y') continue;
        else break;
    }
    return OK;
}

Status Booking(char place1[15],char place2[15])//��Ʊ
{
    printf("<<<<<<<<<<<<<<<�����ڰ���Ʊҵ��>>>>>>>>>>>\n");
    while(1)
    {
        int m,n,i,k,count=0;
        char choice;
        printf("����������(00-00):");
        scanf("%d-%d",&m,&n);
        printf("���\t����\t�ִ�\t�����\t���չ�˾\t�������\t���ʱ��\t����ʱ��\tͷ�Ȳ�\t�����\t���ò�\t�𲽼�\t��Ʊ��\t����\t\n");
        for(i=0;i<airnum;i++)
        {
            if(m==A[i].month&&n==A[i].day&&strcmp(place1,A[i].departure)==0&&strcmp(place2,A[i].destination)==0)
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
                printf("�Ƿ�ѡ����ת����(y|n):");
                scanf(" %c",&choice);
                if(choice=='y') TransitNum(k);
                else Number();
            }
            else Number();
        }
        else printf("���û��%d��%d�յ�Ŀ�꺽��\n",m,n);
        printf("�Ƿ��˳���Ʊ(y|n):");
        scanf(" %c",&choice);
        if(choice=='n') continue;
        else break;
    }
    return OK;
}

Status Number()//ѡ�����
{
    int i,flag=0;
    char choice;
    while(1)
    {
        int num;
        printf("�����붩Ʊ���:");
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
            printf("|ͷ�Ȳ�%dϯ|�����%dϯ|���ò�%dϯ|\n",A[i].F,A[i].C,A[i].Y);
            printf("�Ƿ��µ�(y|n):");
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
            printf("\n�Ƿ�Ը��ѡ������ڵ���������(y|n):");
            scanf(" %c",&choice);
            if(choice=='y') continue;
            else break;
        }
    }
    return OK;
}

Status PlaceOrder(Airline *B)//�µ�
{
    char choice;
    Client C,E;
    int count;
    while(1)
    {
        printf("�����붩Ʊ��:");
        scanf("%d",&count);
        if(B->F+B->C+B->Y<=count)
        {
            printf("��ǰ��Ʊ%d��,�Ƿ��������붩Ʊ��(y|n):",B->F+B->C+B->Y);
            scanf(" %c",&choice);
            if(choice=='y') continue;
            else
            {
                printf("��������,�뿼����������\n");
                return OK;
            }
        }
        else if(count<=0)
        {
            printf("�������!\n");
            continue;
        }
        else break;
    }
    while(count)
    {
        int flag=0;
        printf("����������Ԥ���Ĳ�λ�ȼ�( ͷ�Ȳ� F | ����� C | ���ò� Y ):");
        scanf(" %c",&C.grade);
        switch(C.grade)
        {
            case 'F':if(B->F==0) printf("��ǰû��ͷ�Ȳ�ϯλ\n");else {B->F--;flag=1;}break;
            case 'C':if(B->C==0) printf("��ǰû�������ϯλ\n");else {B->C--;flag=1;}break;
            case 'Y':if(B->Y==0) printf("��ǰû�о��ò�ϯλ\n");else {B->Y--;flag=1;}break;
            default:printf("��������!\n");flag=2;break;
        }
        if(flag==1)
        {
            while(1)
            {
                FillBlank(&C);
                if(Search(B->L,C.ID,&E))
                {
                    printf("���֤��Ϊ%s�Ĺ˿����µ����κ���,�Ƿ�����¼��˿���Ϣ(y|n):",C.ID);
                    scanf(" %c",&choice);
                    if(choice=='y') continue;
                    else break;
                }
                else
                {
                    if(Conflict(C.ID,B))
                    {
                        OrderInSert(B->L,C);
                        printf("���ɹ���Ʊ!\n");
                        break;
                    }
                    else
                    {
                        printf("\n���ζ�����������ζ���ʱ���ͻ,��ѡ����������!\n");
                        break;
                    }
                }
            }
        }
        else if(flag>1) break;
        else
        {
            printf("�Ƿ����Ը��ǼǺ�(y|n):");
            scanf(" %c",&choice);
            if(choice=='y')
            {
                FillBlank(&C);
                EnQueue(&(B->Q),C);
                printf("��Ŀǰ���ŶӺ�!\n");
            }
            else
            {
                printf("�Ƿ�����ѡ��ϯλ(y|n):");
                scanf(" %c",&choice);
                if(choice=='y') continue;
                else break;
            }
        }
        count--;
    }
    return ERROR;
}

Status FillBlank(Client *C)//�ͻ���Ϣ¼��ϵͳ
{
    printf("����д������Ϣ:\n");
    printf("��������������:");
    scanf("%s",C->name);
    printf("�������������֤����:");
    scanf("%s",C->ID);
    return OK;
}

Status Transit(char place1[],char place2[],int m,int n)//������ת
{
    int i,j,k=0;
    printf("\n��ת��\t����\t��ת\t�ִ�\t�������\t���ʱ��\t����ʱ��\t��ת����\t��ת���ʱ��\t��ת����ʱ��\n");
    for(i=0;i<airnum;i++)
    {
        if(strcmp(A[i].departure,place1)==0&&A[i].month==m&&A[i].day==n)
        {
            for(j=0;j<airnum;j++)
            {
                if(strcmp(A[i].destination,A[j].departure)==0&&Day(&A[i],&A[j])==1&&strcmp(A[j].destination,place2)==0)
                {
                    printf("%d\t",k+1);
                    printf("%s\t%s\t%s\t",A[i].departure,A[i].destination,A[j].destination);
                    printf("%02d��%02d��\t%02d:%02d\t\t%02d:%02d\t\t%02d��%02d��\t%02d:%02d\t\t%02d:%02d\n",A[i].month,A[i].day,A[i].hour,A[i].min,A[i].nexthour,A[i].nextmin,A[j].month,A[j].day,A[j].hour,A[j].min,A[j].nexthour,A[j].nextmin);
                    transit[0][k]=A[i];
                    transit[1][k]=A[j];
                    k++;
                }
            }
        }
    }
    if(k) printf("����%d����ת����\n",k);
    else printf("û����ת����!\n");
    return k;
}

Status Day(Airline *B,Airline *D)//�ж���תʱ����ʱ������ʱ���Ƿ���ͬһ��
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

Status MonthDays(int month,int day)//����������һ���е�����
{
    int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int i,days=0;
    for(i=0;i<month-1;i++)
        days+=months[i];
    days+=day;
    return days;
}

Status TransitNum(int k)//��ת��Ʊ
{
    int i,x;
    char choice;
    printf("��ע����תʱ��,�Է����!\n");
    while(1)
    {
        printf("��������ת��:");
        scanf("%d",&x);
        if(x<=k&&x>=1)
        {
            printf("���\t����\t�ִ�\t�����\t���չ�˾\t�������\t���ʱ��\t����ʱ��\tͷ�Ȳ�\t�����\t���ò�\t�𲽼�\t��Ʊ��\t����\t\n");
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
            printf("��������,�Ƿ���������(y|n):");
            if(choice=='y') continue;
            else break;
        }
    }
    return OK;
}

Status Conflict(char id[],Airline *B)//�ж϶�Ʊʱ���Ƿ��ͻ
{
    int i;
    Client E;
    for(i=0;i<airnum;i++)
    {
        if(Search(A[i].L,id,&E))
        {
            if(DayConflit(B,&A[i]))
            {
                printf("����:%s\t�ִ�:%s\t�������:%02d��%02d��\t���ʱ��:%02d:%02d\t����ʱ��:%02d:%02d\t",A[i].departure,A[i].destination,A[i].month,A[i].day,A[i].hour,A[i].min,A[i].nexthour,A[i].nextmin);
                return ERROR;
            }
        }
    }
    return OK;
}

Status DayConflit(Airline *B,Airline *D)//�ж�ʱ���ͻ
{
    int min1[2],min2[2];
    TranMin(B,min1);
    TranMin(D,min2);
    if(min1[0]<min2[0]&&min1[1]>min2[0]||min2[0]<min1[0]&&min2[1]>min1[0]) return OK;
    return ERROR;
}

Status TranMin(Airline *B,int min[2])//ʱ��ת������
{
    int hour;
    min[0]=24*60*MonthDays(B->month,B->day)+B->hour*60+B->min;
    if(B->hour>=B->nexthour) hour=B->nexthour+24;
    else hour=B->nexthour;
    min[1]=24*60*MonthDays(B->month,B->day)+hour*60+B->nextmin;
    return OK;
}