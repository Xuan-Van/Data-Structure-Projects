#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//枚举类型返回值
typedef enum status
{
	OK=1,
	ERROR=0,
}Status;
//赫夫曼树节点存储结构
typedef struct tnode
{
	char character;//字符
	int weight;//权重
	int parent,lchild,rchild;
}HuffmanTree;
//赫夫曼编码表结构 
typedef struct cnode     
{
	int start;
	char bits[1000];
	char character;
}HuffmanCode;
//定义相关变量
char huffmanCode[1000];//代码字符串
char txtCode[1000];//译文字符串
char name[100];//文件名字符串
FILE *fp;//文件指针
char character[]={'\0',' ','A','B','C','D','E','F','G','H','I','J','K',
				  'L','M','N','O','P','Q','R','S','T','U','V','W','X',
				  'Y','Z',',','.','?',':',';','!'};//字符集
int weight[]={0};//权重
//结构库函数
Status CreateTree(HuffmanTree T[],int leafNum);//建立赫夫曼树
Status CreateCode(HuffmanCode code[],HuffmanTree T[],int leafNum);//建立赫夫曼编码
Status CodingHuffman(HuffmanCode code[],HuffmanTree T[],char enter[],int leafNum);//字符串编码
Status DecodingHuffman(HuffmanCode code[],HuffmanTree T[],char s[],int leafNum);//赫夫曼译码
Status PrintTree(HuffmanTree T[],int root,int type,int level,char filename[]);//打印树状图
//功能库函数
Status Entry();//读入赫夫曼树
Status Save();//保存赫夫曼树
Status Init();//初始化
Status Coding(HuffmanCode code[],HuffmanTree T[],int leafNum);//编码
Status Decoding(HuffmanCode code[],HuffmanTree T[],int leafNum);//译码
Status PrintCode();//打印代码
Status PrintHuffmanTree(HuffmanTree T[],int leafNum);//打印赫夫曼树
Status Convert(char s[]);//字母中小写转大写
Status WriteBit(char code[]);//字符串转bit
Status ReadBit();//bit转字符串