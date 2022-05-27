#include "function.h"
#include "stack.c"
double Opreate(double a,double b,char tr) //对操作数和对应的运算符进行计算并返回结果
{
    switch(tr)
    {
        case'+':return a+b;
        case'-':return a-b;
        case'/':return a/b;
        case'*':return a*b;
        case'^':return pow(a,b);
        default:return 0;
    }
}

int In(char c,char *tr) //判断字符是否为运算符
{
    int i=0,flag=0;
    while(tr[i]!='\0')
    {
        if(tr[i]==c) flag=1;
        i++;
    }
    return flag;
}

char Precede(char m, char n, char *tr) //判断运算符的优先级
{
    unsigned char Prior[8][8]={">><<<<>>",">><<<<>>",">>>><<>>",">>>><<>>",">>>>><>>","<<<<<<= ",">>>>> >>","<<<<<< ="};
    int i=0,j=0;
    while(m!=tr[i]) i++;
    while(n!=tr[j]) j++;
    return Prior[i][j];
}

double EvaluateExpression(char *expr) //算术表达式求值的算符优先算法
{
    negative(expr);
    OPTR TR;OPND ND;
    InitStack(&TR);initStack(&ND);
    char *c,cc[500]={},tr,x,OP[10]={'+','-','*','/','^','(',')','#','\0'};
    double a,b,cf;
    int i=1;
    Push(&TR,'#');
    c=strcat(expr,"# "); //拼接表达式使其以#结尾
    while(*c!='#'||GetTop(&TR)!='#') 
    {
        fprintf(fp,"————————————————————第%d步————————————————————\n",i);
        if(!In(*c,OP)) //不是运算符进栈
        {            
            while(!In(*c,OP))
            {
                strcat(cc,c); //两位数以上数字输入
                c++;                
            }
            cf=atof(cc);
            OutPut(&TR);
            outPut(&ND);
            fprintf(fp,"输入字符: '%lf'\n",cf);
            memset(cc,0x00,sizeof(char)*256); //清空临时字符串
            push(&ND,cf);
            fprintf(fp,"操作: Push(OPND,'%lf')\n",cf);
        }
        else
        {
            OutPut(&TR);
            outPut(&ND);
            fprintf(fp,"输入字符: '%c'\n",*c);
            switch(Precede(GetTop(&TR),*c,OP))
            {
                case'<': //栈顶元素优先权低
                    Push(&TR,*c);
                    fprintf(fp,"操作: Push(OPTR,'%c')\n",*c);
                    c++;
                    break;
                case'=': //脱括号指针移动到下一字符
                    Pop(&TR,&x);
                    fprintf(fp,"操作: Pop(OPTR){消去一对括号}\n",x);
                    c++;
                    break;
                case'>': //退栈并将运算结果入栈
                    Pop(&TR,&tr);
                    pop(&ND,&b);
                    pop(&ND,&a);
                    push(&ND,Opreate(a,b,tr));
                    fprintf(fp,"操作: Opreate('%lf','%c','%lf')\n",a,tr,b);
                    break;
            }
        }
        i++;
    }
    fprintf(fp,"————————————————————第%d步————————————————————\n",i);
    OutPut(&TR);
    outPut(&ND);
    fprintf(fp,"输入字符: '%c'\n",*c);
    fprintf(fp,"操作:return GetTop(OPND)\n");
    return getTop(&ND);
}

void clear(char *c)//删除输入的空格
{
	char *str=c;
	int i,j;
	for(i=0,j=0;c[i]!='\0';i++)
	{
		if(c[i]!=' ')
			str[j++]=c[i];
	}
	str[j]='\0';
	c=str;	
}

int check(char *c)//检查是否有非法字符输入
{
    int i,j,t1=0,t2=0,flag=0;
    for(i=0;i<strlen(c);i++)//括号输入不完整问题
    {
        if(c[i]=='(') t1++;
        if(c[i]==')') t2++;
        if(!In(c[i],"+-*/^()1234567890. ")) 
        {
            flag=1;
            break;
        }  
    }
    if(t1!=t2) flag=1;
    for(i=0,j=1;j<strlen(c);i++,j++)//运算符相邻问题
    {
        if(In(c[i],"+-*/^ ")&&In(c[j],"+-*/^ "))
        {
            flag=1;
            break;
        }
    }
    return flag;
}

void negative(char *c)//处理负数问题
{
    int i,j,k,l=0;
    char str[100];
    strcpy(str,c);
    for(i=0,j=1;j<strlen(str);i++,j++)
    {
        if(str[i]=='('&&str[j]=='-')
        {
            c[j+l]='0';
            for(k=j+l;c[k]!='\0';k++)
                c[k+1]=str[k-l];
            l++;
        }
    }
}

void change(char *c,double x)//将变量x赋值
{
	char p[1000],a[100]={};
    int i,j,k,l,f=0;
    strcpy(p,c);
    sprintf(a,"%lf",x);
	for(i=0;i<strlen(c);i++)
    {
		if(c[i]=='x')
        {    
            for(k=i+f*(strlen(a)-1),j=0;j<strlen(a);k++,j++)
                p[k]=a[j];
            for(l=i+1;l<strlen(c);l++,k++)   
                p[k]=c[l];
        p[k]='\0';
        f++;
        }
    }
    strcpy(c,p);
} 

int variable(char *c)//判断输入是否为变量
{
    int i,j,n=0;
    for(i=0;i<strlen(c);i++)
    {
        if(c[i]=='x')
        {
            n=1;
            break;
        }
    }
    for(i=0,j=1;j<strlen(c);i++,j++)
    {   
        if((c[i]=='x'||c[i]=='.')&&(c[j]=='.'||c[j]=='x'))
        {
            n=0;
            break;
        }
    }
    return n;
}