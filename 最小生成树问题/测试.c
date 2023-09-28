#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VertexType int
#define VRType int
#define InfoType char
#define MAX_VERtEX_NUM 30   //��󶥵����
#define INFINITY 99999      //���ֵ

typedef struct
{
    VRType adj;          //�����ϵ 1|0��ʾ�Ƿ�����
    InfoType *info;      //�û������Ϣ��ָ��
}ArcCell,AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];
typedef struct
{
    VertexType vexs[MAX_VERtEX_NUM];   //��������
    AdjMatrix arcs;                    //�ڽӾ���
    int vexnum,arcnum;                 //ͼ�ĵ�ǰ�������ͻ���
}MGraph;
typedef struct
{
    VertexType adjvex;      //Ȩֵ��С�ߵ���ʼ��
    VRType lowcost;         //�ñ�Ȩֵ
}closedge[MAX_VERtEX_NUM];

closedge close;//�������飬����ÿ��ɸѡ��Ȩֵ��С�ı�
int v[100][3]={0,0,0};//�洢����Ϣ

int LocateVex(MGraph G,VertexType v)//�ж϶����ڶ�ά�����е�λ��
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==v) return i;
    }
    return -1;
}

void Create(MGraph *G)//����������
{
    int i,j,k,v1,v2,w,m,n,flag;
    A:printf("�����붥����:");scanf("%d",&(G->vexnum));
    if(G->vexnum<=1||G->vexnum>30) {printf("�������������!\n");goto A;}//����������Ϸ�
    B:flag=0;
    for(i=0;i<G->vexnum;i++)//���붥��
    {
        printf("�������%d������:",i+1);
        scanf("%d",&(G->vexs[i]));
        for(j=0;j<G->vexnum;j++)//�����ʼ��
        {
            G->arcs[i][j].adj=INFINITY;
            G->arcs[i][j].info=NULL;
        }
    }
    for(i=0;i<G->vexnum;i++)//���������ظ�
    {
        for(j=i+1;j<G->vexnum;j++)
        {
            if(G->vexs[i]==G->vexs[j]) {flag=1;break;}
        }
    }
    if(flag) {printf("���������ظ�!\n");goto B;}
    C:printf("�����뻡��:");scanf("%d",&(G->arcnum));
    if(G->arcnum<1||G->arcnum>G->vexnum*(G->vexnum-1)/2) {printf("�������Ϸ�!\n");goto C;}//�������Ϸ�
    printf("���������뻡(����A ����B ��ֵ):\n");
    for(k=0;k<G->arcnum;k++)
    {
        D:flag=0;
        printf("��%d����:",k+1);
        scanf("%d %d %d",&v1,&v2,&w);
        for(i=0;i<G->arcnum;i++)//��������
        {
            if(v1==v[i][0]&&v2==v[i][1]||v1==v[i][1]&&v2==v[i][0])
            {
                flag=1;
                break;
            }
        }
        if(flag) {printf("%d-%d�Ļ�������!\n",v1,v2);goto D;}
        if(w<=0) {printf("��ֵ�������!\n");goto D;}//��ֵ����
        m=LocateVex(*G,v1);n=LocateVex(*G,v2);
        if(m==-1||n==-1) {printf("�����������!\n");goto D;}
        if(m==n) {printf("����%d�ظ�!\n",v1);goto D;}
        v[k][0]=v1;v[k][1]=v2;v[k][2]=w;
        G->arcs[n][m].adj=w;
        G->arcs[m][n].adj=w;
    }
}

void create(MGraph *G)//�Զ�����������
{
    int a,b,i,j,k=0,m,n;
    A:printf("�����붥����:");scanf("%d",&(G->vexnum));
    if(G->vexnum<=1||G->vexnum>30) {printf("�������������!\n");goto A;}//����������Ϸ�
    B:printf("������������������ֵ:");scanf("%d",&b);
    if(b<=0||b>INFINITY) {printf("���볬����Χ!");goto B;}
    for(i=0;i<G->vexnum;i++)
    {
        G->vexs[i]=i+1;
        for(j=0;j<G->vexnum;j++)//�����ʼ��
        {
            G->arcs[i][j].adj=INFINITY;
            G->arcs[i][j].info=NULL;
        }
    }
    G->arcnum=G->vexnum*(G->vexnum-1)/2;
    for(i=1;i<=G->vexnum;i++)
    {
        for(j=i+1;j<=G->vexnum;j++)
        {
            a=rand()%(b+1)+1;     //����1~b֮����������
            m=LocateVex(*G,i);n=LocateVex(*G,j);
            v[k][0]=i;v[k][1]=j;v[k][2]=a;k++;
            G->arcs[n][m].adj=a;
            G->arcs[m][n].adj=a;
        }
    }
}

int minimum(MGraph G,closedge c)//�Ӹ����������ҳ�Ȩֵ��С�ıߵ������±�
{
    int i,min=INFINITY,index=-1;
    for(i=0;i<G.vexnum;i++) 
    {
        if(c[i].lowcost>0&&c[i].lowcost<min)
        {
            min=close[i].lowcost;
            index=i;
        }
    }
    return index;
}

void MiniSpanTree_PRIM(MGraph G,VertexType u)//����ķ�㷨
{
    int i,j,k,m,num=G.arcnum,n[G.vexnum-1][2];
    char name[100],file[100],command[200]="dot ";
    printf("�������ļ���:");
    fflush(stdin);gets(name);strcpy(file,name);
    strcat(file,".png");strcat(name,".gv");
    FILE *fp=fopen(name,"w+");
    fprintf(fp,"graph\n{\n//best\n");
    k=LocateVex(G,u);
    for(i=0;i<G.vexnum;i++)//���������ʼ��
    {
        if(i!=k)
        {
            close[i].adjvex=k;
            close[i].lowcost=G.arcs[k][i].adj;
        }
    }
    close[k].lowcost=0;//��ʼ
    for(i=1;i<G.vexnum;i++)//ѡ������G.vexnum-1������
    {
        k=minimum(G,close);//���T����һ���ڵ㣺��k����
        m=close[k].adjvex;
        n[i-1][0]=G.vexs[m];n[i-1][1]=G.vexs[k];
        fprintf(fp,"v%d--v%d [label=\"%d\" color=blue];\n",G.vexs[m],G.vexs[k],G.arcs[m][k].adj);//����������ı�
        close[k].lowcost=0;//��k���㲢��U��
        for(j=0;j<G.vexnum;j++)
        {
            if(G.arcs[k][j].adj<close[j].lowcost)//�¶��㲢��U������ѡ����С��
            {
                close[j].adjvex=k;
                close[j].lowcost=G.arcs[k][j].adj;
            }
        }
    }
    for(i=0;i<num;i++)//ɸѡ������
    {
        for(j=0;j<G.vexnum-1;j++)
        {
            if(v[i][0]==n[j][0]&&v[i][1]==n[j][1]||v[i][0]==n[j][1]&&v[i][1]==n[j][0])
            {
                for(m=i;m<num;m++)
                {
                    for(k=0;k<3;k++)
                        v[m][k]=v[m+1][k];
                }
                num--;
                i--;
                break;
            }
        }
    }
    fprintf(fp,"//other\n");
    for(i=0;i<num;i++)//���������
        fprintf(fp,"v%d--v%d [label=\"%d\"];\n",v[i][0],v[i][1],v[i][2]);
    printf("�ɹ�������С������!\n");
    fprintf(fp,"}");
    fclose(fp);
    strcat(command,name);strcat(command," -Ksfdp -Tpng -o ");strcat(command,file);
    system(command);
}

int main()
{
    int choice;
    MGraph G;
    system("color F1");
    A:system("cls");
    printf("--��С������--\n1.�ֶ�����\n2.һ������\n0.�˳�����\nѡ����:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:Create(&G);MiniSpanTree_PRIM(G,1);system("pause");goto A;
        case 2:create(&G);MiniSpanTree_PRIM(G,1);system("pause");goto A;
        case 0:break;
        default:goto A;
    }
    system("pause");
}