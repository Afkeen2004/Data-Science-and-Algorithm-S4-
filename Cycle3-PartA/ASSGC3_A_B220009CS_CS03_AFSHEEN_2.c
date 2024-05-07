#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct GraphStruct {
    int size;
    int **adjMatrix;
};

typedef struct GraphStruct *Graph;

Graph createGraph(int size);
void addEdge(Graph graph, int from, int to);
void freeGraph(Graph graph);
int detectCycles(Graph graph);
void depthFirstOrder(Graph graph, int vertex, int visited[], int stack[], int *top);
void depthFirstSearch(Graph graph, int vertex, int visited[], int scc[], int *count);
int stronglyConnectedComponents(Graph graph);

Graph createGraph(int size) {
    Graph g = (Graph)malloc(sizeof(struct GraphStruct));
    if (g == NULL) {
        return NULL;
    }
    g->size = size;
    g->adjMatrix = (int **)calloc(sizeof(int *), g->size);
    if (g->adjMatrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        g->adjMatrix[i] = (int *)calloc(sizeof(int), g->size);
        if (g->adjMatrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g->adjMatrix[j]);
            }
            free(g->adjMatrix);
            free(g);
            return NULL;
        }
    }
    return g;
}

void addEdge(Graph graph, int from, int to) {
    graph->adjMatrix[from][to] = 1;
}

void freeGraph(Graph graph) {
    if (graph->adjMatrix == NULL) {
        return;
    }
    for (int i = 0; i < graph->size; i++) {
        if (graph->adjMatrix[i] != NULL) {
            free(graph->adjMatrix[i]);
        }
    }
    free(graph->adjMatrix);
    free(graph);
}

int detectCycles(Graph graph) {
    int id[graph->size];
    int q[graph->size];

    for (int i = 0; i < graph->size; i++) {
        id[i] = 0;
    }
    int front = 0;
    int rear = 0;
    int count = 0;

    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            if (graph->adjMatrix[i][j]) {
                id[j]++;
            }
        }
    }

    for (int i = 0; i < graph->size; i++) {
        if (id[i] == 0) {
            q[rear++] = i;
            id[i] = -1;
        }
    }

    while (front != rear) {
        int node = q[front++];

        count++;
        for (int i = 0; i < graph->size; i++) {
            if (graph->adjMatrix[node][i] != 0) {
                id[i]--;
            }
            if (id[i] == 0) {
                q[rear++] = i;
                id[i] = -1;
            }
        }
    }

    if (count == graph->size) {
        return 1;
    }
    else {
        return -1;
    }
}

void depthFirstOrder(Graph graph, int vertex, int visited[], int stack[], int *top) {
    visited[vertex] = 1;

    for (int j = 0; j < graph->size; j++) {
        if (graph->adjMatrix[vertex][j] && !visited[j]) {
            depthFirstOrder(graph, j, visited, stack, top);
        }
    }

    stack[(*top)++] = vertex;
}

void depthFirstSearch(Graph graph, int vertex, int visited[], int scc[], int *count) {
    visited[vertex] = 1;
    scc[vertex] = *count;

    for (int j = 0; j < graph->size; j++) {
        if (graph->adjMatrix[vertex][j] && !visited[j]) {
            depthFirstSearch(graph, j, visited, scc, count);
        }
    }
}

int stronglyConnectedComponents(Graph graph) {
    int visited[graph->size];
    int stack[graph->size];
    int count = 0;
    int top = 0;
    for (int i = 0; i < graph->size; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->size; i++) {
        if (!visited[i]) {
            depthFirstOrder(graph, i, visited, stack, &top);
        }
    }

    Graph reverseGraph = createGraph(graph->size);
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            reverseGraph->adjMatrix[i][j] = graph->adjMatrix[j][i];
        }
    }

    for (int i = 0; i < graph->size; i++) {
        visited[i] = 0;
    }

    int scc[graph->size];
    while (top > 0) {
        int v = stack[--top];
        if (!visited[v]) {
            depthFirstSearch(reverseGraph, v, visited, scc, &count);
            count++;
        }
    }

    freeGraph(reverseGraph);

    return count;
}

int main() {
    int length;
    scanf("%d", &length);
    Graph graph = createGraph(length);
    int input;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            scanf("%d", &input);
            if (input) {
                addEdge(graph, i, j);
            }
        }
    }

    char choice;
    while (1) {
        scanf(" %c", &choice);
        if (choice == 't') {
            printf("%d\n", detectCycles(graph));
        }
        else if (choice == 'c') {
            printf("%d\n", stronglyConnectedComponents(graph));
        }
        else if (choice == 'x') {
            freeGraph(graph);
            break;
        }
    }
    return 1;
}

