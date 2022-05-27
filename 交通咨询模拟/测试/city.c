Status enterCity(Graph *G)   //¼�������Ϣ
{
    int i=0;
    if((fp=fopen("city.txt","r"))==NULL)
    {
        printf("���ļ�������city.txt!\n");
        system("pause");exit(0);
    }
    while(fscanf(fp,"%s %lf %lf",G->city[i].name,&G->city[i].lng,&G->city[i].lat)!=EOF) i++;
    fclose(fp);
    G->citynum=i;
}

Status saveCity(Graph *G)   //���������Ϣ
{
    fp=fopen("city.txt","w");
    for(int i=0;i<G->citynum;i++)
        fprintf(fp,"%s %lf %lf\n",G->city[i].name,G->city[i].lng,G->city[i].lat);
    fclose(fp);
}

Status locateCity(Graph *G,char name[])   //��λ����
{
    for(int i=0;i<G->citynum;i++)
    {
        if(strcmp(G->city[i].name,name)==0)
            return i;
    }
    return -1;
}

Status createGraph(Graph *G)   //����ͼ
{
    char *line,*record,buffer[1024],name1[20],name2[20];
    int i,j,city1,city2;
    if((fp=fopen("city.csv","r"))==NULL)
    {
        printf("���ļ�������city.csv!\n");
        system("pause");exit(0);
    }
    for(i=0;i<G->citynum;i++)
    {
        for(j=0;j<G->citynum;j++)
        {
            if(i==j)
            {
                G->timeEdges[i][j]=0;
                G->costEdges[i][j]=0;
            }
            else
            {
                G->timeEdges[i][j]=INF;
                G->costEdges[i][j]=INF;
            }
        }
    }
	fgets(buffer,sizeof(buffer),fp);
	while((line=fgets(buffer,sizeof(buffer),fp)))
	{
        record=strtok(line,",");
		if(record!=NULL)
		{
            sprintf(name1,"%s",record);record=strtok(NULL, ",");
            sprintf(name2,"%s",record);record=strtok(NULL, ",");
            city1=locateCity(G,name1);city2=locateCity(G,name2);
			G->timeEdges[city1][city2]=atoi(record);record=strtok(NULL, ",");
			G->costEdges[city1][city2]=atoi(record);record=strtok(NULL, ",");
            G->timeEdges[city2][city1]=G->timeEdges[city1][city2];
            G->costEdges[city2][city1]=G->costEdges[city1][city2];
		}
	}
	fclose(fp);   
}

Status saveGraph(Graph *G)   //����ͼ
{
    int i,j;
    fp=fopen("city.csv","w");
    fprintf(fp,"��ʼ����,Ŀ�����,ʱ��,����\n");
    for(i=0;i<G->citynum;i++)
    {
        for(j=i+1;j<G->citynum;j++)
        {
            if(G->timeEdges[i][j]!=INF&&G->costEdges[i][j]!=INF)
                fprintf(fp,"%s,%s,%d,%d\n",G->city[i].name,G->city[j].name,G->timeEdges[i][j],G->costEdges[i][j]);
        }
    }
    fclose(fp);
}