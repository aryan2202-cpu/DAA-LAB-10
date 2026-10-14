#include <stdio.h>
#include <stdlib.h>

int *p, *sz;

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

int main() {
    int R, C, k, count = 0;
    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

    printf("==================================================\n");
    printf(" DAA LAB 10 - QUESTION 2: ISLANDS IN A GRID\n");
    printf("==================================================\n\n");

    printf("Enter grid rows and columns (R C): ");
    scanf("%d %d", &R, &C);
    printf("Enter number of land cells to add (k): ");
    scanf("%d", &k);

    p = (int *)malloc(R * C * sizeof(int));
    sz = (int *)malloc(R * C * sizeof(int));
    char *land = (char *)calloc(R * C, sizeof(char));
    int *rr = (int *)malloc(k * sizeof(int));
    int *cc = (int *)malloc(k * sizeof(int));
    for (int i = 0; i < R * C; i++) {
        p[i] = i;
        sz[i] = 1;
    }

    printf("Enter %d positions (r c): ", k);
    for (int i = 0; i < k; i++) scanf("%d %d", &rr[i], &cc[i]);

    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < k; i++) {
        int id = rr[i] * C + cc[i];
        if (!land[id]) {
            land[id] = 1;
            count++;
            for (int d = 0; d < 4; d++) {
                int nr = rr[i] + dr[d], nc = cc[i] + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || !land[nr * C + nc]) continue;
                int a = find(id), b = find(nr * C + nc);
                if (a != b) {
                    if (sz[a] > sz[b]) {
                        int t = a;
                        a = b;
                        b = t;
                    }
                    p[a] = b;
                    sz[b] += sz[a];
                    count--;
                }
            }
        }
        printf("Add (%d, %d): islands = %d\n", rr[i], cc[i], count);
    }
    printf("--------------------------------------------------\n");

    free(p);
    free(sz);
    free(land);
    free(rr);
    free(cc);
    return 0;
}
