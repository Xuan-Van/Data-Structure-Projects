#include "definition.h"
#include "tree.c"
#include "function.c"

Status main()
{
	Entry();
    int choice;  
    A:system("cls");
    system("color F1");
    printf("                              ���׹���ϵͳ\n");
	printf("  -----------------------------------------------------------------------\n");
	printf("*****************************************************************************\n\n");
	printf("             1---��ӳ�Ա                     2---ɾ����Ա\n\n");
	printf("             3---�޸���Ϣ                     4---���ҳ�Ա \n\n");
	printf("             5---�������                     0---�˳�ϵͳ\n\n");
	printf("*****************************************************************************\n");
	printf("  -----------------------------------------------------------------------\n\n");		        
	printf("���������:");
    fflush(stdin);
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:Insert();system("pause");goto A;
        case 2:Delete();system("pause");goto A;
        case 3:Change();system("pause");goto A;
        case 4:Search();system("pause");goto A;
		case 5:PrintTree(T);system("pause");goto A;
        case 0:break;
        default:goto A;
    }
    Out(T);
    system("pause");
    return OK; 
} 