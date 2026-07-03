#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 4000000000000000000LL

static bool canReach(int n, int *head, int *to, int *next, int *cost,
                     int *topo, bool *online, long long k, int limit) {
    long long *dist = (long long *)malloc(sizeof(long long) * n);

    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[0] = 0;

    for (int i = 0; i < n; i++) {
        int u = topo[i];

        if (!online[u] || dist[u] == INF) continue;

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];

            if (!online[v]) continue;
            if (cost[e] < limit) continue;

            long long nd = dist[u] + cost[e];

            if (nd < dist[v]) {
                dist[v] = nd;
            }
        }
    }

    bool ok = dist[n - 1] <= k;
    free(dist);

    return ok;
}

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize,
                     bool* online, int onlineSize, long long k) {
    int n = onlineSize;

    int *head = (int *)malloc(sizeof(int) * n);
    int *to = (int *)malloc(sizeof(int) * edgesSize);
    int *next = (int *)malloc(sizeof(int) * edgesSize);
    int *cost = (int *)malloc(sizeof(int) * edgesSize);
    int *indeg = (int *)calloc(n, sizeof(int));
    int *topo = (int *)malloc(sizeof(int) * n);
    int *queue = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) head[i] = -1;

    int maxCost = 0;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int c = edges[i][2];

        to[i] = v;
        cost[i] = c;
        next[i] = head[u];
        head[u] = i;

        indeg[v]++;

        if (c > maxCost) maxCost = c;
    }

    int front = 0, back = 0;

    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) queue[back++] = i;
    }

    int idx = 0;

    while (front < back) {
        int u = queue[front++];
        topo[idx++] = u;

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];

            indeg[v]--;

            if (indeg[v] == 0) {
                queue[back++] = v;
            }
        }
    }

    if (!canReach(n, head, to, next, cost, topo, online, k, 0)) {
        free(head);
        free(to);
        free(next);
        free(cost);
        free(indeg);
        free(topo);
        free(queue);
        return -1;
    }

    int left = 0, right = maxCost;
    int ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canReach(n, head, to, next, cost, topo, online, k, mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    free(head);
    free(to);
    free(next);
    free(cost);
    free(indeg);
    free(topo);
    free(queue);

    return ans;
}