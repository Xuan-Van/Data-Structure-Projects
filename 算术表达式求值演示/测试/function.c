#include "function.h"
#include "stack.c"
double Opreate(double a,double b,char tr) //�Բ������Ͷ�Ӧ����������м��㲢���ؽ��
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

int In(char c,char *tr) //�ж��ַ��Ƿ�Ϊ�����
{
    int i=0,flag=0;
    while(tr[i]!='\0')
    {
        if(tr[i]==c) flag=1;
        i++;
    }
    return flag;
}

char Precede(char m, char n, char *tr) //�ж�����������ȼ�
{
    unsigned char Prior[8][8]={">><<<<>>",">><<<<>>",">>>><<>>",">>>><<>>",">>>>><>>","<<<<<<= ",">>>>> >>","<<<<<< ="};
    int i=0,j=0;
    while(m!=tr[i]) i++;
    while(n!=tr[j]) j++;
    return Prior[i][j];
}

double EvaluateExpression(char *expr) //�������ʽ��ֵ����������㷨
{
    negative(expr);
    OPTR TR;OPND ND;
    InitStack(&TR);initStack(&ND);
    char *c,cc[500]={},tr,x,OP[10]={'+','-','*','/','^','(',')','#','\0'};
    double a,b,cf;
    int i=1;
    Push(&TR,'#');
    c=strcat(expr,"# "); //ƴ�ӱ��ʽʹ����#��β
    while(*c!='#'||GetTop(&TR)!='#') 
    {
        fprintf(fp,"������������������������������������������%d������������������������������������������\n",i);
        if(!In(*c,OP)) //�����������ջ
        {            
            while(!In(*c,OP))
            {
                strcat(cc,c); //��λ��������������
                c++;                
            }
            cf=atof(cc);
            OutPut(&TR);
            outPut(&ND);
            fprintf(fp,"�����ַ�: '%lf'\n",cf);
            memset(cc,0x00,sizeof(char)*256); //�����ʱ�ַ���
            push(&ND,cf);
            fprintf(fp,"����: Push(OPND,'%lf')\n",cf);
        }
        else
        {
            OutPut(&TR);
            outPut(&ND);
            fprintf(fp,"�����ַ�: '%c'\n",*c);
            switch(Precede(GetTop(&TR),*c,OP))
            {
                case'<': //ջ��Ԫ������Ȩ��
                    Push(&TR,*c);
                    fprintf(fp,"����: Push(OPTR,'%c')\n",*c);
                    c++;
                    break;
                case'=': //������ָ���ƶ�����һ�ַ�
                    Pop(&TR,&x);
                    fprintf(fp,"����: Pop(OPTR){��ȥһ������}\n",x);
                    c++;
                    break;
                case'>': //��ջ������������ջ
                    Pop(&TR,&tr);
                    pop(&ND,&b);
                    pop(&ND,&a);
                    push(&ND,Opreate(a,b,tr));
                    fprintf(fp,"����: Opreate('%lf','%c','%lf')\n",a,tr,b);
                    break;
            }
        }
        i++;
    }
    fprintf(fp,"������������������������������������������%d������������������������������������������\n",i);
    OutPut(&TR);
    outPut(&ND);
    fprintf(fp,"�����ַ�: '%c'\n",*c);
    fprintf(fp,"����:return GetTop(OPND)\n");
    return getTop(&ND);
}

void clear(char *c)//ɾ������Ŀո�
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

int check(char *c)//����Ƿ��зǷ��ַ�����
{
    int i,j,t1=0,t2=0,flag=0;
    for(i=0;i<strlen(c);i++)//�������벻��������
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
    for(i=0,j=1;j<strlen(c);i++,j++)//�������������
    {
        if(In(c[i],"+-*/^ ")&&In(c[j],"+-*/^ "))
        {
            flag=1;
            break;
        }
    }
    return flag;
}

void negative(char *c)//����������
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

void change(char *c,double x)//������x��ֵ
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

int variable(char *c)//�ж������Ƿ�Ϊ����
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