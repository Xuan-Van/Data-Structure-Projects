#include "function.c"
int main()
{
    int y=1,m=1,n=0;
    double x;
    char file[100],Algorite[500];
    while(y)
    {
        sprintf(file,"%d.txt",m);
        if((fp=fopen(file,"w"))==NULL) return -1;
        printf("请输入算式(^_^):");
        gets(Algorite); 
        clear(Algorite);
        n=variable(Algorite);    
        if(n)
        {
            printf("请输入x的值:");
            scanf("%lf",&x);
            fprintf(fp,"变量表达式为:%s\nx=%lf\n",Algorite,x);
            change(Algorite,x);
        }
        int flag=0;
        flag=check(Algorite);        
        if(flag) printf("输入有误，请重新输入(T_T)\n"); 
        else
        {
            fprintf(fp,"算式为：%s\n",Algorite);
            negative(Algorite);
            double result=EvaluateExpression(Algorite);
            if(fabs(result)>DBL_MAX) printf("发生除0错误(-_-)\n");
            else printf("%lf\n",result);
            fclose(fp);
        }
        printf("是否继续计算？ 1:继续 0:退出\n");
        scanf("%d",&y);
        getchar();
        m++;
    }
    system("pause");
    return 0;
}