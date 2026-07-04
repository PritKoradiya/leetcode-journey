int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    int visited[100001] = {0};
    int queue[100001];
    int front = 0, rear = 0;
    int ans = INT_MAX;

    int *head = (int*)calloc(n + 1, sizeof(int));
    int *to = (int*)malloc((2 * roadsSize + 1) * sizeof(int));
    int *wt = (int*)malloc((2 * roadsSize + 1) * sizeof(int));
    int *next = (int*)malloc((2 * roadsSize + 1) * sizeof(int));

    int idx = 1;
    for (int i = 0; i < roadsSize; i++) {
        int a = roads[i][0];
        int b = roads[i][1];
        int d = roads[i][2];

        to[idx] = b;
        wt[idx] = d;
        next[idx] = head[a];
        head[a] = idx++;

        to[idx] = a;
        wt[idx] = d;
        next[idx] = head[b];
        head[b] = idx++;
    }

    queue[rear++] = 1;
    visited[1] = 1;

    while (front < rear) {
        int u = queue[front++];

        for (int i = head[u]; i != 0; i = next[i]) {
            ans = ans < wt[i] ? ans : wt[i];

            int v = to[i];
            if (!visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }

    free(head);
    free(to);
    free(wt);
    free(next);

    return ans;
}