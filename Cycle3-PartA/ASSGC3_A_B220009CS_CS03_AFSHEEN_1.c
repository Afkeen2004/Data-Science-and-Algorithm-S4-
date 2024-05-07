#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

// Global variables for adjacency matrix, visited nodes, discovery and finish times, and other necessary arrays
int adjacency[MAX_NODES][MAX_NODES]; 
int visited[MAX_NODES];
int discovery[MAX_NODES];
int finish[MAX_NODES];
int time_count;
int discovery_time[MAX_NODES]; // discovery time of nodes
int low[MAX_NODES]; // 'low' node of nodes
int articulation_points[MAX_NODES]; // articulation points

// Function prototypes
void DFS_VISIT(int u, int p, int n, int* component_size);
int DFS(int n, int* component_sizes);
int number_of_connected_components(int n);
void size_of_components(int n);
int number_of_bridges(int size);
int min(int a, int b);
void dfs_articulation_points(int u, int p, int n);
int articulation_point_count(int n);
int convert(const char *str, int start, int end);

int main() {
    int num_nodes;
    char ch;
    scanf("%d", &num_nodes);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            adjacency[i][j] = 0;
        }
    }
    
    // Input graph edges
    for (int i = 0; i < num_nodes; i++) {
        char str[100];
        scanf(" %[^\n]", str);
        getchar();

        int index;
        int j = 0;
        while (str[j] != ' ' && str[j] != '\0') {
            j++;
        }
        index = convert(str, 0, j);
        if (str[j] == ' ') {
            j++;
        }

        while (str[j] != '\0') {
            int k = j;
            while (str[j] != ' ' && str[j] != '\0') {
                j++;
            }
            int v = convert(str, k, j);
            adjacency[index - 1][v - 1] = 1; 
            adjacency[v - 1][index - 1] = 1; 
            if (str[j] == ' ') {
                j++;
            }
        }
    }
    
    // Menu-driven program loop
    while(1) {
        scanf(" %c", &ch);
        if (ch == 'n') {
             printf("%d\n", number_of_connected_components(num_nodes));
        } else if (ch == 's') {
            size_of_components(num_nodes);
            printf("\n");
        } else if (ch == 'b') {
            printf("%d\n", number_of_bridges(num_nodes));
        } else if (ch == 'a') {
            printf("%d\n", articulation_point_count(num_nodes));
        } else if (ch == 't') {
            break;
        }
    }
    return 0;
}

// Depth First Search (DFS) function to visit nodes and find connected components
void DFS_VISIT(int u, int p, int n, int* component_size) {
    time_count++;
    discovery[u] = time_count;
    visited[u] = true;
    (*component_size)++;
    int min_back = discovery[u];
    for (int v = 0; v < n; v++) {
        if (adjacency[u][v]) {
            if (!visited[v]) {
                DFS_VISIT(v, u, n, component_size);
                min_back = min_back < discovery[v] ? min_back : discovery[v];
            } 
            else if (v != p) {
                min_back = min_back < discovery[v] ? min_back : discovery[v];
            }
        }
    }
    time_count++;
    finish[u] = time_count;
    if (p != -1) {
        min_back = min_back < finish[u] ? min_back : finish[u];
    }
}

// DFS function to find connected components and their sizes
int DFS(int n, int* component_sizes) {
    time_count = 0;
    int components_count = 0;
    for (int u = 0; u < n; u++) {
        visited[u] = false;
        discovery[u] = 0;
        finish[u] = 0;
    }
    for (int u = 0; u < n; u++) {
        if (!visited[u]) {
            int component_size = 0;
            components_count++;
            DFS_VISIT(u, -1, n, &component_size);
            component_sizes[components_count - 1] = component_size;
        }
    }
    return components_count;
}

// Function to calculate the number of connected components
int number_of_connected_components(int n) {
    int component_sizes[MAX_NODES] = {0}; 
    return DFS(n, component_sizes);
}

// Function to print the sizes of connected components
void size_of_components(int n) {
    int component_sizes[MAX_NODES] = {0};
    int connected_components = DFS(n, component_sizes);
    // Sort component sizes
    for (int i = 0; i < connected_components - 1; i++) {
        for (int j = 0; j < connected_components - i - 1; j++) {
            if (component_sizes[j] > component_sizes[j + 1]) {
                int temp = component_sizes[j];
                component_sizes[j] = component_sizes[j + 1];
                component_sizes[j + 1] = temp;
            }
        }
    }

    // Print component sizes in ascending order
    for (int i = 0; i < connected_components; i++) {
        printf("%d ", component_sizes[i]);
    }
}

// Function to find the number of bridges in the graph
int number_of_bridges(int size){
    int bridge_count = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(adjacency[i][j] != 0){
                adjacency[i][j] = 0;
                adjacency[j][i] = 0;
                int b = number_of_connected_components(size);
                adjacency[i][j] = 1;
                adjacency[j][i] = 1;
                int a = number_of_connected_components(size);
                if(a != b){
                    bridge_count++;
                }
            }
        }
    }
    if (bridge_count == 0)
        return -1;
    else 
        return bridge_count/2;
}

// Function to find the minimum of two integers
int min(int a, int b) {
    return a < b ? a : b;
}

// DFS function to find articulation points in the graph
void dfs_articulation_points(int u, int p, int n) {
    int children = 0;
    low[u] = discovery_time[u] = ++time_count;
    for (int v = 0; v < n; v++) {
        if (adjacency[u][v] && v != p) {
            if (!discovery_time[v]) {
                children++;
                dfs_articulation_points(v, u, n);
                low[u] = min(low[u], low[v]);
                
                // Check for articulation point condition
                if (p == -1 && children > 1) {
                    articulation_points[u] = 1; // condition 1: root with multiple children
                }
                if (p != -1 && low[v] >= discovery_time[u]) {
                    articulation_points[u] = 1; // condition 2: non-root with child v
                }
            } else
                low[u] = min(low[u], discovery_time[v]);
        }
    }
}

// Function to count articulation points in the graph
int articulation_point_count(int n) {
    time_count = 0;
    int count = 0;
    for (int u = 0; u < n; u++) {
        if (!discovery_time[u]) 
        {
            dfs_articulation_points(u, -1, n); // No need to check for children here
        }
    }
    for (int i = 0; i < n; i++) {   //INDEX FROM 0 TO N-1 AND 1 TO N MAKES A LOT OF DIFFERENCE PLS NOTE
        if (articulation_points[i])
            count++;
    }       
        
    if (count == 0)
        return -1;
    else 
        return count; 
}

// Function to convert string to integer
int convert(const char *str, int start, int end) {
    int result = 0;
    for (int i = start; str[i] != '\0' && i < end; i++) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

