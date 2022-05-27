#include "definition.h"
#include "huffman.c"
#include "function.c"
Status main()
{
	int leafNum,choice,flag=1;
	A:system("cls");
	system("color F1");
	printf("  ºÕ·òÂü±àÂëÒëÂëÆ÷\n");
	printf("-------------------\n");
	printf("  1---³õÊ¼»¯\n  2---±àÂë\n  3---ÒëÂë\n  4---´òÓ¡´úÂëÎÄ¼ş\n  5---´òÓ¡ºÕ·òÂüÊ÷\n  0--ÍË³öÏµÍ³\n");
	printf("-------------------\n");
	if(flag==1) Entry();
	leafNum=sizeof(character)-1;
	HuffmanCode Code[leafNum+1];
	HuffmanTree Tree[2*leafNum+1];
	CreateTree(Tree,leafNum);CreateCode(Code,Tree,leafNum);
	if(flag==2) Save(leafNum);
	flag=0;
	printf("ÇëÊäÈëĞòºÅ:");
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