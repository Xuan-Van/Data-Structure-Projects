Status Create(List *B)//创建乘客名单
{
    (*B)=(List)malloc(sizeof(node));
    (*B)->next=NULL;
    return OK;
}

Status OrderInSert(List B,Client E)//客户信息放入名单
{
    List L=B;
    while(L->next!=NULL)
    {
        L=L->next;

    }
    List S=(List)malloc(sizeof(node));
    S->C=E;
    S->next=NULL;
    L->next=S;
    return OK;
}

Status Search(List B,char id[],Client *E)//查询客户订票信息
{
    List L=B->next;
    int flag=0;
    while(L!=NULL)
    {
        if(strcmp(L->C.ID,id)==0)
        {
            *E=L->C;
            flag=1;
            break;
        }
        L=L->next;
    }
    if(flag==0) return ERROR;
    return OK;
}

Status Delete(List B,Client E)//名单移除订票信息
{
    List L=B;
    while(L->next!=NULL)
    {
        List M=L->next;
        if(strcmp(E.ID,M->C.ID)==0)
        {
            L->next=M->next;
            free(M);
            printf("成功办理退票!\n");
            break;
        }
        L=L->next;
    }
    return OK;
}

Status EntryList()//录入客户名单
{
    Client C;
	char *line,*record,buffer[1024];
	if((fp=fopen("client.csv","r+"))==NULL) return ERROR;
	fseek(fp,29L,SEEK_SET);
	while((line=fgets(buffer,sizeof(buffer),fp))!=NULL)
	{
		record=strtok(line,",");
        int i=atoi(record);
        record=strtok(NULL, ",");
		if(record!=NULL)
		{
			sprintf(C.name,"%s",record);record=strtok(NULL, ",");
            sprintf(C.ID,"%s",record);record=strtok(NULL, ",");
            C.grade=record[0];record=strtok(NULL, ",");
		}
        OrderInSert(A[i-1].L,C);
	}
	fclose(fp);
	return OK;
}

Status OutList()//存储客户名单
{
    if((fp=fopen("client.csv","w+"))==NULL) return ERROR;
    fprintf(fp,"序号,姓名,身份证号,飞机舱位\n");
    for(int i=0;i<airnum;i++)
    {
        List L=A[i].L->next;
        while(L!=NULL)
        {
            fprintf(fp,"%d,%s,%s,%c\n",A[i].number,L->C.name,L->C.ID,L->C.grade);
            L=L->next;
        }
    }
    return OK;
}