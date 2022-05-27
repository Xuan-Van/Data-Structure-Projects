Status admin(Graph *G)   //�����¼����
{
    int i;
    char password[20],choice;
    A:printf("����������:");fflush(stdin);
    while(i<19&&(password[i]=getch())!='\r')
    {
        if(password[i]=='\b')
        {
            printf("\b b");
            i--;
        }
        else
        {
            putchar('*');
            i++;
        }
    }
    password[i]='\0';
    if(strcmp(password,"admin8128")==0)
    {
        printf("\n������ȷ!\n");
        system("pause");adminFun(G);
    }
    else
    {
        printf("\n�������,�Ƿ���������(y|n):");
        fflush(stdin);scanf("%c",&choice);
        if(choice=='y') goto A;
    }
    saveCity(G);saveGraph(G);
}

Status adminFun(Graph *G)   //����Աģʽ
{
    int choose;
    A:system("cls");
    printf("==============================\n");
    printf("       ��ӭ�������Աģʽ\n");
    printf("==============================\n");
    printf("       1.��ӳ���\n");
    printf("       2.ɾ������\n");
    printf("       3.�༭��ͨ\n");
    printf("       4.��ѯ��ͨ\n");
    printf("       0.�˳�\n");
    printf("��ѡ����:");scanf("%d",&choose);
    switch(choose)
    {
        case 1:addCity(G);goto A;
        case 2:deleteCity(G);goto A;
        case 3:editRoute(G);goto A;
        case 4:findRoute(G);goto A;
        default:break;
    }
}

Status addCity(Graph *G)   //��ӳ���
{
    char name[20],choice;
    A:system("cls");
    printf("�������������:");
    fflush(stdin);scanf("%s",name);
    if(locateCity(G,name)>=0) printf("%s�����Ѵ���!\n",name);
    else
    {
        printf("������%s�ľ���:",name);scanf("%lf",&G->city[G->citynum].lng);
        printf("������%s��γ��:",name);scanf("%lf",&G->city[G->citynum].lat);
        strcpy(G->city[G->citynum].name,name);
        G->citynum++;
        printf("��ӳɹ�!\n");
    }
    printf("�Ƿ������ӳ���(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}

Status deleteCity(Graph *G)   //ɾ������
{
    char name[20],choice;
    int i,delete,del;
    A:system("cls");
    printf("�������������:");
    fflush(stdin);scanf("%s",name);
    del=locateCity(G,name);
    if(del<0) printf("%s���в�����!\n",name);
    else
    {
        B:printf("���������Ա�˺�ȷ��ɾ��%s���м�������·��:",name);
        scanf("%d",&delete);
        if(delete!=33550336)
        {
            printf("�˺Ŵ���,�Ƿ���������(y|n):");
            fflush(stdin);scanf("%c",&choice);
            if(choice=='y') goto B;
        }
        else
        {
            for(i=0;i<G->citynum;i++)
            {
                G->timeEdges[del][i]=INF;
                G->costEdges[del][i]=INF;
                G->timeEdges[i][del]=INF;
                G->costEdges[i][del]=INF;
            }
            printf("ɾ���ɹ�!\n");
        }
    }
    printf("�Ƿ����ɾ������(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}

Status editRoute(Graph *G)   //�༭��ͨ·��
{
    char name1[20],name2[20],choice;
    int i,j,city1,city2,cost;
    double time;
    A:system("cls");
    printf("��������ʼ��������:");
    fflush(stdin);scanf("%s",name1);
    city1=locateCity(G,name1);
    if(city1<0) printf("%s���в�����!\n",name1);
    else
    {
        printf("������Ŀ���������:");
        fflush(stdin);scanf("%s",name2);
        city2=locateCity(G,name2);
        if(city2<0) printf("%s���в�����!\n",name2);
        else
        {
            if(G->timeEdges[city1][city2]!=INF&&G->costEdges[city1][city2]!=INF)
                printf("%s--->%s\t��ʱ:%.2lfh\t����:%d��\n",name1,name2,G->timeEdges[city1][city2]/3600.0,G->costEdges[city1][city2]);
            else printf("����%s-->%s��·��!\n",name1,name2);
            B:printf("������ʱ��(h):");scanf("%lf",&time);
            time*=3600;
            if(time<=0||time>=INF) {printf("�������,����������!\n");goto B;}
            G->timeEdges[city1][city2]=(int)time;
            G->timeEdges[city2][city1]=(int)time;
            C:printf("���������(��):");scanf("%d",&cost);
            if(cost<=0||cost>=INF) {printf("�������,����������!\n");goto C;}
            G->costEdges[city1][city2]=cost;
            G->costEdges[city2][city1]=cost;
            printf("�༭�ɹ�!\n");
        }
    }
    printf("�Ƿ�����༭·��(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}

Status findRoute(Graph *G)   //�鿴���е�����·��
{
    char name[20],choice;
    int i,find;
    A:system("cls");
    printf("�������������:");
    fflush(stdin);scanf("%s",name);
    find=locateCity(G,name);
    if(find<0) printf("%s���в�����!\n",name);
    else
    {
        printf("Ŀ�����     ʱ��     ����\n");
        for(i=0;i<G->citynum;i++)
        {
            if(i!=find&&G->timeEdges[find][i]!=INF&&G->costEdges[find][i]!=INF)
                printf("%s\t%.2lfh\t%d��\n",G->city[i].name,G->timeEdges[find][i]/3600.0,G->costEdges[find][i]);
        }
    }
    printf("�Ƿ�����鿴��ͨ(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}