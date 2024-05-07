#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_V 100

int minKey(int key[], bool mstSet[], int V);
void printEdgeTraversal(int parent[], int V, int k);
int sumWeights(int parent[], int graph[][MAX_V], int V);
void primMST(int graph[][MAX_V], int V, int startNode, char ch[]);

int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printEdgeTraversal(int arr[], int V, int k) {
    for (int i = 0; i < k;i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int sumWeights(int parent[], int graph[][MAX_V], int V) {
    int sum = 0;
    for (int i = 0; i < V; i++)
        sum += graph[i][parent[i]];
    return sum;
}

void primMST(int graph[][MAX_V], int V, int startNode, char ch[]) {
    int parent[V];
    int key[V];
    bool mstSet[V];
    int arr[MAX_V];
    
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false, parent[startNode] = -1;
 
    key[startNode] = 0;
    int k = 0;
    for (int count = 0; count < V ; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;
        if (parent[u] != -1){
            arr[k++]=parent[u];
            arr[k++]=u;
        }
        for (int v = 0; v < V; v++)
            if (graph[u][v]> 0 && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    
    
    if(strcmp(ch, "t") == 0){
        printf("%d\n", sumWeights(parent, graph, V));
    }else{
        printEdgeTraversal(arr, V, k);
    }
}

int main() {
    int V, startNode;
    int graph[MAX_V][MAX_V];
    char ch[5];
    
    scanf("%d", &V); //no of vertices
    getchar();

    for (int i = 0; i < V; i++) {  //inputting values
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    while(1){
        scanf("%s", ch);
        if (strcmp(ch, "x") == 0){
            break;
        }else if(strcmp(ch, "t") == 0){
            primMST(graph, V, 0, ch);
         }else{
            int st = ch[2]-'0';
            primMST(graph, V, st, ch);
         }
    }
                    
}

