Status Entry()//录入家谱
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

Status Insert()//添加成员
{
    char father[20];
    A=NULL;B=NULL;
    InitTree(&A);
    printf("请输入:姓名(不能重名) 性别(男1|女0) 配偶姓名(没有输入无) 出生日期(8位数) 是否在世(1|0) 父亲姓名\n ");
    scanf("%s %d %s %d %d %s",&A->data.name,&A->data.sex,&A->data.spouse,&A->data.birthday,&A->data.alive,father);
    SearchTree(T,A->data.name,&B);
    if(B!=NULL)
    {
        printf("姓名与家族成员重名!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    B=NULL;
    if(A->data.sex!=1&&A->data.sex!=0)
    {
        printf("性别输入有误!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    if(A->data.alive!=1&&A->data.alive!=0)
    {
        printf("莫把生命当儿戏!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    if(!CheckBirthday(A->data.birthday))
    {
        printf("出生日期输入有误!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    SearchTree(T,father,&B);
    if(B==NULL)
    {
        printf("此人的父亲不在家谱里!\n");
        free(A);
        A=NULL;
        return ERROR;
    }
    if(B->data.seniority!=0&&B->data.birthday>=A->data.birthday)
    {
        printf("出生日期不能比父亲早!\n");
        free(A);
        A=NULL;
        B=NULL;
        return ERROR;
    }
    InsertTree(&B,&A);
    printf("添加了新的家庭成员!\n");
    A=NULL;
    return OK;
}

Status Search()//查找成员
{
    char name[20];
    printf("请输入姓名:");
    scanf("%s",name);
    A=NULL;
    SearchTree(T,name,&A);
    if(A==NULL)
    {
        printf("不存在名为%s的人\n",name);
        return ERROR;
    }
    Show(&A);
    A=NULL;
    return OK;
}

Status Delete()//删除成员
{
    A=NULL;B=NULL;
    char name[20],fatherName[20];
    printf("请输入姓名:");
    scanf("%s",name);
    SearchTree(T,name,&A);
    if(A==NULL)
    {
        printf("不存在名为%s的人\n",name);
        return ERROR;
    }
    printf("请输入其父亲的名字确定删除:");
    scanf("%s",fatherName);
    SearchTree(T,fatherName,&B);
    if(B==NULL)
    {
        printf("此人的父亲不在家谱里!\n");
        return ERROR;
    }
    DeleteTree(&A);
    printf("已删除%s及其后代的全部信息!\n",name);
    A=NULL;B=NULL;
    return OK;
}

Status Change()//修改人物信息
{
    A=NULL;
    char name[20];
    printf("请输入姓名:");
    scanf("%s",name);
    SearchTree(T,name,&A);
    if(A==NULL)
    {
        printf("不存在名为%s的人\n",name);
        return ERROR;
    }
    Edit(&A,T);
    A=NULL;
    return OK;
}

Status Edit(Tree *B,Forest T)//修改成员信息
{
    if((*B)==NULL) return ERROR;
    if((*B)->data.seniority==0)
    {
        printf("该节点为森林根结点,禁止操作!\n");
        system("pause");
        return ERROR;
    }
    int choice; 
    A:system("cls");
    Show(&(*B));
    printf("\n您想修改什么信息?\n\n");
    printf("********************************\n");
    printf("0.退出   1.姓名   2.性别   3.配偶   4.记录过世(慎重选择)\n");
    printf("********************************\n");		        
	printf("请输入序号:");
    fflush(stdin);
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            printf("请输入新名字:");
            char name[20];
            fflush(stdin);
            scanf("%s",name);
            Tree D;
            SearchTree(T,name,&D);
            if(D!=NULL) printf("与其他家庭成员重名!\n");
            else strcpy((*B)->data.name,name);
            system("pause");goto A;
        case 2:
            printf("你的性别为(男1|女0):");
            int sex;
            fflush(stdin);
            scanf("%d",&sex);
            if(sex!=0&&sex!=1)
            {
                printf("输入有误\n");
                system("pause"); goto A;
            }
            (*B)->data.sex=sex;
            system("pause"); goto A;
        case 3:
            printf("请输入配偶姓名:");
            char spouse[100];
            fflush(stdin);
            scanf("%s",spouse);
            strcpy((*B)->data.spouse,spouse);
            system("pause"); goto A;
		case 4:
            if((*B)->data.alive) (*B)->data.alive=0;
            printf("逝者安息,生者奋然。\n");
            system("pause"); goto A;
        case 0:break;
        default:goto A;
    } 
    return OK; 
}

Status Show(Tree *A)//显示成员信息
{
    if((*A)==NULL) return ERROR;
    if((*A)->data.seniority==0)
    {
        printf("该节点为森林根结点，禁止操作!\n");
        system("pause");return ERROR;
    }
    printf("%s ",(*A)->data.name);
    if((*A)) printf("性别:男 ");
    else printf("性别:女 ");
    printf("配偶姓名:%s ",(*A)->data.spouse);
    printf("辈分为%d 出生日期:",(*A)->data.seniority);
    Birthday((*A)->data.birthday);
    if(((*A)->data.alive)==1) printf(" 在世 ");
    else printf(" 逝世 ");
    if(((*A)->data.seniority)!=1) printf("父亲姓名:%s\n",(*A)->father->data.name);
    else printf("是家族的始祖\n");
    return OK;
}

Status Out(Tree T)//存储家谱
{
    if((fp=fopen("family.csv","w"))==NULL) return ERROR;
    fprintf(fp,"姓名,性别,配偶,出生日期,是否在世,父亲\n");
    SaveTree(T);
    return OK;
}