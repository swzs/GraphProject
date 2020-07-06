nclude <stdio.h>
#include "stats.h"
#include <stdlib.h>
#include <fstream>

int freeman_num[MAXV/2];
int numberOfEdges(char name[])
{
	FILE *fd;
	int flag = 0, file_row = 0, count = 0;
    FILE* fp=fopen(name,"r");
	if(fp==NULL)
	{
		printf("无文件");
		return -1;
	}
    while(!feof(fp))
    {
        flag = fgetc(fp);
        if(flag == '\n')
        count++;
    }
    file_row = count + 1;
	fclose(fp);
	return file_row;
}




int numberOfVertices(char name[])
{	 char ver[MAXV/2];
	 int u , v , w ;
	 int m = 0;
	 memset(ver, 0, sizeof(ver));
     FILE *fp;
     fp=fopen(name,"r");
	 if(fp==NULL)
	 {
		 printf("无文件");
		 return -1;
	 }
	 while (fscanf(fp,"%d%d%d", &u, &v, &w) != EOF){	
		 ver[u] = '1';
		 ver[v] = '1';
		 //freeman_num[u]++;
		 freeman_num[v]++;
		 }
	 for (int i = 0; i <= 500000; i++){
		 if (ver[i] == '1'){
			 m++;
		 }
	 }
	 return m;
}



float freemanNetworkCentrality(char name[])
{
	memset (freeman_num, 0, sizeof(freeman_num));
	long long m = 0;
	long long max = 0;
	long long n = (long long)numberOfVertices(name);

	for (int i = 0; i < n; i++)
    {
        if (freeman_num[i] > max)
        {
            max = freeman_num[i];
        }    
    }
    for (int i = 0; i < n; i++)
    {
        m += max - freeman_num[i];   
    }
    return (float)m / ((n - 1) * (n - 2));
}
