#include<stdio.h>
#include<stdlib.h>
#include<math.h>
static int m;//小数位数的全局变量
typedef struct node//定义结点结构体
{
	double coe;//系数
	int exp;//指数
	struct node *next;//结构体
}node,*list;

list input() //函数：输入多项式
{
	list a,b,l;
	l=(list)malloc(sizeof(node));
	l->next=NULL;
	b=l;
	int n,i;
	printf("请输入项数：");
	scanf("%d",&n);//输入项数
	printf("请输入系数 指数：\n");
	for(i=0;i<n;i++)
	{
		a=(list)malloc(sizeof(node));
		printf("第%d项:",i+1);
		scanf("%lf %d",&(a->coe),&(a->exp));//输入系数和指数
		a->next=NULL;
		b->next=a;
		b=a;
	}
	return l;
}

void sort(list l)//多项式整理
{
	list i,j;
	double tcoe;
	int texp;
	for(i=l->next;i!=NULL;i=i->next)
	{
		for(j=i->next;j!=NULL;j=j->next)
		{
			if(j->exp>i->exp)
			{
				tcoe=j->coe;
				j->coe=i->coe;
				i->coe=tcoe;
				texp=j->exp;
				j->exp=i->exp;
				i->exp=texp;
			}
			else if(j->exp==i->exp)
			{
				tcoe=j->coe+i->coe;
				i->coe=tcoe;
				j->coe=0;
				i->exp=j->exp;
				j->exp=0;
			}
		}
	}
}

void output(list l)//函数：输出多项式
{
	sort(l);
	list a,b;
	int i=0,j=0,k=0;
	a=l->next;
	b=l->next;
	while(b)
	{
		j++;
		if(b->coe==0.0)
			k++;
		b=b->next;
	}
	if(j==k)
		printf("0");
	else
	{
		while(a)
		{
			if(a->exp!=0)
			{
				if(a->coe<0)
				{
					printf("-");
					if(a->exp==1)
					{
						if(a->coe==-1)
							printf("x");
						else
							printf("%.*lfx",m,-a->coe);
					}
					else
					{
						if(a->coe==-1)
							printf("x^%d",a->exp);
						else
							printf("%.*lfx^%d",m,-a->coe,a->exp);
					}
				}
				else if(a->coe>0)
				{
					if(i!=0)
						printf("+");
					if(a->exp==1)
					{
						if(a->coe==1)
							printf("x");
						else
							printf("%.*lfx",m,a->coe);
					}
					else if(a->exp!=1)
					{
						if(a->coe==1)
							printf("x^%d",a->exp);
						else
							printf("%.*lfx^%d",m,a->coe,a->exp);
					}
				}
			}
			else
			{
				if(a->coe<0)
					printf("%.*lf",m,a->coe);
				else if(a->coe>0)
				{
					if(i==0)
						printf("%.*lf",m,a->coe);
					else
						printf("+%.*lf",m,a->coe);
				}
			}
			a=a->next;
			i++;
		}
	}
	printf("\n");
}

void plus(list a,list b)//函数：多项式相加
{
	list la,lb,lc,ld,c,d;
	c=(list)malloc(sizeof(node));
	c->next=NULL;
	d=c;
	la=a->next;
	lb=b->next;
	while(la!=NULL&&lb!=NULL)
	{
		lc=(list)malloc(sizeof(node));
		lc->next=NULL;	
		if(la->exp>lb->exp)
		{
			lc->exp=la->exp;
			lc->coe=la->coe;
			d->next=lc;
			d=lc;
			la=la->next;
		}
		else if(la->exp==lb->exp)
		{
			double sum=la->coe+lb->coe;
			if(sum!=0.0)
			{
				lc->exp=la->exp;
				lc->coe=sum;
				d->next=lc;
				d=lc;
			}
			la=la->next;
			lb=lb->next;
		}
		else
		{
			lc->exp=lb->exp;
			lc->coe=lb->coe;
			d->next=lc;
			d=lc;	
			lb=lb->next;			
		}			
	}
	while(la)
	{
		lc=(list)malloc(sizeof(node));
		lc->next=NULL;	
		lc->exp=la->exp;
		lc->coe=la->coe;			
		la=la->next;
		d->next=lc;
		d=lc;
	}
	while(lb)
	{
		lc=(list)malloc(sizeof(node));
		lc->next=NULL;	
		lc->exp=lb->exp;
		lc->coe=lb->coe;
		lb=lb->next;
		d->next=lc;
		d=lc;	
	}
	output(c);
}

void oppo(list *l)//函数：多项式系数变负
{
	list a=(*l)->next;
	while(a)
	{
		a->coe=-a->coe;
		a=a->next;
	}
}

void minus(list a,list b)//函数：多项式相减
{
	oppo(&b);
	plus(a,b);
	oppo(&b);
}

void multi(list a,list b)//函数：多项式乘法
{
	list la,lb,lc,c,ld;
	la=a->next;
	lb=b->next;
	c=(list)malloc(sizeof(node));
	lc=c;
	lc->next=NULL;
	while(la)
	{
		lb=b->next;
		while(lb)
		{
			ld=(list)malloc(sizeof(node));
			ld->next=NULL;
			ld->coe=la->coe*lb->coe;
			ld->exp=la->exp+lb->exp;
			lc->next=ld;
			lc=ld;
			lb=lb->next;
		}
		la=la->next;
	}
	output(c);
}

void fx(list a,double x)//函数：多项式在x处的值
{
	list la;
	la=a->next;
	double value=0;
	while(la)
	{
		value+=(la->coe)*pow(x,la->exp);
		la=la->next;
	}
	printf("在%.*lf处的值为:%.*lf\n",m,x,m,value);
}

void diff(list a)//函数：求一阶导
{
	list la,b,lb,lc;
	la=a->next;
	b=(list)malloc(sizeof(node));
	lb=b;
	lb->next=NULL;
	while(la)
	{
		lc=(list)malloc(sizeof(node));
		if(la->exp==0)
		{	
			lc->coe=0.0;
			lc->exp=0;
		}
		else
		{
			lc->coe=la->coe*la->exp;
			lc->exp=la->exp-1;
		}
		lc->next=NULL;
		lb->next=lc;
		lb=lc;
		la=la->next;
	}
	printf("的一阶导为:");
	output(b);
}

int main()
{
	list A,B;
	int t;
	printf("请输入全部数保留小数的位数：");
	scanf("%d",&m);
	printf("多项式A:\n");
	A=input();
	printf("多项式B:\n");
	B=input();
	printf("多项式A:");
	output(A);
	printf("多项式B:");
	output(B);
	while(1)
	{
		printf("选择运算功能: 0:退出 1:加 2:减 3:乘 4:求一阶导 5:在x处的值\n");
		scanf("%d",&t);
		switch (t)
		{
			case 0:exit(0);
			case 1:printf("多项式相加结果为：");plus(A,B);break; 
			case 2:printf("多项式相减结果为：");minus(A,B);break;
			case 3:printf("多项式相乘结果为：");multi(A,B);break;
			case 4:
			{
				printf("多项式A");diff(A);
				printf("多项式B");diff(B);
			}break;
			case 5:
			{
				double x;
				printf("请输入x的值:");
				scanf("%lf",&x);
				printf("多项式A:");
				fx(A,x);
				printf("多项式B:");
				fx(B,x);
			}break;			
			default:printf("输入错误，请重新输入！\n");
		}
	}
	system("pause");
	return 0;
}