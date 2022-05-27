#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VertexType int
#define VRType int
#define InfoType char
#define MAX_VERtEX_NUM 30   //最大顶点个数
#define INFINITY 99999      //最大值

typedef struct
{
    VRType adj;          //顶点关系 1|0表示是否相邻
    InfoType *info;      //该弧相关信息的指针
}ArcCell,AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];
typedef struct
{
    VertexType vexs[MAX_VERtEX_NUM];   //顶点向量
    AdjMatrix arcs;                    //邻接矩阵
    int vexnum,arcnum;                 //图的当前顶点数和弧数
}MGraph;
typedef struct
{
    VertexType adjvex;      //权值最小边的起始点
    VRType lowcost;         //该边权值
}closedge[MAX_VERtEX_NUM];

closedge close;//辅助数组，用于每次筛选出权值最小的边
int v[100][3]={0,0,0};//存储弧信息

int LocateVex(MGraph G,VertexType v)//判断顶点在二维数组中的位置
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==v) return i;
    }
    return -1;
}

void Create(MGraph *G)//创建无向网
{
    int i,j,k,v1,v2,w,m,n,flag;
    A:printf("请输入顶点数:");scanf("%d",&(G->vexnum));
    if(G->vexnum<=1||G->vexnum>30) {printf("顶点数输入错误!\n");goto A;}//顶点个数不合法
    B:flag=0;
    for(i=0;i<G->vexnum;i++)//输入顶点
    {
        printf("请输入第%d个顶点:",i+1);
        scanf("%d",&(G->vexs[i]));
        for(j=0;j<G->vexnum;j++)//矩阵初始化
        {
            G->arcs[i][j].adj=INFINITY;
            G->arcs[i][j].info=NULL;
        }
    }
    for(i=0;i<G->vexnum;i++)//顶点输入重复
    {
        for(j=i+1;j<G->vexnum;j++)
        {
            if(G->vexs[i]==G->vexs[j]) {flag=1;break;}
        }
    }
    if(flag) {printf("顶点输入重复!\n");goto B;}
    C:printf("请输入弧数:");scanf("%d",&(G->arcnum));
    if(G->arcnum<1||G->arcnum>G->vexnum*(G->vexnum-1)/2) {printf("弧数不合法!\n");goto C;}//弧数不合法
    printf("请依次输入弧(顶点A 顶点B 弧值):\n");
    for(k=0;k<G->arcnum;k++)
    {
        D:flag=0;
        printf("第%d条弧:",k+1);
        scanf("%d %d %d",&v1,&v2,&w);
        for(i=0;i<G->arcnum;i++)//弧已输入
        {
            if(v1==v[i][0]&&v2==v[i][1]||v1==v[i][1]&&v2==v[i][0])
            {
                flag=1;
                break;
            }
        }
        if(flag) {printf("%d-%d的弧已输入!\n",v1,v2);goto D;}
        if(w<=0) {printf("弧值输入错误!\n");goto D;}//弧值非正
        m=LocateVex(*G,v1);n=LocateVex(*G,v2);
        if(m==-1||n==-1) {printf("顶点输入错误!\n");goto D;}
        if(m==n) {printf("顶点%d重复!\n",v1);goto D;}
        v[k][0]=v1;v[k][1]=v2;v[k][2]=w;
        G->arcs[n][m].adj=w;
        G->arcs[m][n].adj=w;
    }
}

void create(MGraph *G)//自动创建无向网
{
    int a,b,i,j,k=0,m,n;
    A:printf("请输入顶点数:");scanf("%d",&(G->vexnum));
    if(G->vexnum<=1||G->vexnum>30) {printf("顶点数输入错误!\n");goto A;}//顶点个数不合法
    B:printf("请输入生成随机数最大值:");scanf("%d",&b);
    if(b<=0||b>INFINITY) {printf("输入超出范围!");goto B;}
    for(i=0;i<G->vexnum;i++)
    {
        G->vexs[i]=i+1;
        for(j=0;j<G->vexnum;j++)//矩阵初始化
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
            a=rand()%(b+1)+1;     //生成1~b之间的随机整数
            m=LocateVex(*G,i);n=LocateVex(*G,j);
            v[k][0]=i;v[k][1]=j;v[k][2]=a;k++;
            G->arcs[n][m].adj=a;
            G->arcs[m][n].adj=a;
        }
    }
}

int minimum(MGraph G,closedge c)//从辅助数组中找出权值最小的边的数组下标
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

void MiniSpanTree_PRIM(MGraph G,VertexType u)//普里姆算法
{
    int i,j,k,m,num=G.arcnum,n[G.vexnum-1][2];
    char name[100],file[100],command[200]="dot ";
    printf("请输入文件名:");
    fflush(stdin);gets(name);strcpy(file,name);
    strcat(file,".png");strcat(name,".gv");
    FILE *fp=fopen(name,"w+");
    fprintf(fp,"graph\n{\n//best\n");
    k=LocateVex(G,u);
    for(i=0;i<G.vexnum;i++)//辅助数组初始化
    {
        if(i!=k)
        {
            close[i].adjvex=k;
            close[i].lowcost=G.arcs[k][i].adj;
        }
    }
    close[k].lowcost=0;//初始
    for(i=1;i<G.vexnum;i++)//选择其余G.vexnum-1个顶点
    {
        k=minimum(G,close);//求出T的下一个节点：第k顶点
        m=close[k].adjvex;
        n[i-1][0]=G.vexs[m];n[i-1][1]=G.vexs[k];
        fprintf(fp,"v%d--v%d [label=\"%d\" color=blue];\n",G.vexs[m],G.vexs[k],G.arcs[m][k].adj);//输出生成树的边
        close[k].lowcost=0;//第k顶点并入U集
        for(j=0;j<G.vexnum;j++)
        {
            if(G.arcs[k][j].adj<close[j].lowcost)//新顶点并入U后重新选择最小边
            {
                close[j].adjvex=k;
                close[j].lowcost=G.arcs[k][j].adj;
            }
        }
    }
    for(i=0;i<num;i++)//筛选其他弧
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
    for(i=0;i<num;i++)//输出其他弧
        fprintf(fp,"v%d--v%d [label=\"%d\"];\n",v[i][0],v[i][1],v[i][2]);
    printf("成功生成最小生成树!\n");
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
    printf("--最小生成树--\n1.手动输入\n2.一劳永逸\n0.退出程序\n选择功能:");
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