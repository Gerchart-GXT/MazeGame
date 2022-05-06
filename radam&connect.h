#include "Adjacentlist.h"
#include <algorithm>
#include <iostream>
#define fi first
#define se second
typedef std::pair<int, int> PII;

const int N = 1e3 + 10, M = N * 2;
const int dx[] = { -2, 0, 2, 0 }, dy[] = { 0, 2, 0, -2 };

bool map[M][M];

int LEN_ROW = 0, LEN_COL = 0;

bool connect(Adjacentlist (*head)[M], int x1, int y1, int x2, int y2)
{
    map[x2][y2] = true;
    auto plb = new Adjacentlist(head[x1][y1].getNext(), x2, y2);
    head[x1][y1].changeNext(plb);
    return true;
}
PII getRandomNear(Adjacentlist (*head)[M], int x, int y)
{
    int dir = rand();
    //不用time(0)随机是因为time（0）返回的单位是s，由于运行的太快了，这个dir不会变化
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[(dir + i) % 4], ty = y + dy[(dir + i) % 4];
        if (tx < 1 || tx > LEN_ROW * 2 || ty < 1 || ty > LEN_COL * 2)
            continue;
        if (!map[tx][ty])
            return { tx, ty };
    }
    return { -1, -1 };
}
