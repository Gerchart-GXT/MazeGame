#include "MazeSolve.h"
Adjacentlist (*init())[M]
{
    auto head = new Adjacentlist[N * 2][N * 2]();
    memset(map, 0, sizeof map);
    return head;
}
void MazeCreate(Adjacentlist (*head)[M])
{
    puts("Please choose the algorithm of creating the Maze:");
    puts("1--Randomized depth-first search");
    puts("2--Randomized Prim's algorithm");
    puts("3--Randomized Kruskal's algorithm");
    puts("4--Recursive division method");
    int op = 0;
    while (std::cin >> op) {
        int x = rand() % LEN_ROW + 1;
        int y = rand() % LEN_COL + 1;
        if (op == 1) {
            dfs_Build_Maze(head, x * 2 - 1, y * 2 - 1);
            puts("Create with Randomized depth-first search!");
        }
        if (op == 2) {
            prim_Build_Maze(head, x * 2 - 1, y * 2 - 1);
            puts("Create with Randomized Prim's algorithm");
        }
        if (op == 3) {
            kruskal_Build_Maze(head, x * 2 - 1, y * 2 - 1);
            puts("Create with Randomized Kruskal's algorithm");
        }
        if (op == 4) {
            recursiveSegment_Build_Maze(head, 0, 0, LEN_ROW * 2, LEN_COL * 2);
            puts("Create with Recursive division method");
        }
        break;
    }
    puts("Finish!!");
    puts("Map of Maze is as follow:");
    puts("");
    printMap(head);
    puts("");
}
void MazeSolve(int sx, int sy, int ex, int ey)
{
    puts("Please choose the algorithm of solving the Maze:");
    puts("1--DFS (with Stack) ");
    puts("2--BFS (with Queue) ");
    puts("Ps: if the Maze is large , choose BFS is better!");
    int op = 0;
    while (std::cin >> op) {
        if (op == 1) {
            Dfs_Solve_Maze(sx, sy, ex, ey);
            printPath();
        }
        if (op == 2) {
            Bfs_Solve_Maze(sx, sy, ex, ey);
            printPath();
        }
        break;
    }
}
int main()
{
    puts("----------");
    puts("Welcome to Gerchart's Maze Game!!!!!!");
    puts("----------");
    puts("");
    puts("--Ps1 : Inputs two num in range [2,800] (to insure can not out of stack)");
    // 800只是在默认下stack是1M下比较安全
    //理论上1s之内5000*5000的迷宫是可以生成的，但是要重新在编译的时候调一下stack的大小
    puts("--Ps2 : We have 4 methods to create a perfect Maze");
    puts("");
    puts("After reading the above tips, please press any key to start input!");
    getchar();

    puts("Please input the size of Maze you want to generate:");
    puts("length of Row:");
    LEN_COL = LEN_ROW = 0;
    std::cin >> LEN_ROW;
    puts("length of Col:");
    std::cin >> LEN_COL;

    auto head = init();
    MazeCreate(head);

    puts("Please input the start position:(x y)");
    int sx = 0, sy = 0;
    std::cin >> sx >> sy;
    puts("Please input the target position:(x y)");
    int ex = 0, ey = 0;
    std::cin >> ex >> ey;

    MazeSolve(sx * 2 - 1, sy * 2 - 1, ex * 2 - 1, ey * 2 - 1);

    delete[] head;
    puts("Finish!! Press any key to exit!");
    getchar();
    getchar();
    return 0;
}