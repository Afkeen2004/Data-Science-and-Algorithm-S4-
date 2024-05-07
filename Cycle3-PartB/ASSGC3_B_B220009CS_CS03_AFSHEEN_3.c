// C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[], int len)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < len; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", dist[i]);
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int *graph, int src, int len)
{
    int dist[len]; // The output array. dist[i] will hold the
    // shortest
    // distance from src to i

    bool sptSet[len]; // sptSet[i] will be true if vertex i is
    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < len; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < len - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet, len);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < len; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u * len + v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u * len + v] < dist[v])
                dist[v] = dist[u] + graph[u * len + v];
    }

    // print the constructed distance array
    printSolution(dist, len);
}

// driver's code
int main()
{
    int len, input, num, sum = 0;
    char c;
    scanf("%d", &len);
    int g[len][len];
    int rank[len];
    int parent[len];

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            g[i][j] = 0;
        }
        rank[i] = 0;
        parent[i] = i;
    }

    for (int i = 0; i < len; i++) {
        num = 0;
        scanf("%d ", &input);
        while ((c = getchar()) != '\n') {
            if (c != ' ') {
                num = num * 10 + (c - '0');
            } else {
                g[input - 1][num - 1] = 1;
                num = 0;
            }
        }
        g[input - 1][num - 1] = 1;
    }

    for (int i = 0; i < len; i++) {
        num = 0;
        int l;
        int idx = 0;
        scanf("%d ", &input);
        while ((c = getchar()) != '\n') {
            if (c != ' ') {
                num = num * 10 + (c - '0');
                l = 1;
            } else if (l == 1) {
                for (int j = idx; j < len; j++) {
                    if (g[input - 1][j] == 1) {
                        g[i][j] = num;
                        num = 0;
                        idx = j + 1; // Increment idx to skip the current space
                        break;
                    }
                }
                l = 0; // Reset flag after assigning weight
            }
        }

        for (int j = idx; j < len; j++) {
            if (g[i][j] == 1) {
                g[i][j] = num;
            }
        }
    }

    int start;
    scanf("%d", &start);
    dijkstra(&g[0][0], start - 1, len);

    return 0;
}

