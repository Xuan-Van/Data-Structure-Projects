#include "definition.h"
#include "huffman.c"
#include "function.c"
Status main()
{
	int leafNum,choice,flag=1;
	A:system("cls");
	system("color F1");
	printf("  �շ�������������\n");
	printf("-------------------\n");
	printf("  1---��ʼ��\n  2---����\n  3---����\n  4---��ӡ�����ļ�\n  5---��ӡ�շ�����\n  0--�˳�ϵͳ\n");
	printf("-------------------\n");
	if(flag==1) Entry();
	leafNum=sizeof(character)-1;
	HuffmanCode Code[leafNum+1];
	HuffmanTree Tree[2*leafNum+1];
	CreateTree(Tree,leafNum);CreateCode(Code,Tree,leafNum);
	if(flag==2) Save(leafNum);
	flag=0;
	printf("���������:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:Init();flag=2;system("pause");goto A;
		case 2:Coding(Code,Tree,leafNum);system("pause");goto A;
		case 3:Decoding(Code,Tree,leafNum);system("pause");goto A;
		case 4:PrintCode();system("pause");goto A;
		case 5:PrintHuffmanTree(Tree,leafNum);system("pause");goto A;
		case 0:break;
		default:goto A;
	}
	system("pause");
	return OK;
}