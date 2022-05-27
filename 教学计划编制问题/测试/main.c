#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct EdgeNode    //�ڽӱ���
{
    int adjVex;            //�ڽӵ���  
    struct EdgeNode *next; //ָ����һ���ڱ߽ڵ��ָ����
}EdgeNode;

typedef struct CNode       //�γ̱�ڵ�
{
    char classNum[3+1];    //�γ̱��
    int credit;            //�γ�ѧ��
    int inDegree;          //�γ����
    EdgeNode *firstEdge;   //ָ���ڽӱ��һ���ڱ߽ڵ��ָ����
}ClassNode;

typedef struct Term        //ѧ����Ϣ
{
    int termNum;           //ѧ����
    int maxCredit;   	   //ÿѧ��ѧ������
}Term;

typedef struct AlGraph     //����ͼ
{
	ClassNode *courses;    //�ڽӱ���
	int vexNum;            //�ڵ���
	int arcNum;			   //����
	Term *message;         //ѧ����γ���Ϣ
}AlGraph;

typedef struct List        //���Ա�
{
 	int data[100];         //����
 	int length;            //����
}List;
int a;

int Create(AlGraph* G)   //��������ͼ
{
	int i,j,s,count;
	char a,name[30],str[4];
	FILE *fp;
	printf("<<<---��ѧ�ƻ�����ϵͳ--->>>\n");
	A:printf("������γ̱��ļ���:");
	fflush(stdin);gets(name);strcat(name,".txt");
	if((fp=fopen(name, "r"))==NULL) {printf("���ļ�������%s,����������!\n",name);goto A;}
	G->message=(Term *)malloc(sizeof(Term));
	G->courses=(ClassNode *)malloc(sizeof(ClassNode)*G->vexNum);
	fscanf(fp,"%d%d%d\n\n",&G->message->termNum,&G->message->maxCredit,&G->vexNum);
	if(G->message->termNum>12||G->message->termNum<1||G->message->maxCredit<1||G->vexNum>100||G->vexNum<1)
		{printf("���볬����Χ!\n");return 0;}
	for(i=0;i<G->vexNum;i++)   //��ʼ��
	{
		fscanf(fp,"%s",G->courses[i].classNum);
		G->courses[i].firstEdge=NULL;
		G->courses[i].inDegree=0;
	}
	for(i=0;i<G->vexNum;i++)
	{	
		fscanf(fp,"%d",&G->courses[i].credit);   //��ȡ�γ̱�ź�ѧ��
		while(fgetc(fp)!='\n')   //�����Ⱦ����������ڽӱ���
		{
			fscanf(fp,"%s",str);
			s=(strlen(str)==2)?str[1]-'1':(str[1]-'0')*10+str[2]-'1';   //�γ��ַ���ת����
			if(s<0||s>G->vexNum) {printf("%s�������!\n",G->courses[i].classNum);return 0;}
			EdgeNode *p=(EdgeNode*)malloc(sizeof(EdgeNode));   //�����ڽӱ���
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

void Add(List *L,int  data)//���Ԫ��
{
   	L->data[L->length++]=data;
}

void Remove(List *L,int number)//ɾ��Ԫ��
{
  	for(int i=number-1;i<L->length;i++)
   		L->data[i]=L->data[i+1];
  	L->length--;
}

void Insert(List *L,int locate,int object)//����Ԫ��
{
	int i;
	for(i=L->length;i>=locate-1;i--)
   		L->data[i+1]=L->data[i];
  	L->data[i+1]=object;
  	L->length++;
}

int TopSort(ClassNode g[],int n,ClassNode *temp,int type)   //��������
{
	int i,j,k,m=0,gd[n],x;
	for(i=0;i<n;i++) gd[i]=g[i].inDegree;
	List degree;
    degree.length=0;
	EdgeNode* p;
	if(type==1||type>=a/2) for(i=n-1;i>=0;i--) {if(gd[i]==0) Add(&degree,i);}
	else for(i=0;i<n;i++) {if(gd[i]==0) Add(&degree,i);}
	printf("\n%d������������Ϊ:",type);
	while(degree.length!=0)
	{
		if(type<3) x=0;
		else x=rand()%degree.length;
		j=degree.data[x];   //��������ĳ��Ԫ��
		Remove(&degree,x+1);
		printf("%s  ",g[j].classNum);
		temp[m++]=g[j];
		for(p=g[j].firstEdge;p;p=p->next)   //ɾ������j�����г���
		{
			k=p->adjVex;
			if(!(--gd[k]))   //������k���Ϊ����������
			{
				if(type==2) Insert(&degree,1,k);
				else if(type<a/2) Add(&degree,k); 
				else Insert(&degree,1,k);
			}
		}
	}
	if(m<n) {printf("AOV���л�·,�޷���ƽ�ѧ�ƻ�!");return 0;}
	return 1;
}

void SortA(ClassNode* t,Term* s,int classNum)   //���Ȱ��ſγ�
{
    char name[30];
	printf("�������ѧ�ƻ������ļ���:");
	fflush(stdin);gets(name);strcat(name,".csv");
	FILE *fp=fopen(name,"w");
	printf("���Ȱ��ſγ̵ķ�������:");
	fprintf(fp,"ѧ��,\t,�γ�");
	int i,j,b,c=0;   //��������γ���Ϣ
	for(i=0;i<s->termNum;i++)
	{
		b=0;   //�ۼ�ÿѧ��ѧ��
		printf("\n��%d��ѧ�ڵĿγ�Ϊ:",i+1);
		fprintf(fp,"\n��%dѧ��,\t,",i+1);
		for(j=0;j<classNum/s->termNum;j++)
		{
			if(b+t[c].credit<=s->maxCredit)   //�ж��Ƿ񳬹����ѧ��
			{
				if(c==classNum) break;
				printf("%s  ",t[c].classNum);
				fprintf(fp,"%s,",t[c].classNum);
				b=b+t[c].credit;   //ѧ���ۼ�
				c++;   //ָ����һ�γ�
			}
		}
		if(i<classNum%s->termNum)   //����ƽ�������Ŀγ�
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

void SortB(ClassNode* t,Term *s,int classNum)   //���찲�ſγ�
{
	char name[30];
	printf("�������ѧ�ƻ������ļ���:");
	fflush(stdin);gets(name);strcat(name,".csv");
	FILE *fp=fopen(name,"w");
	printf("���찲�ſγ̵ķ�������:");
	fprintf(fp,"ѧ��,\t,�γ�");
	int i,b,c=0;		
	for(i=0;i<s->termNum;i++)
	{
		b=0;   //�ۼ�ÿѧ��ѧ��
		printf("\n��%d��ѧ�ڵĿγ�Ϊ:",i+1);
		fprintf(fp, "\n��%dѧ��,\t,",i+1);
		while(b+t[c].credit<=s->maxCredit)   //�ж��Ƿ񳬹����ѧ��
		{
			if (c==classNum)break;
			printf("%s  ",t[c].classNum);		//����γ�
			fprintf(fp,"%s,",t[c].classNum);
			b=b+t[c].credit;   //ѧ���ۼ�
			c++;   //ָ����һ�γ�
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
		B:printf("��������������������:");scanf("%d",&a);
		if(a<2||a>10) {printf("���볬����Χ,����������!\n");goto B;}
		x[0]=TopSort(G.courses,G.vexNum,class[0],i);
		if(x[0])
		{
			for(i=1;i<a;i++)
				x[i]=TopSort(G.courses,G.vexNum,class[i],i+1);
			C:printf("\n��ѡ����������:");scanf("%d",&b);
			if(b<1||b>a) {printf("�������,����������!");goto C;}
			b--;
    		printf("\n1.���Ȱ��ſγ�\n2.���찲�ſγ�\n");
			D:printf("��ѡ���ѧ�ƻ���������:");
    		scanf("%d",&choice);
			if(choice!=0&&choice!=1) {printf("�������,����������!\n");goto D;}
    		(choice==1)?SortA(class[b],G.message,G.vexNum):SortB(class[b],G.message,G.vexNum);
			printf("\n�Ƿ�鿴��һ�ֱ�������(y|n):");fflush(stdin);scanf("%c",&choose);
			if(choose=='y')
			{	 
				choice=1-choice;
				(choice==1)?SortA(class[b],G.message,G.vexNum):SortB(class[b],G.message,G.vexNum);
			}
		}
	}
	else printf("¼����Ϣ����!");
	printf("\n�Ƿ��������(y|n):");fflush(stdin);scanf("%c",&choose);
	if(choose=='y') {system("cls");goto A;}
	printf(">>>------<<<\n�ڴ������´�ʹ��,�ٻ�!\n");system("pause");
}