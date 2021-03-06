# 数据结构作业之——迷宫
## 题干
* 走迷宫：自定义一个迷宫，行、列值>8，它有一个出口和一个入口，先输出迷宫图形，然后找出一条从入口到出口的路径（上下左右四个方向）。分别用栈和队列求解问题
## 文件结构
1.  `Adjacentlist.h`
    * 邻接表类
    * 成员：指针域、`x,y`坐标
2.  `radam&connect.h`
    * 随机周围一个不在集合的点
    * 将相邻的点进行连接
3. `MazeBuild.h`
    * 四种迷宫生成算法
    ```cpp
    //根据邻接表来打印Map
    void printMap(Adjacentlist (*head)[M]);
    //基于DFS的迷宫生成算法——每一个点随机一个方向进行扩展，将对于的点联通
    void dfs_Build_Maze(Adjacentlist (*head)[M], int x, int y);
    //基于Prim的迷宫生成算法
    void prim_Build_Maze(Adjacentlist (*head)[M], int x, int y);
    //基于Kruskal的迷宫生成算法
    void kruskal_Build_Maze(Adjacentlist (*head)[M], int x, int y);
    //基于递归分割的迷宫生成算法
    void recursiveSegment_Build_Maze(Adjacentlist (*head)[M], int x1, int y1, int x2, int y2);
    ```
4. `MazeSolve.h`
    * 两种迷宫求解方法
    ```cpp
    //用栈来深搜，对于每个点定义一个联通方向向量——（0，1，2，3对应dtx，dty），当该点不能被拓展时证明该路径为死路，依次出栈，最后的栈内元素就是路径
    void Dfs_Solve_Maze(int sx, int sy, int ex, int ey）;
    //队列宽搜，要另开一个path来记录每一点的前驱节点，最后回溯输出即可
    void Bfs_Solve_Maze(int sx, int sy, int ex, int ey）;
    ```
## 细节解释
1. 为什么使用邻接表存图
    * 对于DFS和递归分割的迷宫生成算法，优势不明显，甚至相较与数组直接处理，稍显复杂——也可以使用邻接矩阵存储
    * 对于Prim和Kruskal，用邻接表可以更好的完成最小生成树的生成——图的邻接表存储
2. 为什么可以用Prim和Kruskal
    * 初始情况下，可以将每一个可走的点看作是孤立的元点，每个点可以向其四周（上下左右）的元点连一条有向边，边权为0
    * 对于Prim
        * 每次随机选择一个在队列中的点，将其进行扩展（随机选择一个未在集合中的相邻边），并将其加入队列，以此类推直到队列为空，此时所有的可达点都被联通，且图内不存在环
    * 对于Kruskal
        * 遍历所有的点，初始下树的集合为空，对于不在集合的点，对其进行一次扩展，将其连接到集合中
            * 这里对这个扩展进行一些改动，加入了一个类似于Prim的队列，对队列中元素进行扩展
            * Ps：这里如果仅选择周围已在集合点中的点，进行联通，生成的迷宫会有一条非常明显的主路，迷宫复杂度降低
3. 递归分割的原理
    * 基于分治思想，初始下的迷宫没有墙，所有点都是联通的
        * 在图中选择一个应该是墙的点，将其作为一对“十字墙”的中心点，画一个十字
        * 此时迷宫被分为四个不联通的区域，在刚才的十字墙的被中心点分成的四部分中，选择三面墙，将其打通（随机一个在墙上的点），这样刚才被分成的四个区域就联通了
        * 递归处理四个区域，当当前的区域不能画十字墙时，就把该区域的所有墙都打通（此时的区域类似于日字型）

