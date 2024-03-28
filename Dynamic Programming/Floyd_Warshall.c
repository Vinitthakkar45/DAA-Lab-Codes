#include <stdio.h>

#define V 4
#define INF 99999

void printSolution(int dist[][V],int k)
{
    if(k==V){
	printf(
		"\nThe following matrix shows the shortest distances"
		" between every pair of vertices \n\n");
    }
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", dist[i][j]);
		}
		printf("\n");
	}
}

void floydWarshall(int dist[][V])
{
	int i, j, k;

	for (k = 0; k < V; k++) {
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
        printf("\nA%d\n",k+1);
        printSolution(dist,k);
	}
	printSolution(dist,k);
}

int main()
{
	int matrix[V][V] = { { 0, 3, INF, 7 },
						{ 8, 0, 2, 15 },
						{ 5, 8, 0, 1 },
						{ 2, 5, INF, 0 } };

	floydWarshall(matrix);
	return 0;
}
