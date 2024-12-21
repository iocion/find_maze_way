#include "easyx_config.h"
#include "maze_solver.h"
#include "global_vars.h"

//#include <iostream>
//#include <vector>
//#include <cstdlib> // for rand() and srand()
//#include <ctime>   // for time()

//using namespace std;
//
//// Function to generate a random maze
//void generateMaze(int n, vector<vector<int>>& maze, int startX, int startY, int endX, int endY) {
//    // Seed the random number generator
//    srand(static_cast<unsigned int>(time(0)));
//
//    // Generate random values for the maze
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            // Randomly set 0 or 1 in the maze, except for the start and end positions
//            if ((i == startX && j == startY) || (i == endX && j == endY)) {
//                maze[i][j] = 0; // Ensure start and end are passable
//            } else {
//                maze[i][j] = rand() % 2; // Randomly choose between 0 and 1
//            }
//        }
//    }
//
//    // Optionally, you can add logic here to ensure the maze is solvable.
//    // This might involve using a pathfinding algorithm to check connectivity.
//}
//

int main() {
    // 初始化迷宫
    int maze[20][20] = {
        {0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    };
    n = 10, m = 10;         // 迷宫尺寸（行数和列数）
    startX = 1, startY = 1; // 起点
    endX = 10, endY = 10;   // 终点

    // 将二维数组转换为指针数组
    int* mazePtr[20]{};
    for (int i = 0; i <= n; i++) {
        mazePtr[i] = maze[i];
    }

    // 初始化窗口
    initgraph(m * cell_size, n * cell_size);
    setbkcolor(WHITE);
    cleardevice();

    MazeSolver solver(mazePtr, n, m, startX, startY, endX, endY);
    solver.drawMaze();
    int choice;
    /*while (true) {*/
        std::cout << "\t\t\t\t欢迎来到迷宫寻路小游戏" << std::endl;
        std::cout << "\t\t\t输入你想要使用的算法来解决这个迷宫:" << std::endl;
        std::cout << "\t\t\t1. 深度优先遍历(DFS)" << std::endl;
        std::cout << "\t\t\t2. 广度优先遍历 (BFS)" << std::endl;
        std::cout << "\t\t\t3. A*算法遍历（A* Algorithm）" << std::endl;
        std::cout << "\t\t\t4.玩家进行操作走出迷宫（使用上下左右的箭头进行移动)" << std::endl;
        std::cout << "\t\t\t请输入你的选择：";
        std::cin >> choice;
        bool solved = false;//使用solved来进行记录是否解决的当前状态
        std::vector<std::pair<int, int>> path;

        switch (choice) {
        case 1:
            solved = solver.solveDFS();
            path = solver.getPath();
            break;
        case 2:
            solved = solver.solveBFS();
            path = solver.getPath();
            break;
        case 3:
            solved = solver.solveAStar();
            path = solver.getPath();
            break;
        case 4:
            X = startX, Y = startY;
            while (true) {
                if (_kbhit()) { // 检测键盘按键
                    char key = _getch();

                    // 如果检测到特殊键（箭头键），需捕获两次键值
                    if (key == 0 || key == -32) {
                        key = _getch(); // 捕获箭头键的实际值

                        // 记录旧位置
                        int oldX = X;
                        int oldY = Y;

                        // 根据箭头键值更新玩家坐标
                        if (key == 72 && X > 1 && maze[X - 1][Y] == 0) { // 上箭头
                            X--;
                        }
                        else if (key == 80 && X < n && maze[X + 1][Y] == 0) { // 下箭头
                            X++;
                        }
                        else if (key == 75 && Y > 1 && maze[X][Y - 1] == 0) { // 左箭头
                            Y--;
                        }
                        else if (key == 77 && Y < m && maze[X][Y + 1] == 0) { // 右箭头
                            Y++;
                        }

                        // 擦除旧位置
                        solver.clearPlayer(oldX, oldY);
                        // 重绘新位置
                        solver.drawPlayer(X, Y);

                        // 判断是否到达终点
                        if (X == endX && Y == endY) {
                            std::cout << "\t\t\t\t恭喜你成功到达终点" << std::endl;
                            break;
                        }
                    }
                }

                // 退出条件：按 ESC 键退出
                if (_kbhit() && _getch() == 27) { // ESC 的 ASCII 值为 27
                    break;
                }
            }
        default:
            std::cout << "\t\t\t\t游戏结束" << std::endl;
            break;
        }
    //}
    if (choice != 4) {
        if (solved) {
            solver.visualizePath(path);
            solver.printPath(path);
        }
        else {
            std::cout << "\t\t\t\t没有找到的路径" << std::endl;
        }
    }
    Sleep(100000); //延迟100s关闭图形库
    closegraph(); // 关闭图形窗口
    return 0;
}