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
}Status;//枚举类型返回值

typedef struct Member
{
    char name[20];//姓名
    int sex;//性别:1为男性 0为女性
    char spouse[20];//配偶姓名  
    int seniority;//辈分
    int birthday;//生日
    int alive;//是否在世:1为在世 0为过世
}Member;//每个家庭成员的信息库

typedef struct TNode
{
    Member data;
    struct TNode *firstChild,*nextSibling,*father;
}TNode,*Tree,*Forest;//二叉树结构——孩子兄弟表示法 

FILE *fp;
Forest T;
Tree A,B;
//二叉树函数
Status InitTree(Tree *A);//创建家谱树
Status SearchTree(Forest T,char name[20],Tree *B);//搜索成员姓名
Status InsertTree(Tree *father,Tree *child);//插入新成员
Status DeleteTree(Tree *A);//删除成员
Status DestroyTree(Tree *A);//销毁树
Status PrintTree(Tree T);//输出家谱
Status SaveTree(Tree T);//保存树
Status CheckBirthday(int birthday);//判断生日合法性
Status Birthday(int birthday);//转换为生日格式
//功能函数
Status Entry();//录入家谱
Status Insert();//添加成员
Status Search();//查找成员
Status Delete();//删除成员
Status Change();//修改成员信息
Status Edit(Tree *B,Forest T);//修改成员信息
Status Show(Tree *A);//显示成员信息
Status Out();//存储家谱