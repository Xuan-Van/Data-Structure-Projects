Status EntryAirline()//录入航线信息
{
	char *line,*record,buffer[1024];
    int i=0;
	if((fp=fopen("airline.csv","r+"))==NULL) return ERROR;
	fseek(fp,127L,SEEK_SET);
	while((line=fgets(buffer,sizeof(buffer),fp))!=NULL)
	{
        record=strtok(line,",");
		if(record!=NULL)
		{
            A[i].number=atoi(record);record=strtok(NULL, ",");
            sprintf(A[i].departure,"%s",record);record=strtok(NULL, ",");
            sprintf(A[i].destination,"%s",record);record=strtok(NULL, ",");
            sprintf(A[i].flightNum,"%s",record);record=strtok(NULL, ",");
            sprintf(A[i].company,"%s",record);record=strtok(NULL, ",");
            sprintf(A[i].planeNum,"%s",record);record=strtok(NULL, ",");
			A[i].price=atoi(record);record=strtok(NULL, ",");
            A[i].capacity=atoi(record);record=strtok(NULL, ",");
			A[i].F=atoi(record);record=strtok(NULL, ",");
			A[i].C=atoi(record);record=strtok(NULL, ",");
			A[i].Y=atoi(record);record=strtok(NULL, ",");
            sprintf(A[i].airport,"%s",record);record=strtok(NULL, ",");
            sprintf(A[i].nextairport,"%s",record);record=strtok(NULL, ",");
			A[i].month=atoi(record);record=strtok(NULL, ",");
			A[i].day=atoi(record);record=strtok(NULL, ",");
            A[i].date=atoi(record);record=strtok(NULL, ",");
			A[i].hour=atoi(record);record=strtok(NULL, ",");
			A[i].min=atoi(record);record=strtok(NULL, ",");
            A[i].nexthour=atoi(record);record=strtok(NULL, ",");
            A[i].nextmin=atoi(record);record=strtok(NULL, ",");
		}
		i++;
	}
    airnum=i;
	fclose(fp);   
	return OK;
}

Status OutAirline()//存储航线信息
{
    int i;
    if((fp=fopen("airline.csv","w+"))==NULL) return ERROR;
	fprintf(fp,"序号,出发地,抵达地,航班号,航空公司,飞机号,起步价,载客量,头等舱,商务舱,
    经济舱,起飞机场,降落机场,月,日,星期,时,分,抵达时,抵达分\n");
    for(i=0;i<airnum;i++) fprintf(fp,"%d,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%s,%s,%d,
    %d,%d,%d,%d,%d,%d\n",A[i].number,A[i].departure,A[i].destination,A[i].flightNum,
    A[i].company,A[i].planeNum,A[i].price,A[i].capacity,A[i].F,A[i].C,A[i].Y,
    A[i].airport,A[i].nextairport,A[i].month,A[i].day,A[i].date,A[i].hour,A[i].min,
    A[i].nexthour,A[i].nextmin);
    return OK;
}

Status PrintAirline(Airline *A)//打印航线信息
{
    printf("%s\t%s\t%s\t%s\t",A->departure,A->destination,A->flightNum,A->company);
    printf("%02d月%02d号\t%02d:%02d\t\t%02d:%02d\t\t",A->month,A->day,A->hour,A->min,
    A->nexthour,A->nextmin);
    printf("%-d\t%-d\t%-d\t",A->F,A->C,A->Y);
    printf("%-d元\t%-d\t",A->price,A->F+A->C+A->Y);
    int i=A->date;
    printf("%-s\t\n",week[i]);
    return OK;
}

Status AirlineReady()//构建航线对应的线性表和队列
{
    for(int i=0;i<airnum;i++)
    {
        Create(&(A[i].L));
        InitQueue(&(A[i].Q));
    }
    return OK;
}

Status AirlineBack(Airline *B,char C)//退票后补位
{
    switch(C)
    {
        case 'F':B->F++;break;
        case 'C':B->C++;break;
        case 'Y':B->Y++;break;
    }
    return OK;
}