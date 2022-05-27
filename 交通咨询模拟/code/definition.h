#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<malloc.h>
#include<conio.h>
#include<windows.h>
#include<shellapi.h>
#define MAX 700
#define INF 0x3f3f3f3f
//枚举类型返回值
typedef int Status;
//城市信息
typedef struct 
{
    double lng;      //经度
    double lat;      //纬度
    char name[20];   //城市名
}City;
//图
typedef struct 
{
    int citynum;               //城市数
    City city[MAX];            //城市信息
    int timeEdges[MAX][MAX];   //时间边(秒)
    int costEdges[MAX][MAX];   //费用边(元)
}Graph;
//city.c
Status enterCity(Graph *G);//录入城市信息
Status saveCity(Graph *G);//保存城市信息
Status locateCity(Graph *G,char name[]);//定位城市
Status createGraph(Graph *G);//创建图
Status saveGraph(Graph *G);//保存图
//admin.c
Status admin(Graph *G);//密码登录功能
Status adminFun(Graph *G);//管理员模式
Status addCity(Graph *G);//添加城市
Status deleteCity(Graph *G);//删除城市
Status editRoute(Graph *G);//编辑交通路线
Status findRoute(Graph *G);//查看城市的所有直达路线
//function.c
Status inquire(Graph *G);//查询功能
Status bestRoute(Graph *G,int city1,int city2,int flag);//最优路线
Status floyd(int n,int cost[][MAX]);//弗洛伊德算法

FILE *fp;  //文件指针
int weight[MAX][MAX]={0},path[MAX][MAX]={0};//权值矩阵和路径矩阵，便于实现算法