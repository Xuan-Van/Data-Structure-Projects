Status inquire(Graph *G)   //查询路线
{
    char name1[20],name2[20],choice,name[100],filename[105],order[120];;
    int i,j,city1,city2,choose,flag;
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
        else if(city1==city2) printf("请勿重复输入城市!\n");
        else
        {  
            printf("=====================\n");
            printf("1.最快到达\n2.最少费用\n");
            printf("=====================\n");
            A:printf("请选择决策原则:");
            scanf("%d",&choose);
            if(choose!=1&&choose!=2) {printf("输入错误,请重新输入!\n");goto A;}
            flag=bestRoute(G,city1,city2,choose);
            printf("\n是否查看另一种方案(y|n):");
            fflush(stdin);scanf("%c",&choice);
            if(choice=='y')
            {
                choose=3-choose;
                flag=bestRoute(G,city1,city2,choose);
            }
            if(flag)
            {
                strcpy(order,"copy tmp.html ");strcpy(name,G->city[city1].name);
                strcat(name,"——");strcat(name,G->city[city2].name);
                strcpy(filename,name);
                strcat(filename,".html");
                strcat(order,filename);strcat(order,">nul");
                system(order);
                fp=fopen(filename,"a");
                fprintf(fp,"\nvar start=new BMap.Point(%lf,%lf);\n",G->city[city1].lng,G->city[city1].lat);
                fprintf(fp,"var end=new BMap.Point(%lf,%lf);\n",G->city[city2].lng,G->city[city2].lat);
                fprintf(fp,"driving.search(start,end);\n</script>\n</body>\n</html>");
                fclose(fp);
                system("pause");
                ShellExecute(NULL,"open",filename,NULL,NULL,SW_SHOWNORMAL);
            }
        }
    }
}

Status bestRoute(Graph *G,int city1,int city2,int flag)   //最优路线
{
    int sum=0;
    if(flag==1)
        floyd(G->citynum,G->timeEdges);
    else
        floyd(G->citynum,G->costEdges);
    if(weight[city1][city2]!=INF)
    {
        if(flag==1)
            printf("\n%s--->%s的最少用时为:%.2lfh\t",G->city[city1].name,G->city[city2].name,weight[city1][city2]/3600.0);
        else printf("\n%s--->%s的最少花费为:%d￥\t",G->city[city1].name,G->city[city2].name,weight[city1][city2]);
        int x=path[city1][city2],a,b,result=0;
        a=city1;
        printf("路径为:%s",G->city[city1].name);
        while(x!=-1)
        {
            printf("-->%s",G->city[x].name);
            if(flag==1) result+=G->costEdges[a][x];
            else result+=G->timeEdges[a][x];
            a=x;
            x=path[city1][x];
        }
        printf("-->%s\t",G->city[city2].name);
        if(flag==1) {result+=G->costEdges[a][city2];printf("花费为%d￥\n",result);}
        else {result+=G->timeEdges[a][city2];printf("用时为%.2lfh\n",result/3600.0);}
        return 1;
    }
    else printf("%s和%s之间不可达!\n",G->city[city1].name,G->city[city2].name);
    return 0;
}

Status floyd(int n,int edge[][MAX])   //弗洛伊德算法
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++) 
        {
            weight[i][j]=edge[i][j]; 
            path[i][j]=-1; 
        }
    }
    for(k=0;k<n;k++) 
    {
        for(i=0;i<n;i++) 
        {
            for(j=0;j<n;j++) 
            {
                if(weight[i][j]>weight[i][k]+weight[k][j])
                { 
                    weight[i][j]=weight[i][k]+weight[k][j]; 
                    path[i][j]=k; 
                } 
            } 
        }
    }
}