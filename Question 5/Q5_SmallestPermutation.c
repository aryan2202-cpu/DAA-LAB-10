#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int root, key;
} Pair;

int p[1001];

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

int cmp(const void *a, const void *b) {
    Pair *x = (Pair *)a, *y = (Pair *)b;
    return x->root != y->root ? x->root - y->root : x->key - y->key;
}

int main() {
    int n, E, A[1001], res[1001];
    Pair pos[1001], val[1001];

    printf("==================================================\n");
    printf(" DAA LAB 10 - QUESTION 5: SMALLEST PERMUTATION BY SWAPS\n");
    printf("==================================================\n\n");

    printf("Enter size of permutation (n): ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        p[i] = i;
    }
    printf("Enter number of allowed swaps (E): ");
    scanf("%d", &E);
    printf("Enter %d swaps (u v): ", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        p[find(u)] = find(v);
    }

    for (int i = 1; i <= n; i++) {
        int r = find(i);
        pos[i - 1].root = val[i - 1].root = r;
        pos[i - 1].key = i;
        val[i - 1].key = A[i];
    }
    qsort(pos, n, sizeof(Pair), cmp);
    qsort(val, n, sizeof(Pair), cmp);
    for (int k = 0; k < n; k++) res[pos[k].key] = val[k].key;

    printf("\n--------------------------------------------------\n");
    printf("Smallest permutation:");
    for (int i = 1; i <= n; i++) printf(" %d", res[i]);
    printf("\n--------------------------------------------------\n");
    return 0;
}
