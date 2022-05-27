Status Entry()//读入赫夫曼树
{
    int i=1,j=1,k,m;
    char buffer[1024],*p;
    A:printf("请输入赫夫曼树读取文件名:");
    fflush(stdin);gets(name);strcat(name,".txt");
    if((fp=fopen(name,"r"))==NULL)
    {
        printf("该文件夹下不存在%s文件!\n",name);
        goto A;
    }
    while((fgets(buffer,1024,fp))!=NULL)
    {
        if(i>2)
        {
            character[j]=buffer[0];
            m=0;
            for(k=0;buffer[k]!='\0';k++)
            {
                if(buffer[k]>='0'&&buffer[k]<='9')
                {
                    p[m]=buffer[k];
                    m++;
                }
            }
            weight[j]=atoi(p);
            memset(p,0,sizeof(p)); 
            j++;
        }
        i++;
    }
    fclose(fp);
    printf("赫夫曼树建立成功!\n");
}

Status Save()//保存赫夫曼树
{
    printf("请输入该赫夫曼树保存文件名:");
    fflush(stdin);gets(name);strcat(name,".txt");
    fp=fopen(name,"w");
    fprintf(fp,"size:%d\n",sizeof(character));
    fprintf(fp,"字符\t权重\n");
    for(int i=1;i<sizeof(character);i++)
    {
        fprintf(fp,"%c\t%d\n",character[i],weight[i]);
    }
    printf("保存成功!\n");
    fclose(fp);
}

Status Init()//初始化
{
    int i,j,n,ret,w,flag=0;
    char c;
    A:printf("请输入字符集数:");
    ret=scanf("%d",&n);
    if(n<0||ret==0) goto A;
    for(i=0;i<n;i++)
    {
        printf("请输入第%d个字符:",i+1);
        fflush(stdin);scanf("%c",&c);
        B:printf("请输入\'%c\'的权重:",c);
        ret=scanf("%d",&w);
        if(w<0||ret==0) goto B;
        if(w>0)
        {
            for(j=0;j<sizeof(character)-1;j++)
            {
                if(c==character[j])
                {
                    weight[j]=w;
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
                character[j]=c;
                weight[j]=w;
            }
        }
    }
    printf("初始化成功!\n");
}

Status Coding(HuffmanCode code[],HuffmanTree T[],int leafNum)//编码
{
    int i;
    char enter[1000]; 
    printf("请输入编码文件名:");
    fflush(stdin);gets(name);strcat(name,".txt");
    if((fp=fopen(name,"r"))==NULL)
    {
        printf("该文件夹下无%s!\n",name);
        return ERROR;
    }
    fgets(enter,1000,fp);
    fclose(fp);
    Convert(enter);
	CodingHuffman(code,T,enter,leafNum);
    WriteBit(huffmanCode);
    printf("编码成功!\n");
}

Status Decoding(HuffmanCode code[],HuffmanTree T[],int leafNum)//译码
{
    char choice;
    if(ReadBit())
    {
        DecodingHuffman(code,T,huffmanCode,leafNum);
        printf("请输入译码结果存储文件名:");
        fflush(stdin);gets(name);strcat(name,".txt");
        fp=fopen(name,"w");
        fputs(txtCode,fp);
        fclose(fp);
        printf("译码成功,");
        A:printf("是否打印结果(y|n):");
        fflush(stdin);scanf("%c",&choice);
        if(choice=='y') printf("%s\n",txtCode);
        else if(choice=='n') return OK;
        else goto A;
    }
    return OK;
}

Status PrintCode()//打印代码
{
    if(ReadBit())
    {
        printf("请输入打印代码文件名:");
        fflush(stdin);gets(name);strcat(name,".txt");
        fp=fopen(name,"w");
        for(int i=0;i<strlen(huffmanCode);i++)
        {
            printf("%c",huffmanCode[i]);
            fprintf(fp,"%c",huffmanCode[i]);
            if((i+1)%50==0)
            {
                printf("\n");
                fprintf(fp,"\n");
            }
        }
        fclose(fp);
        printf("\n结果存入%s文件成功!\n",name);
    }
}

Status PrintHuffmanTree(HuffmanTree T[],int leafNum)//打印赫夫曼树
{
    printf("请输入打印赫夫曼树文件名:");
    fflush(stdin);gets(name);strcat(name,".txt");
    fp=fopen(name,"w");
    fprintf(fp,"赫夫曼树:\n");
    fclose(fp);
    PrintTree(T,2*leafNum-1,0,0,name);
    printf("已存入%s文件!\n",name);
}

Status Convert(char s[])//字母中小写转大写
{
    char *p;
    p=s;
    while(*p!='\0')
    {
        if(*p>='a'&&*p<='z') *p-=32;
        p++;
    }
}

Status WriteBit(char code[])//将字符串转化为bit:开头4个字节保存了该文件存储的位数，后面的字节为存储内容
{
    char *p;
    int i,j=-1,count,num,left;
    printf("请输入代码存储文件名:");
    fflush(stdin);gets(name);strcat(name,".txt");
    fp=fopen(name,"wb");
    count=strlen(code);//字符串个数
    num=count/8;//存储字符需要的字节数
    left=count%8;//字符串剩余不足8位的个数
    if(left==0)
    {
        p=(char*)malloc(sizeof(char)*num);
        memset(p,0,num);
    }
    else
    {
        p=(char*)malloc(sizeof(char)*(num+1));
        memset(p, 0, num + 1);
    }
    for(i=0;i<count;i++)//位运算，每8个字符以2进制的形式储存在一个字符中
    {
        if(i%8==0) j++;
        p[j]<<=1;
        code[i]-='0';
        p[j]|=code[i];
    }
    if(left!=0)//如果left不为0，需要把剩余的几个位向左边靠拢
    {
        p[j]<<=8-left;
        fwrite(&count,sizeof(count),1,fp);
        fwrite(p,1,num+1,fp);
    }
    else
    {
        fwrite(&count,sizeof(count),1,fp);
        fwrite(p,1,num,fp);
    }
    fclose(fp);
}

Status ReadBit()//bit转字符串
{
    strcpy(huffmanCode,"");
    char *p;
    int i,j=-1,count,num,left,t=0;
    unsigned char flag=128; //即0b1000000,用于做位运算,注意要用无符号的字符型
    printf("请输入代码存储文件名:");
    fflush(stdin);gets(name);strcat(name,".txt");
    if((fp=fopen(name,"rb"))==NULL)
    {
        printf("该文件夹下无%s!\n",name);
        return ERROR;
    }
    fread(&count,sizeof(count),1,fp);
    num=count/8;
    left=count%8;
    if(left==0)
    {
        p=(char*)malloc(sizeof(char)*num);
        fread(p,1,num,fp);
    }
    else
    {
        p=(char*)malloc(sizeof(char)*(num+1));
        fread(p,1,num+1,fp);
    }
    fclose(fp);
    for(i=0;i<count;i++)
    {
        if(i%8==0)
        {
            j++;
            flag=128;
        }
        if((p[j]&flag)) huffmanCode[t]='1';
        else huffmanCode[t]='0';
        t++;
        flag/=2;
    }
    return OK;
}