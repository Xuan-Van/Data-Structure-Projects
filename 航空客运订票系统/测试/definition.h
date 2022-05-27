#ifndef DEFINITION
#define DEFINITION
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
FILE *fp;//�ļ�ָ��
typedef int Status;//������װ

typedef struct passenger
{
    char name[50];//����
    char ID[50];//���֤����
    char grade;//�ɻ���λ ͷ�Ȳ�F,�����C,���ò�Y
}Client;//�˿���Ϣ

typedef struct node
{
    Client C;
    struct node *next;
}node,*List;//�˿�����

typedef struct
{
    List front;
    List rear;
}Queue;//�򲹶���

typedef struct
{
    int number;//���
    char flightNum[10];//�����
    char planeNum[10];//�ɻ���
    char departure[20];//ʼ��վ
    char destination[20]; //Ŀ�ĵ�
    char company[20];//���չ�˾
    char airport[20];//��ɻ���
    char nextairport[20];//�������
    int price;//���òջ���Ʊ�ۣ�ͷ�Ȳռ۸�Ϊ����Ʊ��150%������ռ۸�Ϊ����Ʊ�۵�130%��
    int month;
    int day;
    int hour;//���ʱ��
    int min;
    int nexthour;//�ִ�ʱ��
    int nextmin;
    int date;//����
    int capacity;//�ؿ��� һ�����ߵĲ�λ����0.1��ͷ�Ȳգ�0.2������գ�����Ϊ���ò�
    int F;//ͷ�Ȳ���Ʊ��
    int C;//�������Ʊ��
    int Y;//���ò���Ʊ��
    List L;//�˿�����
    Queue Q;//�Ⱥ��油����
}Airline;//������Ϣ

//List��غ���
Status Create(List *B);//�����˿�����
Status OrderInSert(List B,Client E);//�ͻ���Ϣ��������
Status Search(List B,char id[],Client *E);//��ѯ�ͻ���Ʊ��Ϣ
Status Delete(List B,Client E);//�����Ƴ���Ʊ��Ϣ
Status EntryList();//¼��ͻ�����
Status OutList();//�洢�ͻ�����

//Queue��غ���
Status InitQueue(Queue *Q);//����һ���ն���
Status EnQueue(Queue *Q,Client E);//�����βԪ��
Status DeQueue(Queue *Q,Client *E);//ɾ����ͷԪ��
Status QueueEmpty(Queue *Q);//�ж϶���Ϊ��
Status CheckQueue(Queue *Q,char space,Client *E);//�����Ʊ�Ƿ�����򲹿ͻ����󣬲��ŶӺ�

//Airline��غ���
int airnum;//������
Airline transit[2][1000]={0};//��ת������ſ�
Airline A[10000]={0};//������Ϣ��
char *week[7]={"������","����һ","���ڶ�","������","������","������","������"};//����
Status EntryAirline();//¼�뺽����Ϣ
Status OutAirline();//�洢������Ϣ
Status PrintAirline(Airline *A);//��ӡ������Ϣ
Status AirlineReady();//�������߶�Ӧ�����Ա�Ͷ���
Status AirlineBack(Airline *B,char C);//��Ʊ��λ

//inquire����
Status Query();//���߲�ѯ
Status Booking(char place1[15],char place2[15]);//��Ʊ
Status Number();//ѡ�����
Status PlaceOrder(Airline *B);//�µ�
Status FillBlank(Client *C);//�ͻ���Ϣ¼��ϵͳ
Status Transit(char place1[],char place2[],int m,int n);//������ת
Status Day(Airline *B,Airline *D);//�ж���תʱ����ʱ������ʱ���Ƿ���ͬһ��
Status MonthDays(int month,int day);//����������һ���е�����
Status TransitNum(int k);//��ת��Ʊ
Status Conflict(char id[],Airline *B);//�ж϶�Ʊʱ���Ƿ��ͻ
Status DayConflit(Airline *B,Airline *D);//�ж�ʱ���ͻ
Status TranMin(Airline *B,int min[2]);//ʱ��ת������

//refund����
Status Information();//��ʾ��Ϣ
Status Refund(char id[]);//��Ʊ
#endif