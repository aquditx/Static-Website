#include <stdio.h>
#include <string.h>
#include <limits.h>

#define V 6  // Nodes (0=S, 1=A, 2=B, 3=C, 4=D, 5=T)
#define min(a,b) ((a < b) ? a : b)

int graph[V][V];

// Dfs -> augmenting path
int dfs(int u, int t, int visited[], int flow) {
    if (u == t)
        return flow;

    visited[u] = 1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && graph[u][v] > 0) {
            int bottleneck = dfs(v, t, visited, min(flow, graph[u][v]));
            if (bottleneck > 0) {
                // Update residual capacities
                graph[u][v] -= bottleneck; // forward directed path
                graph[v][u] += bottleneck; // backward directed path
                return bottleneck; // max capacity flowing through the edges
            }
        }
    }
    return 0;
}

// Ford–Fulkerson Algorithm
int fordFulkerson(int s, int t) {
    int max_flow = 0, flow;

    while (1) {
        int visited[V];
        memset(visited, 0, sizeof(visited));
        flow = dfs(s, t, visited, INT_MAX);

        if (flow == 0) // no augmenting path left
            break;

        max_flow += flow;
        printf("Augmenting path found with flow = %d, Total flow = %d\n", flow, max_flow);
    }

    return max_flow;
}

int main() {
    // Initialization
    memset(graph, 0, sizeof(graph));

    //(u, v, capacity)
    int edges[][3] = {
        {0, 1, 10}, {0, 2, 10},
        {1, 2, 2}, {1, 3, 4}, {1, 4, 8},
        {2, 4, 9},
        {3, 5, 10},
        {4, 3, 6}, {4, 5, 10}
    };

    int E = sizeof(edges) / sizeof(edges[0]);

    // adjacency matrix
    for (int i = 0; i < E; i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        graph[u][v] = w;
    }

    int source = 0; // S
    int sink = 5;   // T

    printf("\n--- Ford–Fulkerson Algorithm ---\n");
    int max_flow = fordFulkerson(source, sink);
    printf("\nMaximum possible flow: %d\n", max_flow);

    return 0;
}


