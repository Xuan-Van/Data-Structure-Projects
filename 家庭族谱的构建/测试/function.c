Status Entry()//¼�����
{
    InitTree(&T);
    char *line,*record,buffer[1024];
    if((fp=fopen("family.csv","r"))==NULL) return ERROR;
    char father[20];
    fseek(fp,39L,SEEK_SET);
    while((line=fgets(buffer,sizeof(buffer),fp))!=NULL)
    {
        A=NULL;B=NULL;
        InitTree(&A);
        record=strtok(line,","); 
        if(record!=NULL)
        {
            sprintf(A->data.name,"%s",record);record=strtok(NULL,",");
            A->data.sex=atoi(record);record=strtok(NULL,",");
            sprintf(A->data.spouse,"%s",record);record=strtok(NULL,",");
            A->data.birthday=atoi(record);record=strtok(NULL,",");
            A->data.alive=atoi(record);record=strtok(NULL,",");
            sprintf(father,"%s",record);record=strtok(NULL,",");
            SearchTree(T,father,&B);
            if(B!=NULL) InsertTree(&B,&A);
        }    
    }
    free(A);
    A=NULL;
    fclose(fp);
    return OK;
}

Status Insert()//��ӳ�Ա
{
    char father[20];
    A=NULL;B=NULL;
    InitTree(&A);
    printf("������:����(��������) �Ա�(��1|Ů0) ��ż����(û��������) ��������(8λ��) �Ƿ�����(1|0) ��������\n ");
    scanf("%s %d %s %d %d %s",&A->data.name,&A->data.sex,&A->data.spouse,&A->data.birthday,&A->data.alive,father);
    SearchTree(T,A->data.name,&B);
    if(B!=NULL)
    {
        printf("����������Ա����!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    B=NULL;
    if(A->data.sex!=1&&A->data.sex!=0)
    {
        printf("�Ա���������!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    if(A->data.alive!=1&&A->data.alive!=0)
    {
        printf("Ī����������Ϸ!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    if(!CheckBirthday(A->data.birthday))
    {
        printf("����������������!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    SearchTree(T,father,&B);
    if(B==NULL)
    {
        printf("���˵ĸ��ײ��ڼ�����!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    if(B->data.seniority!=0&&B->data.birthday>=A->data.birthday)
    {
        printf("�������ڲ��ܱȸ�����!\n");
        free(A);
        A=NULL;
        B=NULL;
        return ERROR;
    }
    InsertTree(&B,&A);
    printf("������µļ�ͥ��Ա!\n");
    A=NULL;
    return OK;
}

Status Search()//���ҳ�Ա
{
    char name[20];
    printf("����������:");
    scanf("%s",name);
    A=NULL;
    SearchTree(T,name,&A);
    if(A==NULL)
    {
        printf("��������Ϊ%s����\n",name);
        return ERROR;
    }
    Show(&A);
    A=NULL;
    return OK;
}

Status Delete()//ɾ����Ա
{
    A=NULL;B=NULL;
    char name[20],fatherName[20];
    printf("����������:");
    scanf("%s",name);
    SearchTree(T,name,&A);
    if(A==NULL)
    {
        printf("��������Ϊ%s����\n",name);
        return ERROR;
    }
    printf("�������丸�׵�����ȷ��ɾ��:");
    scanf("%s",fatherName);
    SearchTree(T,fatherName,&B);
    if(B==NULL)
    {
        printf("���˵ĸ��ײ��ڼ�����!\n");
        return ERROR;
    }
    DeleteTree(&A);
    printf("��ɾ��%s��������ȫ����Ϣ!\n",name);
    A=NULL;B=NULL;
    return OK;
}

Status Change()//�޸�������Ϣ
{
    A=NULL;
    char name[20];
    printf("����������:");
    scanf("%s",name);
    SearchTree(T,name,&A);
    if(A==NULL)
    {
        printf("��������Ϊ%s����\n",name);
        return ERROR;
    }
    Edit(&A,T);
    A=NULL;
    return OK;
}

Status Edit(Tree *B,Forest T)//�޸ĳ�Ա��Ϣ
{
    if((*B)==NULL) return ERROR;
    if((*B)->data.seniority==0)
    {
        printf("�ýڵ�Ϊɭ�ָ����,��ֹ����!\n");
        system("pause");
        return ERROR;
    }
    int choice; 
    A:system("cls");
    Show(&(*B));
    printf("\n�����޸�ʲô��Ϣ?\n\n");
    printf("********************************\n");
    printf("0.�˳�   1.����   2.�Ա�   3.��ż   4.��¼����(����ѡ��)\n");
    printf("********************************\n");		        
	printf("���������:");
    fflush(stdin);
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            printf("������������:");
            char name[20];
            fflush(stdin);
            scanf("%s",name);
            Tree D;
            SearchTree(T,name,&D);
            if(D!=NULL) printf("��������ͥ��Ա����!\n");
            else strcpy((*B)->data.name,name);
            system("pause");goto A;
        case 2:
            printf("����Ա�Ϊ(��1|Ů0):");
            int sex;
            fflush(stdin);
            scanf("%d",&sex);
            if(sex!=0&&sex!=1)
            {
                printf("��������\n");
                system("pause"); goto A;
            }
            (*B)->data.sex=sex;
            system("pause"); goto A;
        case 3:
            printf("��������ż����:");
            char spouse[100];
            fflush(stdin);
            scanf("%s",spouse);
            strcpy((*B)->data.spouse,spouse);
            system("pause"); goto A;
		case 4:
            if((*B)->data.alive) (*B)->data.alive=0;
            printf("���߰�Ϣ,���߷�Ȼ��\n");
            system("pause"); goto A;
        case 0:break;
        default:goto A;
    } 
    return OK; 
}

Status Show(Tree *A)//��ʾ��Ա��Ϣ
{
    if((*A)==NULL) return ERROR;
    if((*A)->data.seniority==0)
    {
        printf("�ýڵ�Ϊɭ�ָ���㣬��ֹ����!\n");
        system("pause");return ERROR;
    }
    printf("%s ",(*A)->data.name);
    if((*A)) printf("�Ա�:�� ");
    else printf("�Ա�:Ů ");
    printf("��ż����:%s ",(*A)->data.spouse);
    printf("����Ϊ%d ��������:",(*A)->data.seniority);
    Birthday((*A)->data.birthday);
    if(((*A)->data.alive)==1) printf(" ���� ");
    else printf(" ���� ");
    if(((*A)->data.seniority)!=1) printf("��������:%s\n",(*A)->father->data.name);
    else printf("�Ǽ����ʼ��\n");
    return OK;
}

Status Out(Tree T)//�洢����
{
    if((fp=fopen("family.csv","w"))==NULL) return ERROR;
    fprintf(fp,"����,�Ա�,��ż,��������,�Ƿ�����,����\n");
    SaveTree(T);
    return OK;
}