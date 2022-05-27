Status admin(Graph *G)   //密码登录功能
{
    int i;
    char password[20],choice;
    A:printf("请输入密码:");fflush(stdin);
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
        printf("\n密码正确!\n");
        system("pause");adminFun(G);
    }
    else
    {
        printf("\n密码错误,是否重新输入(y|n):");
        fflush(stdin);scanf("%c",&choice);
        if(choice=='y') goto A;
    }
    saveCity(G);saveGraph(G);
}

Status adminFun(Graph *G)   //管理员模式
{
    int choose;
    A:system("cls");
    printf("==============================\n");
    printf("       欢迎进入管理员模式\n");
    printf("==============================\n");
    printf("       1.添加城市\n");
    printf("       2.删除城市\n");
    printf("       3.编辑交通\n");
    printf("       4.查询交通\n");
    printf("       0.退出\n");
    printf("请选择功能:");scanf("%d",&choose);
    switch(choose)
    {
        case 1:addCity(G);goto A;
        case 2:deleteCity(G);goto A;
        case 3:editRoute(G);goto A;
        case 4:findRoute(G);goto A;
        default:break;
    }
}

Status addCity(Graph *G)   //添加城市
{
    char name[20],choice;
    A:system("cls");
    printf("请输入城市名称:");
    fflush(stdin);scanf("%s",name);
    if(locateCity(G,name)>=0) printf("%s城市已存在!\n",name);
    else
    {
        printf("请输入%s的经度:",name);scanf("%lf",&G->city[G->citynum].lng);
        printf("请输入%s的纬度:",name);scanf("%lf",&G->city[G->citynum].lat);
        strcpy(G->city[G->citynum].name,name);
        G->citynum++;
        printf("添加成功!\n");
    }
    printf("是否继续添加城市(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}

Status deleteCity(Graph *G)   //删除城市
{
    char name[20],choice;
    int i,delete,del;
    A:system("cls");
    printf("请输入城市名称:");
    fflush(stdin);scanf("%s",name);
    del=locateCity(G,name);
    if(del<0) printf("%s城市不存在!\n",name);
    else
    {
        B:printf("请输入管理员账号确认删除%s城市及其所有路线:",name);
        scanf("%d",&delete);
        if(delete!=33550336)
        {
            printf("账号错误,是否重新输入(y|n):");
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
            printf("删除成功!\n");
        }
    }
    printf("是否继续删除城市(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}

Status editRoute(Graph *G)   //编辑交通路线
{
    char name1[20],name2[20],choice;
    int i,j,city1,city2,cost;
    double time;
    A:system("cls");
    printf("请输入起始城市名称:");
    fflush(stdin);scanf("%s",name1);
    city1=locateCity(G,name1);
    if(city1<0) printf("%s城市不存在!\n",name1);
    else
    {
        printf("请输入目标城市名称:");
        fflush(stdin);scanf("%s",name2);
        city2=locateCity(G,name2);
        if(city2<0) printf("%s城市不存在!\n",name2);
        else
        {
            if(G->timeEdges[city1][city2]!=INF&&G->costEdges[city1][city2]!=INF)
                printf("%s--->%s\t用时:%.2lfh\t花费:%d￥\n",name1,name2,G->timeEdges[city1][city2]/3600.0,G->costEdges[city1][city2]);
            else printf("暂无%s-->%s的路线!\n",name1,name2);
            B:printf("请输入时间(h):");scanf("%lf",&time);
            time*=3600;
            if(time<=0||time>=INF) {printf("输入错误,请重新输入!\n");goto B;}
            G->timeEdges[city1][city2]=(int)time;
            G->timeEdges[city2][city1]=(int)time;
            C:printf("请输入费用(￥):");scanf("%d",&cost);
            if(cost<=0||cost>=INF) {printf("输入错误,请重新输入!\n");goto C;}
            G->costEdges[city1][city2]=cost;
            G->costEdges[city2][city1]=cost;
            printf("编辑成功!\n");
        }
    }
    printf("是否继续编辑路线(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}

Status findRoute(Graph *G)   //查看城市的所有路线
{
    char name[20],choice;
    int i,find;
    A:system("cls");
    printf("请输入城市名称:");
    fflush(stdin);scanf("%s",name);
    find=locateCity(G,name);
    if(find<0) printf("%s城市不存在!\n",name);
    else
    {
        printf("目标城市     时间     费用\n");
        for(i=0;i<G->citynum;i++)
        {
            if(i!=find&&G->timeEdges[find][i]!=INF&&G->costEdges[find][i]!=INF)
                printf("%s\t%.2lfh\t%d￥\n",G->city[i].name,G->timeEdges[find][i]/3600.0,G->costEdges[find][i]);
        }
    }
    printf("是否继续查看交通(y|n):");
    fflush(stdin);scanf("%c",&choice);
    if(choice=='y') goto A;
}