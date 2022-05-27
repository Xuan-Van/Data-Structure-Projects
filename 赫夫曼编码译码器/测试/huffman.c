Status CreateTree(HuffmanTree T[],int leafNum)//½¨Á¢ºÕ·òÂüÊ÷
{
	int huffmanNum=2*leafNum;
	int i,j,p1,p2,least1,least2;
	for(i=1;i<=huffmanNum;i++)//³õÊ¼»¯ºÕ·òÂüÊ÷
	{
		T[i].character='\0';
		T[i].parent=0;
		T[i].lchild=0;
		T[i].rchild=0;
		T[i].weight=0;
	}
	for(i=1;i<=leafNum;i++)//Â¼Èë×Ö·ûºÍÆµ¶È
	{
		T[i].character=character[i];
		T[i].weight=weight[i];
	}
	for(i=leafNum+1;i<=huffmanNum;i++)
	{
		p1=0;p2=0;least1=least2=10000;
		for(j=1;j<i;j++)
		{
			if(T[j].parent==0)
				if(T[j].weight<least1)
				{
					least2=least1;
					least1=T[j].weight;
					p2=p1;
					p1=j;
				}
				else
				{
					if(T[j].weight<least2)
					{
						least2=T[j].weight;
						p2=j;
					}
				}
		}
		T[p1].parent=i;
		T[p2].parent=i;
		T[i].lchild=p1;
		T[i].rchild=p2;
		T[i].weight=T[p1].weight+T[p2].weight;
	}
	T[huffmanNum-1].parent=0;
}

Status CreateCode(HuffmanCode code[],HuffmanTree T[],int leafNum)//½¨Á¢ºÕ·òÂü±àÂë
{
	int i,child,parent;
	HuffmanCode buffer;
	for(i=1;i<=leafNum;i++)
	{
		buffer.character=character[i];
		buffer.start=leafNum;
		child=i;
		parent=T[i].parent;
		while(parent!=0)
		{
			buffer.start--;
			if(T[parent].lchild==child)
				buffer.bits[buffer.start]='0';
			else buffer.bits[buffer.start]='1';
			child=parent;
			parent=T[parent].parent;
		}
		code[i]=buffer;
	}
}

Status CodingHuffman(HuffmanCode code[],HuffmanTree T[],char enter[],int leafNum)//×Ö·û´®±àÂë
{
	strcpy(huffmanCode,"");
	int i,j,k,n=0;
	for(i=0;i<strlen(enter);i++)
	{
		for(j=1;j<=leafNum;j++)
		{
			if(enter[i]==T[j].character)
			{
				for(k=code[j].start;k<leafNum;k++)
				{
					huffmanCode[n]=code[j].bits[k];
					n++;
				}
			}
		}
	}
} 

Status DecodingHuffman(HuffmanCode code[],HuffmanTree T[],char s[],int leafNum)//ºÕ·òÂüÒëÂë
{
	int huffmanNum=2*leafNum;
	strcpy(txtCode,"");
	int i=huffmanNum-1,t=0;
	char *q=NULL;
	q=s;
	while(*q!='\0')
	{
		if(*q=='0') i=T[i].lchild;
		if(*q=='1') i=T[i].rchild;
		if((T[i].lchild==0)&&(T[i].rchild==0))
		{
			txtCode[t]=code[i].character;
			t++;
			i=huffmanNum-1;
		}
		q++;
	}
}

Status PrintTree(HuffmanTree T[],int root,int type,int level,char filename[])//´òÓ¡Ê÷×´Í¼
{
    int i;
	FILE *print=fopen(filename,"a+");
    if(root==0)
    {
        fclose(print);
        return OK;
    }
    PrintTree(T,T[root].rchild,2,level+1,filename);
    switch(type)
    {
    	case 0:
        	printf("%2d:%c\n",T[root].weight,T[root].character);
			fprintf(print,"%2d:%c\n",T[root].weight,T[root].character);
        	break;
    	case 1:
        	for(i=0;i<level;i++)
        	{
            	printf("\t");
            	fputc('\t',print);
        	}
        	printf("\\ %2d:%c\n",T[root].weight,T[root].character);
        	fprintf(print,"\\ %2d:%c\n",T[root].weight,T[root].character);
        	break;
    	case 2:
        	for(i=0;i<level;i++)
        	{
            	printf("\t");
            	fputc('\t',print);
        	}
        	printf("/ %2d:%c\n",T[root].weight,T[root].character);
        	fprintf(print,"/ %2d:%c\n",T[root].weight,T[root].character);
        	break;
    	default:break;
    }
	fclose(print);
    PrintTree(T,T[root].lchild,1,level+1,filename);
}