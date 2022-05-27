Status InitTree(Tree *A)//创建家谱树
{
    (*A)=(Tree)malloc(sizeof(TNode));
    if((*A)==NULL) return ERROR;
    (*A)->father=NULL;
    (*A)->firstChild=NULL;
    (*A)->nextSibling=NULL;
    (*A)->data.birthday=0;
    (*A)->data.seniority=0;
    (*A)->data.sex=0;
    (*A)->data.alive=0;
    strcpy((*A)->data.name,"无");
    strcpy((*A)->data.spouse,"无");
    return OK;
}

Status SearchTree(Forest T,char name[20],Tree *B)//搜索成员姓名
{
    if(T==NULL) return ERROR;
    if(strcmp(T->data.name,name)==0)
    {
        (*B)=T;
        return OK;
    }
    SearchTree(T->firstChild,name,&(*B));
    if((*B)!=NULL) return OK;
    SearchTree(T->nextSibling,name,&(*B));
    return OK;
}

Status InsertTree(Tree *father,Tree *child)//插入新成员
{
    (*child)->data.seniority=(*father)->data.seniority+1;
    (*child)->father=(*father);
    int date=(*child)->data.birthday;
    Tree kid1=(*father)->firstChild,kid2=kid1;
    if(kid1==NULL)
    {
        (*father)->firstChild=(*child);
        return OK;
    }
    if(kid1->data.birthday>=date)
    {
        (*child)->nextSibling=kid1;
        (*father)->firstChild=(*child);
        return OK;
    }    
    for(kid1=kid2->nextSibling;kid1!=NULL&&date>kid1->data.birthday;)
    {
        kid2=kid2->nextSibling;
        kid1=kid2->nextSibling;
    }
    (*child)->nextSibling=kid1;
    kid2->nextSibling=(*child);
    return OK;
}

Status DeleteTree(Tree *A)//删除成员
{
    Tree kid;
    if((*A)->father->firstChild==(*A))
        (*A)->father->firstChild=(*A)->nextSibling;
    else
    {
        for(kid=(*A)->father->firstChild;kid->nextSibling!=(*A);)
            kid=kid->nextSibling;
        kid->nextSibling=(*A)->nextSibling;
    }
    (*A)->nextSibling=NULL;
    (*A)->father=NULL;
    system("pause");
    DestroyTree(&(*A));
    return OK;
}

Status DestroyTree(Tree *A)//销毁树
{
    if((*A)==NULL) return ERROR;
    DestroyTree(&((*A)->firstChild));
    DestroyTree(&((*A)->nextSibling));
    free(*A);
    return OK;
}

Status PrintTree(Tree T)//输出家谱
{
	if(T)
    {
		for(int t=1;t<T->data.seniority;t++) printf("     ");
        if(T->data.seniority)
        {
            printf("[%d|",T->data.seniority);
            Birthday(T->data.birthday);
            printf("|%s]\n\n",T->data.name);
        }
		PrintTree(T->firstChild);
		PrintTree(T->nextSibling);
	}
    return OK;
}

Status SaveTree(Tree T)//保存树
{
	if(T)
    {
        if(T->data.seniority) fprintf(fp,"%s,%d,%s,%d,%d,%s,\n",T->data.name,T->data.sex,T->data.spouse,T->data.birthday,T->data.alive,T->father->data.name);
		SaveTree(T->firstChild);
		SaveTree(T->nextSibling);
	}
    return OK;
}

Status CheckBirthday(int birthday)//判断生日合法性
{
    int year,month,day;
    char months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    year=birthday/10000;
    month=(birthday-year*10000)/100;
    day=birthday%100;           
    if(month==2) (((year%4==0)&&(year%100!=0))||(year%400==0))?months[1]+=1:months[1];
    if(month>12||month<1||day>months[month-1]||day<1) return ERROR;
    return OK;
}

Status Birthday(int birthday)//转换为生日格式
{
    int year,month,day;
    year=birthday/10000;
    month=(birthday-year*10000)/100;
    day=birthday%100;
    printf("%d年%d月%d日",year,month,day);
    return OK;
}