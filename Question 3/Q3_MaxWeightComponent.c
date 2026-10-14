#include <stdio.h>

typedef struct {
    long long s;
    int r;
} Node;

Node h[10000];
int hs = 0, p[1001], sz[1001];
long long w[1001], sum[1001];

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void push(long long s, int r) {
    int i = hs++;
    while (i > 0 && h[(i - 1) / 2].s < s) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h[i].s = s;
    h[i].r = r;
}

void pop() {
    Node x = h[--hs];
    int i = 0;
    while (2 * i + 1 < hs) {
        int c = 2 * i + 1;
        if (c + 1 < hs && h[c + 1].s > h[c].s) c++;
        if (h[c].s <= x.s) break;
        h[i] = h[c];
        i = c;
    }
    h[i] = x;
}

int main() {
    int V, K, E;

    printf("==================================================\n");
    printf(" DAA LAB 10 - QUESTION 3: MAX WEIGHT COMPONENT WITH SIZE LIMIT\n");
    printf("==================================================\n\n");

    printf("Enter number of vertices (V): ");
    scanf("%d", &V);
    printf("Enter size threshold (K): ");
    scanf("%d", &K);
    printf("Enter %d vertex weights: ", V);
    for (int i = 1; i <= V; i++) {
        scanf("%lld", &w[i]);
        p[i] = i;
        sz[i] = 1;
        sum[i] = w[i];
        if (K >= 1) push(w[i], i);
    }
    printf("Enter number of edges (E): ");
    scanf("%d", &E);
    printf("Enter %d edges (u v weight): ", E);

    int eu[1000], ev[1000], ew[1000];
    for (int i = 0; i < E; i++) scanf("%d %d %d", &eu[i], &ev[i], &ew[i]);

    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < E; i++) {
        int a = find(eu[i]), b = find(ev[i]);
        if (a != b) {
            if (sz[a] > sz[b]) {
                int t = a;
                a = b;
                b = t;
            }
            p[a] = b;
            sz[b] += sz[a];
            sum[b] += sum[a];
            if (sz[b] <= K) push(sum[b], b);
        }
        while (hs > 0 && !(p[h[0].r] == h[0].r && sum[h[0].r] == h[0].s && sz[h[0].r] <= K)) pop();
        printf("Edge (%d, %d): maximum component weight = %lld\n", eu[i], ev[i], hs > 0 ? h[0].s : 0);
    }
    printf("--------------------------------------------------\n");
    return 0;
}
