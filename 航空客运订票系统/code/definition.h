#ifndef DEFINITION
#define DEFINITION
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
FILE *fp;//文件指针
typedef int Status;//函数封装

typedef struct passenger
{
    char name[50];//姓名
    char ID[50];//身份证号码
    char grade;//飞机舱位 头等舱F,商务舱C,经济舱Y
}Client;//乘客信息

typedef struct node
{
    Client C;
    struct node *next;
}node,*List;//乘客名单

typedef struct
{
    List front;
    List rear;
}Queue;//候补队列

typedef struct
{
    int number;//序号
    char flightNum[10];//航班号
    char planeNum[10];//飞机号
    char departure[20];//始发站
    char destination[20]; //目的地
    char company[20];//航空公司
    char airport[20];//起飞机场
    char nextairport[20];//降落机场
    int price;//经济舱基础票价（头等舱价格为基础票价150%，商务舱价格为基础票价的130%）
    int month;
    int day;
    int hour;//起飞时间
    int min;
    int nexthour;//抵达时间
    int nextmin;
    int date;//星期
    int capacity;//载客量 一条航线的舱位中有0.1的头等舱，0.2的商务舱，其余为经济舱
    int F;//头等舱余票量
    int C;//商务舱余票量
    int Y;//经济舱余票量
    List L;//乘客名单
    Queue Q;//等候替补队列
}Airline;//航线信息

//List相关函数
Status Create(List *B);//创建乘客名单
Status OrderInSert(List B,Client E);//客户信息放入名单
Status Search(List B,char id[],Client *E);//查询客户订票信息
Status Delete(List B,Client E);//名单移除订票信息
Status EntryList();//录入客户名单
Status OutList();//存储客户名单

//Queue相关函数
Status InitQueue(Queue *Q);//构造一个空队列
Status EnQueue(Queue *Q,Client E);//插入队尾元素
Status DeQueue(Queue *Q,Client *E);//删除队头元素
Status QueueEmpty(Queue *Q);//判断队列为空
Status CheckQueue(Queue *Q,char space,Client *E);//检查退票是否满足候补客户需求，并排队候补

//Airline相关函数
int airnum;//航线数
Airline transit[2][1000]={0};//中转航班序号库
Airline A[10000]={0};//航线信息库
char *week[7]={"星期天","星期一","星期二","星期三","星期四","星期五","星期六"};//星期
Status EntryAirline();//录入航线信息
Status OutAirline();//存储航线信息
Status PrintAirline(Airline *A);//打印航线信息
Status AirlineReady();//构建航线对应的线性表和队列
Status AirlineBack(Airline *B,char C);//退票后补位

//inquire函数
Status Query();//航线查询
Status Booking(char place1[15],char place2[15]);//订票
Status Number();//选择序号
Status PlaceOrder(Airline *B);//下单
Status FillBlank(Client *C);//客户信息录入系统
Status Transit(char place1[],char place2[],int m,int n);//订单中转
Status Day(Airline *B,Airline *D);//判断中转时到达时间和起飞时间是否在同一天
Status MonthDays(int month,int day);//计算日期在一年中的天数
Status TransitNum(int k);//中转订票
Status Conflict(char id[],Airline *B);//判断订票时间是否冲突
Status DayConflit(Airline *B,Airline *D);//判断时间冲突
Status TranMin(Airline *B,int min[2]);//时间转换分钟

//refund函数
Status Information();//显示信息
Status Refund(char id[]);//退票
#endif