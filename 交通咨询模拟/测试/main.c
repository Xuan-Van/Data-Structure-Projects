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
    printf("��ѡ�����/ҹ��ģʽ(1|0):");scanf("%d",&color);
    if(color==496) admin(G);
    else if(!color) system("color 0F");
    A:system("cls");
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("                        ��ӭʹ��ȫ����ͨ��ѯϵͳ\n");
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("          ��ǰʱ���Ǳ���ʱ��:��%d��%d��%d������%d %dʱ%d��%d�롿\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_wday,now->tm_hour,now->tm_min,now->tm_sec);
    inquire(G);
    printf("�Ƿ��˳�(y|n):");fflush(stdin);scanf("%c",&choice);
    if(choice=='y')
    {
        printf("\n>>>>>>>>��л����ʹ��,�´��ٻ�!<<<<<<<<<\n");
        system("pause");exit(0);
    }
    system("pause");goto A;
}