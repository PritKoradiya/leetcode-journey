/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MOD 1000000007

int* pathsWithMaxScore(char** board, int boardSize, int* returnSize) {
    int n = boardSize;
    int score[101][101] = {0};
    int path[101][101] = {0};

    int dx[3] = {0, -1, -1};
    int dy[3] = {-1, 0, -1};

    path[n - 1][n - 1] = 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (path[i][j] == 0) continue;

            for (int k = 0; k < 3; k++) {
                int x = i + dx[k];
                int y = j + dy[k];

                if (x < 0 || y < 0 || board[x][y] == 'X')
                    continue;

                int sum = score[i][j];
                if (board[x][y] != 'E')
                    sum += board[x][y] - '0';

                if (sum > score[x][y]) {
                    score[x][y] = sum;
                    path[x][y] = path[i][j];
                } else if (sum == score[x][y]) {
                    path[x][y] = (path[x][y] + path[i][j]) % MOD;
                }
            }
        }
    }

    int* ans = (int*)malloc(2 * sizeof(int));
    ans[0] = path[0][0] ? score[0][0] : 0;
    ans[1] = path[0][0];
    *returnSize = 2;
    return ans;
}