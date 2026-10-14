#include <stdio.h>

int p[101], adj[101][101], on[101], order[101];
long long w[101], sum[101], res[101];

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

int main() {
    int V, E;
    long long best = 0;

    printf("==================================================\n");
    printf(" DAA LAB 10 - QUESTION 4: REVERSE TIME-STEP DSU\n");
    printf("==================================================\n\n");

    printf("Enter number of vertices (V): ");
    scanf("%d", &V);
    printf("Enter %d vertex weights: ", V);
    for (int i = 1; i <= V; i++) scanf("%lld", &w[i]);
    printf("Enter number of edges (E): ");
    scanf("%d", &E);
    printf("Enter %d edges (u v): ", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }
    printf("Enter deletion order of %d vertices: ", V);
    for (int i = 1; i <= V; i++) scanf("%d", &order[i]);

    res[V] = 0;
    for (int i = V; i >= 2; i--) {
        int x = order[i];
        on[x] = 1;
        p[x] = x;
        sum[x] = w[x];
        for (int y = 1; y <= V; y++) {
            if (adj[x][y] && on[y]) {
                int a = find(x), b = find(y);
                if (a != b) {
                    p[a] = b;
                    sum[b] += sum[a];
                }
            }
        }
        if (sum[find(x)] > best) best = sum[find(x)];
        res[i - 1] = best;
    }

    printf("\n--------------------------------------------------\n");
    for (int i = 1; i <= V; i++) printf("Delete vertex %d: maximum component sum = %lld\n", order[i], res[i]);
    printf("--------------------------------------------------\n");
    return 0;
}
