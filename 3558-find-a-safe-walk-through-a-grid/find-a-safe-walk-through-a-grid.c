#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int r, c;
} Node;

bool findSafeWalk(int** grid, int gridSize, int* gridColSize, int health) {
    int m = gridSize;
    int n = gridColSize[0];
    int total = m * n;
    
    int *dist = (int*)malloc(total * sizeof(int));
    for (int i = 0; i < total; i++) dist[i] = INT_MAX;
    
    Node *deque = (Node*)malloc((total * 4 + 5) * sizeof(Node));
    int front = total * 2;
    int back = total * 2;
    
    dist[0] = grid[0][0];
    deque[back++] = (Node){0, 0};
    
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    while (front < back) {
        Node cur = deque[front++];
        int r = cur.r;
        int c = cur.c;
        int idx = r * n + c;
        
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            
            int nidx = nr * n + nc;
            int cost = grid[nr][nc];
            
            if (dist[idx] + cost < dist[nidx]) {
                dist[nidx] = dist[idx] + cost;
                
                if (cost == 0) {
                    deque[--front] = (Node){nr, nc};
                } else {
                    deque[back++] = (Node){nr, nc};
                }
            }
        }
    }
    
    bool ans = dist[total - 1] < health;
    
    free(dist);
    free(deque);
    
    return ans;
}