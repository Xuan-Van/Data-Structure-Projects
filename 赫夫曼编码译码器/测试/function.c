Status Entry()//����շ�����
{
    int i=1,j=1,k,m;
    char buffer[1024],*p;
    A:printf("������շ�������ȡ�ļ���:");
    fflush(stdin);gets(name);strcat(name,".txt");
    if((fp=fopen(name,"r"))==NULL)
    {
        printf("���ļ����²�����%s�ļ�!\n",name);
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
    printf("�շ����������ɹ�!\n");
}

Status Save()//����շ�����
{
    printf("������úշ����������ļ���:");
    fflush(stdin);gets(name);strcat(name,".txt");
    fp=fopen(name,"w");
    fprintf(fp,"size:%d\n",sizeof(character));
    fprintf(fp,"�ַ�\tȨ��\n");
    for(int i=1;i<sizeof(character);i++)
    {
        fprintf(fp,"%c\t%d\n",character[i],weight[i]);
    }
    printf("����ɹ�!\n");
    fclose(fp);
}

Status Init()//��ʼ��
{
    int i,j,n,ret,w,flag=0;
    char c;
    A:printf("�������ַ�����:");
    ret=scanf("%d",&n);
    if(n<0||ret==0) goto A;
    for(i=0;i<n;i++)
    {
        printf("�������%d���ַ�:",i+1);
        fflush(stdin);scanf("%c",&c);
        B:printf("������\'%c\'��Ȩ��:",c);
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
    printf("��ʼ���ɹ�!\n");
}

Status Coding(HuffmanCode code[],HuffmanTree T[],int leafNum)//����
{
    int i;
    char enter[1000]; 
    printf("����������ļ���:");
    fflush(stdin);gets(name);strcat(name,".txt");
    if((fp=fopen(name,"r"))==NULL)
    {
        printf("���ļ�������%s!\n",name);
        return ERROR;
    }
    fgets(enter,1000,fp);
    fclose(fp);
    Convert(enter);
	CodingHuffman(code,T,enter,leafNum);
    WriteBit(huffmanCode);
    printf("����ɹ�!\n");
}

Status Decoding(HuffmanCode code[],HuffmanTree T[],int leafNum)//����
{
    char choice;
    if(ReadBit())
    {
        DecodingHuffman(code,T,huffmanCode,leafNum);
        printf("�������������洢�ļ���:");
        fflush(stdin);gets(name);strcat(name,".txt");
        fp=fopen(name,"w");
        fputs(txtCode,fp);
        fclose(fp);
        printf("����ɹ�,");
        A:printf("�Ƿ��ӡ���(y|n):");
        fflush(stdin);scanf("%c",&choice);
        if(choice=='y') printf("%s\n",txtCode);
        else if(choice=='n') return OK;
        else goto A;
    }
    return OK;
}

Status PrintCode()//��ӡ����
{
    if(ReadBit())
    {
        printf("�������ӡ�����ļ���:");
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
        printf("\n�������%s�ļ��ɹ�!\n",name);
    }
}

Status PrintHuffmanTree(HuffmanTree T[],int leafNum)//��ӡ�շ�����
{
    printf("�������ӡ�շ������ļ���:");
    fflush(stdin);gets(name);strcat(name,".txt");
    fp=fopen(name,"w");
    fprintf(fp,"�շ�����:\n");
    fclose(fp);
    PrintTree(T,2*leafNum-1,0,0,name);
    printf("�Ѵ���%s�ļ�!\n",name);
}

Status Convert(char s[])//��ĸ��Сдת��д
{
    char *p;
    p=s;
    while(*p!='\0')
    {
        if(*p>='a'&&*p<='z') *p-=32;
        p++;
    }
}

Status WriteBit(char code[])//���ַ���ת��Ϊbit:��ͷ4���ֽڱ����˸��ļ��洢��λ����������ֽ�Ϊ�洢����
{
    char *p;
    int i,j=-1,count,num,left;
    printf("���������洢�ļ���:");
    fflush(stdin);gets(name);strcat(name,".txt");
    fp=fopen(name,"wb");
    count=strlen(code);//�ַ�������
    num=count/8;//�洢�ַ���Ҫ���ֽ���
    left=count%8;//�ַ���ʣ�಻��8λ�ĸ���
    if(left==0)
    {
        p=(char*)malloc(sizeof(char)*num);
        memset(p,0,num);
    }
    else
    {
        p=(char*)malloc(sizeof(char)*(num+1));
        memset(p,0,num+1);
    }
    for(i=0;i<count;i++)//λ���㣬ÿ8���ַ���2���Ƶ���ʽ������һ���ַ���
    {
        if(i%8==0) j++;
        p[j]<<=1;
        code[i]-='0';
        p[j]|=code[i];
    }
    if(left!=0)//���left��Ϊ0����Ҫ��ʣ��ļ���λ����߿�£
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

Status ReadBit()//bitת�ַ���
{
    strcpy(huffmanCode,"");
    char *p;
    int i,j=-1,count,num,left,t=0;
    unsigned char flag=128; //��0b1000000,������λ����,ע��Ҫ���޷��ŵ��ַ���
    printf("���������洢�ļ���:");
    fflush(stdin);gets(name);strcat(name,".txt");
    if((fp=fopen(name,"rb"))==NULL)
    {
        printf("���ļ�������%s!\n",name);
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