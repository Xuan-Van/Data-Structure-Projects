#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

typedef enum status
{             
    TRUE,
    FALSE,
    OK,
    ERROR,
    SUCCESS,
    OVERFLOW,
    EMPTY
}Status;//ö�����ͷ���ֵ

typedef struct Member
{
    char name[20];//����
    int sex;//�Ա�:1Ϊ���� 0ΪŮ��
    char spouse[20];//��ż����  
    int seniority;//����
    int birthday;//����
    int alive;//�Ƿ�����:1Ϊ���� 0Ϊ����
}Member;//ÿ����ͥ��Ա����Ϣ��

typedef struct TNode
{
    Member data;
    struct TNode *firstChild,*nextSibling,*father;
}TNode,*Tree,*Forest;//�������ṹ���������ֵܱ�ʾ�� 

FILE *fp;
Forest T;
Tree A,B;
//����������
Status InitTree(Tree *A);//����������
Status SearchTree(Forest T,char name[20],Tree *B);//������Ա����
Status InsertTree(Tree *father,Tree *child);//�����³�Ա
Status DeleteTree(Tree *A);//ɾ����Ա
Status DestroyTree(Tree *A);//������
Status PrintTree(Tree T);//�������
Status SaveTree(Tree T);//������
Status CheckBirthday(int birthday);//�ж����պϷ���
Status Birthday(int birthday);//ת��Ϊ���ո�ʽ
//���ܺ���
Status Entry();//¼�����
Status Insert();//��ӳ�Ա
Status Search();//���ҳ�Ա
Status Delete();//ɾ����Ա
Status Change();//�޸ĳ�Ա��Ϣ
Status Edit(Tree *B,Forest T);//�޸ĳ�Ա��Ϣ
Status Show(Tree *A);//��ʾ��Ա��Ϣ
Status Out();//�洢����