
#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include <string.h>
#include "search.h"
int main(int agrc, char *agrv[])
{   
	if (agrc == 2 && (strcmp(agrv[1], "-h") == 0 || strcmp(agrv[1], "-help") == 0)){
		printf("帮助菜单:\n");
		printf("若输入：`./search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS`\n");
		printf("则会输出：显示以 `FILE_PATH` 为输入文件的图的统计信息,STATS_PARAMS可为：edges，vertices，freeman \n");
		printf("若输入：`./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT`\n");
		printf("SEARCH_PARAMS可为：DFS，BFS，Dijkstra\n");
		printf("则会输出：显示以 `FILE_PATH` 为输入文件的图中 从开始点 u 到 终点 v 的用 `SEARCH_PARAMS`蒜出来的最短路径\n");
		printf("若输入：`./search-cli -j`");
		printf("则会输出：蒜头大魔王");
	}else if (agrc == 2 && strcmp(agrv[1], "-j") == 0){
		printf("      ");
	}else if (agrc == 5 && (strcmp(agrv[1], "-g") == 0 || strcmp(agrv[1], "--graph") == 0) && (strcmp(agrv[3], "-s") == 0 || strcmp(agrv[3], "--stats") == 0)){
		if (strcmp(agrv[4], "edges") == 0){
			printf("图的边数为：%d",numberOfEdges(agrv[2]));
		}else if (strcmp(agrv[4], "vertices") == 0){
			printf("图的点数为：%d",numberOfVertices(agrv[2]));
		}else if (strcmp(agrv[4], "freeman") == 0) {
			printf("图的freemanNetworkCentrality为：%f",freemanNetworkCentrality(agrv[2]));
		}else{
			printf("输入错误\n");
		}
	}else if (agrc == 9 && (strcmp(agrv[1], "-g") == 0 || strcmp(agrv[1], "--graph") == 0) && (strcmp(agrv[3], "-sp") == 0 || strcmp(agrv[3], "--shortestpath") == 0) 
		&& strcmp(agrv[5], "-u") == 0 && strcmp(agrv[7], "-v") == 0)
	{	
		int u = 0, v = 0;
        for (int i = 0; i < strlen(agrv[6]); i++)
        {
            u *= 10;
            u += agrv[6][i] - '0';
        } 
        for (int i = 0; i < strlen(agrv[8]); i++)
        {
            v *= 10;
            v += agrv[8][i] - '0';
        }
    
        int n = 0;
        int *answer = shortestPath(u, v, agrv[4], agrv[2]);
        while (answer[n] != v)
        {
            printf("%d -> ", answer[n]);
            n++;
        } 
        printf("%d\n", answer[n]);
    }else {
		printf("输入错误\n");
	}
}
