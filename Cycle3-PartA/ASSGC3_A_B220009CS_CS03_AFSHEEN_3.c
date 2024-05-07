#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Node structure for adjacency list
struct Node {
    int vertex;
    struct Node *next;
};

// Graph structure
struct Graph {
    int num_vertices;
    struct Node **adj_list;
};

// Function prototypes
struct Graph *createGraph(int num_vertices);
struct Node *createNode(int vertex);
struct Graph *insertEdge(struct Graph *graph, int source, int destination);
struct Graph *createAdjacencyList(struct Graph *graph, char input[]);
void dfs_allpaths(struct Graph *graph, int current_vertex, int end_vertex, int visited[], int path[], int path_index);
void find_all_paths(struct Graph *graph, int source, int destination);
void dfs(struct Graph *graph, int start_vertex, int visited[]);
int helper(struct Graph *graph, int current_vertex, int parent, int visited[]);
int is_cyclic(struct Graph *graph);
int is_valid_tree(struct Graph *graph);

int main() {
    int vertices;
    scanf("%d", &vertices);
    scanf("\n");
    struct Graph *graph = createGraph(vertices);
    int k = vertices;
    while (k > 0) {
        char input[100];
        fgets(input, 100, stdin);
        graph = createAdjacencyList(graph, input);
        k--;
    }

    char c;
    int x, y;
    while (1) {
        scanf(" %c", &c); // Added space before %c to consume whitespace characters
        switch (c) {
            case 'a':
                scanf("%d", &x);
                scanf("%d", &y);
                find_all_paths(graph, x, y);
                break;
            case 't':
                x = is_valid_tree(graph);
                printf("%d \n", x);
                break;
            case 'x':
                break;
        }
        if (c == 'x') {
            break;
        }
    }

    return 0;
}

// Function to create a new graph with given number of vertices
struct Graph *createGraph(int num_vertices) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->num_vertices = num_vertices;
    graph->adj_list = (struct Node **)malloc(sizeof(struct Node *) * num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

// Function to create a new node
struct Node *createNode(int vertex) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->vertex = vertex;
    temp->next = NULL;
    return temp;
}

// Function to insert an edge into the graph
struct Graph *insertEdge(struct Graph *graph, int source, int destination) {
    struct Node *p = graph->adj_list[source];
    if (p == NULL) {
        p = createNode(destination);
        graph->adj_list[source] = p;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = createNode(destination);
    }
    return graph;
}

// Function to create adjacency list representation of the graph
struct Graph *createAdjacencyList(struct Graph *graph, char input[]) {
    int i = 0;
    int source = 0, destination = 0;
    while (input[i] != ' ') {
        source = source * 10 + (int)(input[i] - '0');
        i++;
    }
    while (input[i] != '\n' && input[i] == ' ') {
        i++;
        destination = 0;
        while (input[i] >= '0' && input[i] <= '9') {
            destination = destination * 10 + (int)(input[i] - '0');
            i++;
        }
        graph = insertEdge(graph, source, destination);
    }
    return graph;
}

// Function to find all paths between two vertices
void dfs_allpaths(struct Graph *graph, int current_vertex, int end_vertex, int visited[], int path[], int path_index) {
    visited[current_vertex] = 1;
    path[path_index] = current_vertex;
    path_index++;

    if (current_vertex == end_vertex) {
        // Print the current path
        for (int i = 0; i < path_index; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        struct Node *p = graph->adj_list[current_vertex];
        while (p) {
            if (visited[p->vertex] == 0) {
                dfs_allpaths(graph, p->vertex, end_vertex, visited, path, path_index);
            }
            p = p->next;
        }
    }

    visited[current_vertex] = 0;
    path_index--;
}

// Function to find all paths between two vertices
void find_all_paths(struct Graph *graph, int source, int destination) {
    int *visited = (int *)malloc(sizeof(int) * graph->num_vertices);
    int *path = (int *)malloc(sizeof(int) * graph->num_vertices);
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    dfs_allpaths(graph, source, destination, visited, path, 0);

    free(visited);
    free(path);
}

// Function for depth-first search traversal
void dfs(struct Graph *graph, int start_vertex, int visited[]) {
    visited[start_vertex] = 1;
    struct Node *p = graph->adj_list[start_vertex];
    while (p) {
        if (!visited[p->vertex]) {
            dfs(graph, p->vertex, visited);
        }
        p = p->next;
    }
}

// Helper function for detecting cycles in the graph
int helper(struct Graph *graph, int current_vertex, int parent, int visited[]) {
    visited[current_vertex] = 1;
    struct Node *p = graph->adj_list[current_vertex];
    while (p) {
        if (!visited[p->vertex]) {
            if (helper(graph, p->vertex, current_vertex, visited)) {
                return 1;
            }
        } else if (p->vertex != parent) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

// Function to check if the graph is cyclic
int is_cyclic(struct Graph *graph) {
    int *visited = (int *)malloc(sizeof(int) * graph->num_vertices);
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            if (helper(graph, i, -1, visited)) {
                free(visited);
                return 1;
            }
        }
    }
    free(visited);
    return 0;
}

// Function to check if the graph is a valid tree
int is_valid_tree(struct Graph *graph) {
    int visited[graph->num_vertices];
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    int root_count = 0;
    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            root_count++;
            dfs(graph, i, visited);
        }
    }
    if (root_count != 1) {
        return -1; // Not a valid tree (multiple roots)
    }

    for (int i = 0; i < graph->num_vertices; i++) {
        if (!visited[i]) {
            return -1; // Not a valid tree (not fully connected)
        }
    }

    if (is_cyclic(graph)) {
        return -1; // Not a valid tree (contains cycles)
    }

    int edge_count = 0;
    for (int i = 0; i < graph->num_vertices; i++) {
        struct Node *p = graph->adj_list[i];
        while (p) {
            edge_count++;
            p = p->next;
        }
    }
    if (edge_count <= graph->num_vertices - 1) {
        return -1; // Not a valid tree (does not have n-1 edges)
    }

    return 1; // Valid tree
}
