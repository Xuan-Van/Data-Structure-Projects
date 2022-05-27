#include "definition.h"
#include "city.c"
#include "admin.c"
#include "function.c"
Status main()
{
    system("color F9");
    int color;
    char choice;
    Graph *G; 
    G=(Graph*)malloc(sizeof(Graph));
    time_t T;
    time(&T);
    struct tm *now;
    now=localtime(&T);
    enterCity(G);createGraph(G);
    printf("请选择白天/夜间模式(1|0):");scanf("%d",&color);
    if(color==496) admin(G);
    else if(!color) system("color 0F");
    A:system("cls");
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("                        欢迎使用全国交通咨询系统\n");
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("          当前时间是北京时间:【%d年%d月%d日星期%d %d时%d分%d秒】\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_wday,now->tm_hour,now->tm_min,now->tm_sec);
    inquire(G);
    printf("是否退出(y|n):");fflush(stdin);scanf("%c",&choice);
    if(choice=='y')
    {
        printf("\n>>>>>>>>感谢您的使用,下次再会!<<<<<<<<<\n");
        system("pause");exit(0);
    }
    system("pause");goto A;
}