Status inquire(Graph *G)   //��ѯ·��
{
    char name1[20],name2[20],choice,name[100],filename[105],order[120];;
    int i,j,city1,city2,choose,flag;
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
        else if(city1==city2) printf("�����ظ��������!\n");
        else
        {  
            printf("=====================\n");
            printf("1.��쵽��\n2.���ٷ���\n");
            printf("=====================\n");
            A:printf("��ѡ�����ԭ��:");
            scanf("%d",&choose);
            if(choose!=1&&choose!=2) {printf("�������,����������!\n");goto A;}
            flag=bestRoute(G,city1,city2,choose);
            printf("\n�Ƿ�鿴��һ�ַ���(y|n):");
            fflush(stdin);scanf("%c",&choice);
            if(choice=='y')
            {
                choose=3-choose;
                flag=bestRoute(G,city1,city2,choose);
            }
            if(flag)
            {
                strcpy(order,"copy tmp.html ");strcpy(name,G->city[city1].name);
                strcat(name,"����");strcat(name,G->city[city2].name);
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

Status bestRoute(Graph *G,int city1,int city2,int flag)   //����·��
{
    int sum=0;
    if(flag==1)
        floyd(G->citynum,G->timeEdges);
    else
        floyd(G->citynum,G->costEdges);
    if(weight[city1][city2]!=INF)
    {
        if(flag==1)
            printf("\n%s--->%s��������ʱΪ:%.2lfh\t",G->city[city1].name,G->city[city2].name,weight[city1][city2]/3600.0);
        else printf("\n%s--->%s�����ٻ���Ϊ:%d��\t",G->city[city1].name,G->city[city2].name,weight[city1][city2]);
        int x=path[city1][city2],a,b,result=0;
        a=city1;
        printf("·��Ϊ:%s",G->city[city1].name);
        while(x!=-1)
        {
            printf("-->%s",G->city[x].name);
            if(flag==1) result+=G->costEdges[a][x];
            else result+=G->timeEdges[a][x];
            a=x;
            x=path[city1][x];
        }
        printf("-->%s\t",G->city[city2].name);
        if(flag==1) {result+=G->costEdges[a][city2];printf("����Ϊ%d��\n",result);}
        else {result+=G->timeEdges[a][city2];printf("��ʱΪ%.2lfh\n",result/3600.0);}
        return 1;
    }
    else printf("%s��%s֮�䲻�ɴ�!\n",G->city[city1].name,G->city[city2].name);
    return 0;
}

Status floyd(int n,int edge[][MAX])   //���������㷨
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