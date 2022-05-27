#include "definition.h"
#include "tree.c"
#include "function.c"

Status main()
{
	Entry();
    int choice;  
    A:system("cls");
    system("color F1");
    printf("                              家谱管理系统\n");
	printf("  -----------------------------------------------------------------------\n");
	printf("*****************************************************************************\n\n");
	printf("             1---添加成员                     2---删除成员\n\n");
	printf("             3---修改信息                     4---查找成员 \n\n");
	printf("             5---输出家谱                     0---退出系统\n\n");
	printf("*****************************************************************************\n");
	printf("  -----------------------------------------------------------------------\n\n");		        
	printf("请输入序号:");
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