#include<stdio.h>
#include<stdlib.h>
#include<math.h>
static int m;//С��λ����ȫ�ֱ���
typedef struct node//������ṹ��
{
	double coe;//ϵ��
	int exp;//ָ��
	struct node *next;//�ṹ��
}node,*list;

list input() //�������������ʽ
{
	list a,b,l;
	l=(list)malloc(sizeof(node));
	l->next=NULL;
	b=l;
	int n,i;
	printf("������������");
	scanf("%d",&n);//��������
	printf("������ϵ�� ָ����\n");
	for(i=0;i<n;i++)
	{
		a=(list)malloc(sizeof(node));
		printf("��%d��:",i+1);
		scanf("%lf %d",&(a->coe),&(a->exp));//����ϵ����ָ��
		a->next=NULL;
		b->next=a;
		b=a;
	}
	return l;
}

void sort(list l)//����ʽ����
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

void output(list l)//�������������ʽ
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

void plus(list a,list b)//����������ʽ���
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

void oppo(list *l)//����������ʽϵ���为
{
	list a=(*l)->next;
	while(a)
	{
		a->coe=-a->coe;
		a=a->next;
	}
}

void minus(list a,list b)//����������ʽ���
{
	oppo(&b);
	plus(a,b);
	oppo(&b);
}

void multi(list a,list b)//����������ʽ�˷�
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

void fx(list a,double x)//����������ʽ��x����ֵ
{
	list la;
	la=a->next;
	double value=0;
	while(la)
	{
		value+=(la->coe)*pow(x,la->exp);
		la=la->next;
	}
	printf("��%.*lf����ֵΪ:%.*lf\n",m,x,m,value);
}

void diff(list a)//��������һ�׵�
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
	printf("��һ�׵�Ϊ:");
	output(b);
}

int main()
{
	list A,B;
	int t;
	printf("������ȫ��������С����λ����");
	scanf("%d",&m);
	printf("����ʽA:\n");
	A=input();
	printf("����ʽB:\n");
	B=input();
	printf("����ʽA:");
	output(A);
	printf("����ʽB:");
	output(B);
	while(1)
	{
		printf("ѡ�����㹦��: 0:�˳� 1:�� 2:�� 3:�� 4:��һ�׵� 5:��x����ֵ\n");
		scanf("%d",&t);
		switch (t)
		{
			case 0:exit(0);
			case 1:printf("����ʽ��ӽ��Ϊ��");plus(A,B);break; 
			case 2:printf("����ʽ������Ϊ��");minus(A,B);break;
			case 3:printf("����ʽ��˽��Ϊ��");multi(A,B);break;
			case 4:
			{
				printf("����ʽA");diff(A);
				printf("����ʽB");diff(B);
			}break;
			case 5:
			{
				double x;
				printf("������x��ֵ:");
				scanf("%lf",&x);
				printf("����ʽA:");
				fx(A,x);
				printf("����ʽB:");
				fx(B,x);
			}break;			
			default:printf("����������������룡\n");
		}
	}
	system("pause");
	return 0;
}