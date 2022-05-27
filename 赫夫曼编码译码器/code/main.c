#include "definition.h"
#include "huffman.c"
#include "function.c"
Status main()
{
	int leafNum,choice,flag=1;
	A:system("cls");
	system("color F1");
	printf("  赫夫曼编码译码器\n");
	printf("-------------------\n");
	printf("  1---初始化\n  2---编码\n  3---译码\n  4---打印代码文件\n  5---打印赫夫曼树\n  0--退出系统\n");
	printf("-------------------\n");
	if(flag==1) Entry();
	leafNum=sizeof(character)-1;
	HuffmanCode Code[leafNum+1];
	HuffmanTree Tree[2*leafNum+1];
	CreateTree(Tree,leafNum);CreateCode(Code,Tree,leafNum);
	if(flag==2) Save(leafNum);
	flag=0;
	printf("请输入序号:");
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