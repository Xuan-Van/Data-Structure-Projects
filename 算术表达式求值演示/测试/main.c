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
        printf("��������ʽ(^_^):");
        gets(Algorite); 
        clear(Algorite);
        n=variable(Algorite);    
        if(n)
        {
            printf("������x��ֵ:");
            scanf("%lf",&x);
            fprintf(fp,"�������ʽΪ:%s\nx=%lf\n",Algorite,x);
            change(Algorite,x);
        }
        int flag=0;
        flag=check(Algorite);        
        if(flag) printf("������������������(T_T)\n"); 
        else
        {
            fprintf(fp,"��ʽΪ��%s\n",Algorite);
            negative(Algorite);
            double result=EvaluateExpression(Algorite);
            if(fabs(result)>DBL_MAX) printf("������0����(-_-)\n");
            else printf("%lf\n",result);
            fclose(fp);
        }
        printf("�Ƿ�������㣿 1:���� 0:�˳�\n");
        scanf("%d",&y);
        getchar();
        m++;
    }
    system("pause");
    return 0;
}