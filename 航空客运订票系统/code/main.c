#include "definition.h"
#include "list.c"
#include "queue.c"
#include "airline.c"
#include "inquire.c"
#include "refund.c"

Status main()
{
    system("Color F3"); 
    int color,x;
    time_t T;
    time(&T);
    struct tm *now;
    now=localtime(&T);
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("                     欢迎使用中国航空客运订票系统                          \n");
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("          当前时间是北京时间:【%d年%d月%d日星期%d %d时%d分%d秒】\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_wday,
    now->tm_hour,now->tm_min,now->tm_sec);
    EntryAirline();AirlineReady();EntryList();
    printf("\n                <<<<<<<<<<<<----功能菜单---->>>>>>>>>>>>                    \n\n");
    printf("                  0.退出系统   1.查询航线   2.个人信息\n\n");
    while(1)
    {
        printf("请输入选择的功能(1查询|2退票):");
        scanf("%d",&x);
        if(x!=0&&x!=1&&x!=2) {printf("输入有误!!\n");continue;}
        if(x==0) break;
        switch(x)
        {
            case 1:Query();break;//查询航线
            case 2:Information();break;//个人信息
        } 
    }
    OutAirline();OutList();
    printf("\n>>>>>>>>感谢您的使用,下次再会!<<<<<<<<<\n");
    return OK;
}