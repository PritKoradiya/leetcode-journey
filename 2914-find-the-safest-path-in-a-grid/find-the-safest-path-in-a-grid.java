class Solution {
    public int maximumSafenessFactor(List<List<Integer>> grid) {
        int n = grid.size();
        int[][] safeness = new int[n][n];
        for (int[] row : safeness) Arrays.fill(row, -1);

        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};

        Queue<int[]> bfsQueue = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid.get(i).get(j) == 1) {
                    safeness[i][j] = 0;
                    bfsQueue.offer(new int[]{i, j});
                }
            }
        }

        while (!bfsQueue.isEmpty()) {
            int[] cur = bfsQueue.poll();
            int cx = cur[0], cy = cur[1];
            for (int d = 0; d < 4; d++) {
                int nx = cx + dx[d], ny = cy + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && safeness[nx][ny] == -1) {
                    safeness[nx][ny] = safeness[cx][cy] + 1;
                    bfsQueue.offer(new int[]{nx, ny});
                }
            }
        }

        boolean[][] visited = new boolean[n][n];
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        pq.offer(new int[]{safeness[0][0], 0, 0});

        int result = 0;

        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int val = top[0], x = top[1], y = top[2];

            if (visited[x][y]) continue;
            visited[x][y] = true;

            if (x == n - 1 && y == n - 1) {
                result = val;
                break;
            }

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                    int newSafeness = Math.min(val, safeness[nx][ny]);
                    pq.offer(new int[]{newSafeness, nx, ny});
                }
            }
        }

        return result;
    }
}