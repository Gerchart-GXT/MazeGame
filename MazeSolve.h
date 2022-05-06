#include "MazeBuild.h"
#include <cstdio>
#include <unistd.h>
int dtx[] = { -1, 0, 1, 0 }, dty[] = { 0, 1, 0, -1 };
int dir[M][M];
bool visited[M][M];
PII path[M][M];
PII ans[N * N];
void printPath()
{
    for (int i = 0; i <= LEN_ROW * 2; i++) {
        for (int j = 0; j <= LEN_COL * 2; j++) {
            if (!map[i][j])
                putchar('*');
            else if (visited[i][j])
                putchar('@');
            else
                putchar(' ');
            putchar(' ');
        }
        puts("");
    }
}
void Dfs_Solve_Maze(int sx, int sy, int ex, int ey)
{
    PII stack[N * N];
    memset(stack, 0, sizeof stack);
    int top = -1;
    stack[++top] = { sx, sy };
    visited[sx][sy] = 1;
    while (top >= 0) {
        auto t = stack[top];

        bool flag = 0;
        int tx = t.fi + dtx[dir[t.fi][t.se]], ty = t.se + dty[dir[t.fi][t.se]];
        if (tx < 1 || tx >= LEN_ROW * 2 || ty < 1 || ty >= LEN_COL * 2)
            flag = 1;
        if (visited[tx][ty])
            flag = 1;
        if (!map[tx][ty])
            flag = 1;
        if (flag) {
            if (dir[t.fi][t.se] == 3)
                top--;
            else
                dir[t.fi][t.se]++;
            continue;
        }
        visited[tx][ty] = 1;
        stack[++top] = { tx, ty };
        if (tx == ex && ty == ey) {
            memset(visited, 0, sizeof visited);
            for (int j = 0; j <= top; j++) {
                auto t = stack[j];
                visited[t.fi][t.se] = 1;
                printPath();
                usleep(100000);
            }
            return;
        }
    }
    return;
}
void Bfs_Solve_Maze(int sx, int sy, int ex, int ey)
{
    PII queue[N * N];
    memset(queue, 0, sizeof queue);
    int hh = 0, tt = -1;
    queue[++tt] = { sx, sy };
    visited[sx][sy] = 1;
    while (hh <= tt) {
        auto t = queue[hh++];
        for (int i = 0; i < 4; i++) {
            int tx = t.fi + dtx[i], ty = t.se + dty[i];
            if (tx < 1 || tx >= LEN_ROW * 2 || ty < 1 || ty >= LEN_COL * 2)
                continue;
            if (visited[tx][ty])
                continue;
            if (!map[tx][ty])
                continue;
            visited[tx][ty] = 1;
            path[tx][ty] = t;
            queue[++tt] = { tx, ty };
            if (tx == ex && ty == ey) {
                int px = tx, py = ty;
                int idx = 0;
                while (px != sx || py != sy) {
                    ans[++idx] = { px, py };
                    auto tp = path[px][py];
                    px = tp.fi, py = tp.se;
                }
                ans[++idx] = { sx, sy };
                memset(visited, 0, sizeof visited);
                for (int j = idx; j > 0; j--) {
                    auto t = ans[j];
                    visited[t.fi][t.se] = 1;
                    printPath();
                    usleep(100000);
                }
                return;
            }
        }
    }
    return;
}