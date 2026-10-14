#include <stdio.h>

int p[1001], rel[1001], sz[1001];

int find(int x) {
    if (p[x] == x) return x;
    int r = find(p[x]);
    rel[x] ^= rel[p[x]];
    p[x] = r;
    return r;
}

int main() {
    int V, E, eu[1000], ev[1000], added = 0, skipped = 0;

    printf("==================================================\n");
    printf(" DAA LAB 10 - QUESTION 1: ONLINE BIPARTITENESS TESTING\n");
    printf("==================================================\n\n");

    printf("Enter number of vertices (V): ");
    scanf("%d", &V);
    printf("Enter number of edges (E): ");
    scanf("%d", &E);
    printf("Enter %d edges (u v): ", E);
    for (int i = 0; i < E; i++) scanf("%d %d", &eu[i], &ev[i]);

    for (int i = 1; i <= V; i++) {
        p[i] = i;
        sz[i] = 1;
    }

    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < E; i++) {
        int u = eu[i], v = ev[i];
        int ru = find(u), rv = find(v);
        if (ru == rv) {
            if (rel[u] == rel[v]) {
                printf("Edge (%d, %d): creates an odd cycle, skipped\n", u, v);
                skipped++;
                continue;
            }
        } else {
            if (sz[ru] > sz[rv]) {
                int t = ru;
                ru = rv;
                rv = t;
            }
            p[ru] = rv;
            rel[ru] = rel[u] ^ rel[v] ^ 1;
            sz[rv] += sz[ru];
        }
        printf("Edge (%d, %d): added, graph is still bipartite\n", u, v);
        added++;
    }
    printf("Edges added: %d, edges skipped: %d\n", added, skipped);
    printf("--------------------------------------------------\n");
    return 0;
}
