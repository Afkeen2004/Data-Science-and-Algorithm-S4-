#include <stdio.h> 
#include <stdlib.h> 

// Comparator function to use in sorting 
int comparator(const void* p1, const void* p2) 
{ 
    const int(*x)[3] = p1; 
    const int(*y)[3] = p2; 

    return (*x)[2] - (*y)[2]; 
} 

// Initialization of parent[] and rank[] arrays 
void makeSet(int parent[], int rank[], int n) 
{ 
    for (int i = 0; i < n; i++) { 
        parent[i] = i; 
        rank[i] = 0; 
    } 
} 

// Function to find the parent of a node 
int findParent(int parent[], int component) 
{ 
    if (parent[component] == component) 
        return component; 

    return parent[component] = findParent(parent, parent[component]); 
} 

// Function to unite two sets 
void unionSet(int u, int v, int parent[], int rank[], int n) 
{ 
    // Finding the parents 
    u = findParent(parent, u); 
    v = findParent(parent, v); 

    if (rank[u] < rank[v]) { 
        parent[u] = v; 
    } 
    else if (rank[u] > rank[v]) { 
        parent[v] = u; 
    } 
    else { 
        parent[v] = u; 

        // Since the rank increases if 
        // the ranks of two sets are same 
        rank[u]++; 
    } 
} 

// Function to find the MST 
void kruskalAlgo(int n, int graph[][n]) 
{ 
    // Create an edge list from the adjacency matrix
    int num_edges = 0;
    int edge[n*n][3];
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (graph[i][j] != 0) {
                edge[num_edges][0] = i;
                edge[num_edges][1] = j;
                edge[num_edges][2] = graph[i][j];
                num_edges++;
            }
        }
    }

    // First we sort the edge array in ascending order 
    // so that we can access minimum distances/cost 
    qsort(edge, num_edges, sizeof(edge[0]), comparator); 

    int parent[n]; 
    int rank[n]; 

    // Function to initialize parent[] and rank[] 
    makeSet(parent, rank, n); 

    // To store the minimum cost 
    int minCost = 0;  
    for (int i = 0; i < num_edges; i++) { 
        int v1 = findParent(parent, edge[i][0]); 
        int v2 = findParent(parent, edge[i][1]); 
        int wt = edge[i][2]; 

        // If the parents are different that 
        // means they are in different sets so 
        // union them 
        if (v1 != v2) { 
            unionSet(v1, v2, parent, rank, n); 
            minCost += wt;  
        } 
    } 
    printf("%d\n", minCost); 
} 

// Driver code 
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
                g[input][num] = 1;
                num = 0;
            }
        }
        g[input][num] = 1;
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
		        if (g[input][j] == 1) {
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
    kruskalAlgo(len, g);
}
