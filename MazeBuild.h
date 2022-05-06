#include "radam&connect.h"
#include <stdlib.h>
void printMap(Adjacentlist (*head)[M])
{
    // 这里用Adjacentlist来重新构图
    memset(map, 0, sizeof map);
    for (int i = 1; i < LEN_ROW * 2; i += 2)
        for (int j = 1; j < LEN_COL * 2; j += 2) {
            auto tnext = &head[i][j];
            map[i][j] = 1;
            while (tnext->getNext() != nullptr) {
                tnext = tnext->getNext();
                map[i - (i - tnext->getX()) / 2][j - (j - tnext->getY()) / 2] = 1;
            }
        }
    for (int i = 0; i <= LEN_ROW * 2; i++) {
        for (int j = 0; j <= LEN_COL * 2; j++) {
            if (map[i][j])
                putchar(' ');
            else
                putchar('*');
            putchar(' ');
        }
        puts("");
    }
}
void dfs_Build_Maze(Adjacentlist (*head)[M], int x, int y)
{
    map[x][y] = true;
    auto nxt = getRandomNear(head, x, y);

    if (nxt.fi == -1 && nxt.se == -1)
        return;

    connect(head, x, y, nxt.fi, nxt.se);

    for (int i = 0; i < 4; i++)
        dfs_Build_Maze(head, nxt.fi, nxt.se);
}
void prim_Build_Maze(Adjacentlist (*head)[M], int x, int y)
{
    PII queue[N * N];
    int hh = 0, tt = -1;
    queue[++tt] = { x, y };
    map[x][y] = 1;
    while (hh <= tt) {
        //这里一个从集合中随机拿一个点出
        int idx = hh + rand() % (tt - hh + 1);
        auto pnow = queue[idx];
        swap(queue[idx], queue[hh++]);
        bool flag = 0;
        while (!flag) {
            for (int i = 0; i < 4; i++) {
                auto pnext = getRandomNear(head, pnow.fi, pnow.se);
                if (pnext.fi == -1 && pnext.se == -1) {
                    flag = 1;
                    break;
                }
                connect(head, pnow.fi, pnow.se, pnext.fi, pnext.se);
                queue[++tt] = pnext;
            }
        }
    }
    return;
}
void kruskal_Build_Maze(Adjacentlist (*head)[M], int x, int y)
{
    for (int i = 1; i < LEN_ROW * 2; i++)
        for (int j = 1; j < LEN_COL * 2; j++) {
            if (map[i][j])
                continue;
            PII queue[N * N];
            int hh = 0, tt = -1;
            queue[++tt] = { i, j };
            while (hh <= tt) {
                int idx = hh + rand() % (tt - hh + 1);
                auto pnow = queue[idx];
                swap(queue[idx], queue[hh++]);
                for (int i = 0; i < 4; i++) {
                    auto pnext = getRandomNear(head, pnow.fi, pnow.se);
                    if (pnext.fi == -1 && pnext.se == -1) {
                        break;
                    }
                    connect(head, pnow.fi, pnow.se, pnext.fi, pnext.se);
                    queue[++tt] = pnext;
                }
            }
        }
    return;
}
void recursiveSegment_Build_Maze(Adjacentlist (*head)[M], int x1, int y1, int x2, int y2)
{
    srand((unsigned int)time(NULL));
    if (x2 - x1 == 2 || y2 - y1 == 2) {
        if (x2 - x1 == 2 && y2 - y1 == 2)
            return;
        if (x2 - x1 == 2) {
            for (int i = y1 + 1; i <= y2 - 3; i += 2)
                connect(head, x1 + 1, i, x1 + 1, i + 2);
        } else {
            for (int i = x1 + 1; i <= x2 - 3; i += 2)
                connect(head, i, y1 + 1, i + 2, y1 + 1);
        }
        return;
    }
    int centerx = x1 + (rand() % (x2 - x1 - 2)) + 1;
    int centery = y1 + (rand() % (y2 - y1 - 2)) + 1;
    if (centerx % 2)
        centerx++;
    if (centery % 2)
        centery++;
    int lefty = y1 + rand() % (centery - y1 - 1) + 1;
    if (lefty % 2 == 0)
        lefty++;
    connect(head, centerx - 1, lefty, centerx + 1, lefty);

    int righty = centery + rand() % (y2 - centery - 1) + 1;
    if (righty % 2 == 0)
        righty++;
    connect(head, centerx - 1, righty, centerx + 1, righty);

    int upx = x1 + rand() % (centerx - x1 - 1) + 1;
    if (upx % 2 == 0)
        upx++;
    connect(head, upx, centery - 1, upx, centery + 1);

    recursiveSegment_Build_Maze(head, x1, y1, centerx, centery);
    recursiveSegment_Build_Maze(head, x1, centery, centerx, y2);
    recursiveSegment_Build_Maze(head, centerx, y1, x2, centery);
    recursiveSegment_Build_Maze(head, centerx, centery, x2, y2);
}
