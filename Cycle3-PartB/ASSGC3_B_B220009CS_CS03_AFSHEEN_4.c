#include <stdio.h>

#define INF 99999

void floydWarshall(int graph[][100], int n) {
    int dist[100][100];
    int i, j, k;

    // Initialize dist matrix with the graph
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Applying Floyd-Warshall algorithm
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][k] != -1 && dist[k][j] != -1) { // Skip if there's no path through k
                    if (dist[i][j] == -1 || dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Printing the shortest paths
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, i, j;
    int graph[100][100];

    // Input number of nodes
    scanf("%d", &n);

    // Input adjacency matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, n);

    return 0;
}

