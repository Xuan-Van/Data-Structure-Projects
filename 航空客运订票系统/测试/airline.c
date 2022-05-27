Status EntryAirline()//¼�뺽����Ϣ
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

Status OutAirline()//�洢������Ϣ
{
    int i;
    if((fp=fopen("airline.csv","w+"))==NULL) return ERROR;
	fprintf(fp,"���,������,�ִ��,�����,���չ�˾,�ɻ���,�𲽼�,�ؿ���,ͷ�Ȳ�,�����,���ò�,��ɻ���,�������,��,��,����,ʱ,��,�ִ�ʱ,�ִ��\n");
    for(i=0;i<airnum;i++) fprintf(fp,"%d,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d\n",A[i].number,A[i].departure,A[i].destination,A[i].flightNum,A[i].company,A[i].planeNum,A[i].price,A[i].capacity,A[i].F,A[i].C,A[i].Y,A[i].airport,A[i].nextairport,A[i].month,A[i].day,A[i].date,A[i].hour,A[i].min,A[i].nexthour,A[i].nextmin);
    return OK;
}

Status PrintAirline(Airline *A)//��ӡ������Ϣ
{
    printf("%s\t%s\t%s\t%s\t",A->departure,A->destination,A->flightNum,A->company);
    printf("%02d��%02d��\t%02d:%02d\t\t%02d:%02d\t\t",A->month,A->day,A->hour,A->min,A->nexthour,A->nextmin);
    printf("%-d\t%-d\t%-d\t",A->F,A->C,A->Y);
    printf("%-dԪ\t%-d\t",A->price,A->F+A->C+A->Y);
    int i=A->date;
    printf("%-s\t\n",week[i]);
    return OK;
}

Status AirlineReady()//�������߶�Ӧ�����Ա�Ͷ���
{
    for(int i=0;i<airnum;i++)
    {
        Create(&(A[i].L));
        InitQueue(&(A[i].Q));
    }
    return OK;
}

Status AirlineBack(Airline *B,char C)//��Ʊ��λ
{
    switch(C)
    {
        case 'F':B->F++;break;
        case 'C':B->C++;break;
        case 'Y':B->Y++;break;
    }
    return OK;
}