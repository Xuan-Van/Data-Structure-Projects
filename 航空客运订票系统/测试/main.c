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
    printf("                     ��ӭʹ���й����տ��˶�Ʊϵͳ                          \n");
    printf("<<<<<<<<<<---------------------------------------------------->>>>>>>>>>\n");
    printf("          ��ǰʱ���Ǳ���ʱ��:��%d��%d��%d������%d %dʱ%d��%d�롿\n",now->tm_year+1900,now->tm_mon+1,now->tm_mday,now->tm_wday,now->tm_hour,now->tm_min,now->tm_sec);
    EntryAirline();AirlineReady();EntryList();
    printf("\n                <<<<<<<<<<<<----���ܲ˵�---->>>>>>>>>>>>                    \n\n");
    printf("                  0.�˳�ϵͳ   1.��ѯ����   2.������Ϣ\n\n");
    while(1)
    {
        printf("������ѡ��Ĺ���(1��ѯ|2��Ʊ):");
        scanf("%d",&x);
        if(x!=0&&x!=1&&x!=2) {printf("��������!!\n");continue;}
        if(x==0) break;
        switch(x)
        {
            case 1:Query();break;//��ѯ����
            case 2:Information();break;//������Ϣ
        } 
    }
    OutAirline();OutList();
    printf("\n>>>>>>>>��л����ʹ��,�´��ٻ�!<<<<<<<<<\n");
    return OK;
}