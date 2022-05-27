#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct EdgeNode    //邻接表结点
{
    int adjVex;            //邻接点域  
    struct EdgeNode *next; //指向下一个邻边节点的指针域
}EdgeNode;

typedef struct CNode       //课程表节点
{
    char classNum[3+1];    //课程编号
    int credit;            //课程学分
    int inDegree;          //课程入度
    EdgeNode *firstEdge;   //指向邻接表第一个邻边节点的指针域
}ClassNode;

typedef struct Term        //学期信息
{
    int termNum;           //学期数
    int maxCredit;   	   //每学期学分上限
}Term;

typedef struct AlGraph     //有向图
{
	ClassNode *courses;    //邻接表域
	int vexNum;            //节点数
	int arcNum;			   //边数
	Term *message;         //学期与课程信息
}AlGraph;

typedef struct List        //线性表
{
 	int data[100];         //数据
 	int length;            //长度
}List;
int a;

int Create(AlGraph* G)   //创建有向图
{
	int i,j,s,count;
	char a,name[30],str[4];
	FILE *fp;
	printf("<<<---教学计划编制系统--->>>\n");
	A:printf("请输入课程表文件名:");
	fflush(stdin);gets(name);strcat(name,".txt");
	if((fp=fopen(name, "r"))==NULL) {printf("该文件夹下无%s,请重新输入!\n",name);goto A;}
	G->message=(Term *)malloc(sizeof(Term));
	G->courses=(ClassNode *)malloc(sizeof(ClassNode)*G->vexNum);
	fscanf(fp,"%d%d%d\n\n",&G->message->termNum,&G->message->maxCredit,&G->vexNum);
	if(G->message->termNum>12||G->message->termNum<1||G->message->maxCredit<1||G->vexNum>100||G->vexNum<1)
		{printf("输入超出范围!\n");return 0;}
	for(i=0;i<G->vexNum;i++)   //初始化
	{
		fscanf(fp,"%s",G->courses[i].classNum);
		G->courses[i].firstEdge=NULL;
		G->courses[i].inDegree=0;
	}
	for(i=0;i<G->vexNum;i++)
	{	
		fscanf(fp,"%d",&G->courses[i].credit);   //读取课程编号和学分
		while(fgetc(fp)!='\n')   //根据先决条件建立邻接表结点
		{
			fscanf(fp,"%s",str);
			s=(strlen(str)==2)?str[1]-'1':(str[1]-'0')*10+str[2]-'1';   //课程字符串转数字
			if(s<0||s>G->vexNum) {printf("%s输入错误!\n",G->courses[i].classNum);return 0;}
			EdgeNode *p=(EdgeNode*)malloc(sizeof(EdgeNode));   //更新邻接表结点
			p->adjVex=i;
			p->next=G->courses[s].firstEdge; 
			G->courses[s].firstEdge=p;
			G->arcNum++;
		}
	}
    fclose(fp);
	for(i=0;i<G->vexNum;i++)
	{
		for(EdgeNode *p=G->courses[i].firstEdge;p!=NULL;p=p->next) G->courses[p->adjVex].inDegree++;
	}
	return 1;
}

void Add(List *L,int  data)//添加元素
{
   	L->data[L->length++]=data;
}

void Remove(List *L,int number)//删除元素
{
  	for(int i=number-1;i<L->length;i++)
   		L->data[i]=L->data[i+1];
  	L->length--;
}

void Insert(List *L,int locate,int object)//插入元素
{
	int i;
	for(i=L->length;i>=locate-1;i--)
   		L->data[i+1]=L->data[i];
  	L->data[i+1]=object;
  	L->length++;
}

int TopSort(ClassNode g[],int n,ClassNode *temp,int type)   //拓扑排序
{
	int i,j,k,m=0,gd[n],x;
	for(i=0;i<n;i++) gd[i]=g[i].inDegree;
	List degree;
    degree.length=0;
	EdgeNode* p;
	if(type==1||type>=a/2) for(i=n-1;i>=0;i--) {if(gd[i]==0) Add(&degree,i);}
	else for(i=0;i<n;i++) {if(gd[i]==0) Add(&degree,i);}
	printf("\n%d种拓扑排序结果为:",type);
	while(degree.length!=0)
	{
		if(type<3) x=0;
		else x=rand()%degree.length;
		j=degree.data[x];   //输出链表的某个元素
		Remove(&degree,x+1);
		printf("%s  ",g[j].classNum);
		temp[m++]=g[j];
		for(p=g[j].firstEdge;p;p=p->next)   //删除顶点j的所有出边
		{
			k=p->adjVex;
			if(!(--gd[k]))   //若顶点k入度为零则入链表
			{
				if(type==2) Insert(&degree,1,k);
				else if(type<a/2) Add(&degree,k); 
				else Insert(&degree,1,k);
			}
		}
	}
	if(m<n) {printf("AOV网有回路,无法设计教学计划!");return 0;}
	return 1;
}

void SortA(ClassNode* t,Term* s,int classNum)   //均匀安排课程
{
    char name[30];
	printf("请输入教学计划编制文件名:");
	fflush(stdin);gets(name);strcat(name,".csv");
	FILE *fp=fopen(name,"w");
	printf("均匀安排课程的方案如下:");
	fprintf(fp,"学期,\t,课程");
	int i,j,b,c=0;   //用于输出课程信息
	for(i=0;i<s->termNum;i++)
	{
		b=0;   //累计每学期学分
		printf("\n第%d个学期的课程为:",i+1);
		fprintf(fp,"\n第%d学期,\t,",i+1);
		for(j=0;j<classNum/s->termNum;j++)
		{
			if(b+t[c].credit<=s->maxCredit)   //判断是否超过最大学分
			{
				if(c==classNum) break;
				printf("%s  ",t[c].classNum);
				fprintf(fp,"%s,",t[c].classNum);
				b=b+t[c].credit;   //学分累计
				c++;   //指向下一课程
			}
		}
		if(i<classNum%s->termNum)   //加入平均后多余的课程
		{
			if(c==classNum) break;
			printf("%s ",t[c].classNum);
			fprintf(fp,"%s,",t[c].classNum);
			b=b+t[c].credit;
			c++;
		}
	}
	fclose(fp);
}

void SortB(ClassNode* t,Term *s,int classNum)   //尽快安排课程
{
	char name[30];
	printf("请输入教学计划编制文件名:");
	fflush(stdin);gets(name);strcat(name,".csv");
	FILE *fp=fopen(name,"w");
	printf("尽快安排课程的方案如下:");
	fprintf(fp,"学期,\t,课程");
	int i,b,c=0;		
	for(i=0;i<s->termNum;i++)
	{
		b=0;   //累计每学期学分
		printf("\n第%d个学期的课程为:",i+1);
		fprintf(fp, "\n第%d学期,\t,",i+1);
		while(b+t[c].credit<=s->maxCredit)   //判断是否超过最大学分
		{
			if(c==classNum) break;
			printf("%s  ",t[c].classNum);		//输出课程
			fprintf(fp,"%s,",t[c].classNum);
			b=b+t[c].credit;   //学分累计
			c++;   //指向下一课程
		}
	}
	fclose(fp);
}

int main()
{
    A:system("color F1");
	AlGraph G;
    int i=1,flag,b,x[5],choice;
	char choose;
	ClassNode class[11][100];
	flag=Create(&G);
    if(flag)
	{
		B:printf("请输入产生拓扑排序个数:");scanf("%d",&a);
		if(a<2||a>10) {printf("输入超出范围,请重新输入!\n");goto B;}
		x[0]=TopSort(G.courses,G.vexNum,class[0],i);
		if(x[0])
		{
			for(i=1;i<a;i++)
				x[i]=TopSort(G.courses,G.vexNum,class[i],i+1);
			C:printf("\n请选择拓扑排序:");scanf("%d",&b);
			if(b<1||b>a) {printf("输入错误,请重新输入!");goto C;}
			b--;
    		printf("\n1.均匀安排课程\n2.尽快安排课程\n");
			D:printf("请选择教学计划编制类型:");
    		scanf("%d",&choice);
			if(choice!=0&&choice!=1) {printf("输入错误,请重新输入!\n");goto D;}
    		(choice==1)?SortA(class[b],G.message,G.vexNum):SortB(class[b],G.message,G.vexNum);
			printf("\n是否查看另一种编制类型(y|n):");fflush(stdin);scanf("%c",&choose);
			if(choose=='y')
			{	 
				choice=1-choice;
				(choice==1)?SortA(class[b],G.message,G.vexNum):SortB(class[b],G.message,G.vexNum);
			}
		}
	}
	else printf("录入信息有误!");
	printf("\n是否继续操作(y|n):");fflush(stdin);scanf("%c",&choose);
	if(choose=='y') {system("cls");goto A;}
	printf(">>>------<<<\n期待您的下次使用,再会!\n");system("pause");
}