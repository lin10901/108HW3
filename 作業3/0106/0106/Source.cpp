#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)   
long todec(char *source);
int getindex(char ch);
void print(struct cache cache[8][5]);
struct cache
{
	char  tag[10] = "\0";
	char  index[10] = "\0";
	char  tail[10] = "\0";
	int vaild = 0;
	int hotdata = 0;
};
int main(void)
{
	struct cache fifocache[8][5];
	struct cache lrucache[8][5];
	FILE *fp = NULL;
	int option = 0;
	errno_t err;

	while (option!=-1)
	{
		printf("option:1)FIFO 2) LRU -1)quiz:");
		scanf_s("%d", &option);

		if (option == -1)
			break;

		char tag[10] = "\0";
		char index[10] = "\0";
		int charindex = 0, hitcount = 0;

		if ((err = fopen_s(&fp, "test123.txt", "r")) != 0)
		{
			printf("open file error!!\n");
			system("PAUSE");
			exit(0);
		}
		else
		{
			while (!feof(fp))
			{
				char  ch = '\0';
				ch = fgetc(fp);
				while (ch != EOF)
				{

					if (charindex == 0 || charindex == 1)
						strncat(tag, &ch, 1);

					if (charindex == 2 || charindex == 3)
						strncat(index, &ch, 1);
					charindex++;

					if (charindex == 6)
					{
						printf("Input: %s%s\n", index, tag);
						charindex = 0;
						int n1 = todec(index);
						int n2 = 0;
						n1 = n1 % 8;
						n2 = -1;
						if (option == 1)
						{
						
							for (int i = 0; fifocache[n1][i].vaild != 0; i++)
							{
								if (strcmp(tag, fifocache[n1][i].tag) == 0 && strcmp(index, fifocache[n1][i].index) == 0)
								{
									printf("\nHit! %s %s\n", index, tag);
									hitcount++;
									n2 = -2;
									break;
								}

							}
							if (n2 == -1)
							{
								for (int i = 0; i < 4; i++)
								{
									if (fifocache[n1][i].vaild == 0)
									{
										n2 = i;
										break;
									}
								}
								if (n2 == -1)
								{
									for (int j = 0; j < 4; j++)
										fifocache[n1][j] = fifocache[n1][j + 1];
									
									strcpy(fifocache[n1][3].tag, tag);
									strcpy(fifocache[n1][3].index, index);
									fifocache[n1][3].vaild = 1;

								}
								else
								{
									strcpy(fifocache[n1][n2].tag, tag);
									strcpy(fifocache[n1][n2].index, index);
									fifocache[n1][n2].vaild = 1;

								}
							}
							print(fifocache);

						}

						if (option == 2)
						{
							for (int i = 0; lrucache[n1][i].vaild != 0; i++)
							{
								if (strcmp(tag, lrucache[n1][i].tag) == 0 && strcmp(index, lrucache[n1][i].index) == 0)
								{
									printf("\nHit! %s %s\n", index, tag);
									n2 = -2;
									lrucache[n1][i].hotdata++;
									hitcount++;
									break;
								}

							}
							if (n2 == -1)
							{
								for (int i = 0; i < 4; i++)
								{
									if (lrucache[n1][i].vaild == 0)
									{
										n2 = i;
										break;
									}//有空位
								}
							if (n2 == -1)
							{
								int min = lrucache[n1][0].hotdata;
								for (int j = 3; j >= 0; j--)
								{
									if (lrucache[n1][j].vaild == 1 && lrucache[n1][j].hotdata <= min)
									{
										min = lrucache[n1][j].hotdata;
										n2 = j;

									}
								}

							}//沒空位沒hit 找最少使用
							 
								if (n2 != -1)
								{
									strcpy(lrucache[n1][n2].tag, tag);
									strcpy(lrucache[n1][n2].index, index);
									lrucache[n1][n2].vaild = 1;
								}
							// }//找到空位

							}
							print(lrucache);
						}
						strcpy(tag, "\0");
						strcpy(index, "\0");


					}
					ch = fgetc(fp);

				}//!= Feof

			}
		}
		printf("Total Hit:%d\n", hitcount);
		fclose(fp);
	}
		
	system("PAUSE");
	return 0;
}
long todec(char *source)
{
	long sum = 0;
	long t = 1;
	int i, len;
	
	len = strlen(source);
	for (i = len - 1; i >= 0; i--)
	{
		sum += t * getIndexOfSigns(*(source + i));
		t *= 16;
	}

	return sum;
}


int getindex(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
	if (ch >= 'A' && ch <= 'F')
	{
		return ch - 'A' + 10;
	}
	if (ch >= 'a' && ch <= 'f')
	{
		return ch - 'a' + 10;
	}
	return -1;
}

void print(struct cache cache[8][5])
{


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cache[i][j].vaild == 1)
				printf("index:%d way: %d %s %s\n", i, j, cache[i][j].index, cache[i][j].tag);
			
		}
	}
	printf("\n---------------------\n");


}
