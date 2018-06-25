#include <stdio.h> 
#include <stdlib.h> //为了使用exit() 
#include <memory.h> //为了使用memset()
int main() 
{ 
	int ch; 
	FILE* fp;
	FILE* fpout;
	int datatxt[10],base[10];
	char str[10];
	int i,j,n=0;
	unsigned int seed;
	int k,temp,rem,s[32],h=0;
	unsigned int randval;
	unsigned int cnt=0,seed_temp=0;
	//char fname[50]; //用于存放文件名 
	//printf("输入文件名："); 
	//scanf("%s",fname); 
	fp=fopen("/home/zz/work/c_study/cm4rand.txt","rt"); //只供读取 
	if(fp==NULL) //如果失败了 
	{ 
		printf("open log1 error！\n"); 
		exit(1); //中止程序 
	} 
	
	
	fpout=fopen("/home/zz/work/c_study/logout.txt","w"); //只供写入 
		if(fpout==NULL) //如果失败了 
		{ 
			printf("open logout error！"); 
			exit(1); //中止程序 
		} 
	//getc()用于在打开文件中获取一个字符 
	//while((ch=fgetc(fp))!=EOF)
	//	ch=fgetc(fp);//1
	//	putchar(ch); 
	//	ch=10;//2
	//	putchar(ch);
	//回车，ASCII码13
	//换行，ASCII码10
	//空格，ASCII码32
	//while((ch=fgetc(fp))!=EOF)
		
	memset(str, 0, strlen(str));
	while(!feof(fp))               //换成 while((ch=fgetc(fp))!=EOF) 这样一句也可以，就是不保险
	{
		ch=fgetc(fp);
		datatxt[n] = ch;
		//if ((datatxt[n] == 32) || (datatxt[n] == 10))
		if (datatxt[n] == 10)
		{
			cnt=cnt+1;
			for(i = n-1;i >= 0;i--)
			{
				if (datatxt[i]>='0' && datatxt[i]<='9') base[i] = datatxt[i]-'0'; 
				else if(datatxt[i]>='a' && datatxt[i]<='f') base[i] = datatxt[i]-'a'+10; 
				else if(datatxt[i]>='A' && datatxt[i]<='F') base[i] = datatxt[i]-'A'+10; 
				else return -1; 	
			}

			switch (n) {
				case 8:
					seed_temp = base[7]*1+base[6]*(1 << 4)+base[5]*(1 << 8)+base[4]*(1 << 12)+base[3]*(1 << 16)+base[2]*(1 << 20)+base[1]*(1 << 24)+base[0]*(1 << 28);
					break;
				case 7:
					seed_temp = base[6]*1+base[5]*(1 << 4)+base[4]*(1 << 8)+base[3]*(1 << 12)+base[2]*(1 << 16)+base[1]*(1 << 20)+base[0]*(1 << 24);
					break;
				case 6:
					seed_temp = base[5]*1+base[4]*(1 << 4)+base[3]*(1 << 8)+base[2]*(1 << 12)+base[1]*(1 << 16)+base[0]*(1 << 20);
					break;
				case 5:
					seed_temp = base[4]*1+base[3]*(1 << 4)+base[2]*(1 << 8)+base[1]*(1 << 12)+base[0]*(1 << 16);
					break;
				case 4:
					seed_temp = base[3]*1+base[2]*(1 << 4)+base[1]*(1 << 8)+base[0]*(1 << 12);
					break;
				case 3:
					seed_temp = base[2]*1+base[1]*(1 << 4)+base[0]*(1 << 8);
					break;
				case 2:
					seed_temp = base[1]*1+base[0]*(1 << 4);
					break;
				case 1:
					seed_temp = base[0]*1;
					break;
				default:
					//printf("Input number do not meet the requirement!\n");
					break;
			}
			
			if(cnt == 1) seed = ((seed_temp & 0xf)<< 28)+seed;
			else if (cnt == 2) seed = ((seed_temp & 0xf)<< 24)+seed;
			else if (cnt == 3) seed = ((seed_temp & 0xf)<< 20)+seed;
			else if (cnt == 4) seed = ((seed_temp & 0xf)<< 16)+seed;
			else if (cnt == 5) seed = ((seed_temp & 0xf)<< 12)+seed;
			else if (cnt == 6) seed = ((seed_temp & 0xf)<< 8)+seed;
			else if (cnt == 7) seed = ((seed_temp & 0xf)<< 4)+seed;
			else if (cnt == 8)
			{
				cnt = 0;
				seed = (seed_temp & 0xf)+seed;		
				srand(seed);
				randval = rand();//我自己试过rand()函数的返回值不能写成rand，编译器会把rand也当成函数，报错。所以我又改成了randval。
				printf("seed %x generate rand function value is %x\n",seed,randval);
				sprintf(str, "%08x", randval); 
				
				for(j=0;str[j] != 0 ;j++)
				{
					
					if (str[j] == 48) 
					{
						for(k=0;k<=3;k++)
						{
							fputc('0',fpout);
						}
					}
					else
					{
						#if 1
						if (str[j] > '7')
						{
							do
							{
								rem = randval%2;
								randval = randval/2;
								s[h] = rem;
								h++;
							}while(randval!=0);
							while(h>0)
							{
								--h;
								if (s[h]==0) fputc('0',fpout);
								else 
								{
									fputc('1',fpout);
									s[h]=0;
								}
							}
						}
						else if(str[j] > '3')
						{
							fputc('0',fpout);
							do
							{
								rem = randval%2;
								randval = randval/2;
								s[h] = rem;
								h++;
							}while(randval!=0);
							while(h>0)
							{
								--h;
								if (s[h]==0) fputc('0',fpout);
								else 
								{
									fputc('1',fpout);
									s[h]=0;
								}
							}
						}
						else if(str[j] > '1')
						{
							fputc('0',fpout);
							fputc('0',fpout);
							do
							{
								rem = randval%2;
								randval = randval/2;
								s[h] = rem;
								h++;
							}while(randval!=0);
							while(h>0)
							{
								--h;
								if (s[h]==0) fputc('0',fpout);
								else 
								{
									fputc('1',fpout);
									s[h]=0;
								}
							}
						}
						else if(str[j] == '1')
						{
							//printf("str is 1\n");
							fputc('0',fpout);
							fputc('0',fpout);
							fputc('0',fpout);
							do
							{
								rem = randval%2;
								randval = randval/2;
								s[h] = rem;
								h++;
							}while(randval!=0);
							while(h>0)
							{
								--h;
								if (s[h]==0) fputc('0',fpout);
								else 
								{
									fputc('1',fpout);
									s[h]=0;
								}
								
							}
						}
						#endif
						break;
					}
				}
				//#endif
				seed_temp = 0;
				seed = 0;
				memset(str, 0, strlen(str));
			}
			
			n = 0;
		}
		else{
			n = n+1;
		}	
	}
	
	//printf("9th char is %d",ch);
	//putchar(ch); 	
	fclose(fp); //关闭文件 
	return 0; 
} 
