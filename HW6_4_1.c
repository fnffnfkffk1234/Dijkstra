//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];		/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */
int previous[MAX_VERTICES];		/* 정점의 최단경로 상에 있는 그 정점의 바로 앞 정점*/

void graph_init(GraphType *g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;
}
void read_graph(GraphType *g, char *filename)
{
	int number, u, v, weight;
	FILE *fp;
    fp = fopen(filename, "rt");
	if (fp == NULL) 
	{
		printf("file %s open error!\n", filename);
		return;
	}
     // 코드 삽입
	fscanf(fp, "%d", &number);
	g->n = number;

	while (fscanf(fp, "%d %d %d", &u, &v, &weight) != EOF) {
		g->adj_mat[u][v] = weight;
		g->adj_mat[v][u] = weight;
	}
    fclose(fp);
}
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
/*void print_status(GraphType* g)
{
	static int step = 1;
	int i;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("        found:    ");
	for (i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}*/
void print_path(int start, int end)
{
	if (start == end)
		printf("%d", start);
	else {
		print_path(start, previous[end]);
		printf("-> %d ", end);
	}
}
void shortest_path(GraphType* g, int start)
{
	int i, u, w, j;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->adj_mat[start][i];
		found[i] = FALSE;
		previous[i] = start;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		print_path(start, u);
		printf("<%d>\n", distance[u]);
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->adj_mat[u][w] < distance[w]) {
					distance[w] = distance[u] + g->adj_mat[u][w];
					previous[w] = u;
				}
			}
 		}
	}
}
int main()
{
	GraphType g;		// 입력 그래프
	
	graph_init(&g);
	read_graph(&g, "input.txt");
	
	shortest_path(&g, 0);	//시작 정점
}