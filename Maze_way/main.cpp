#include "easyx_config.h"
#include "maze_solver.h"
#include "global_vars.h"

int main() {
    // 初始化迷宫

    int ix, iy, ox, oy;     // 定义玩家输入的变量
    int flag = 0;           // 用来检测是否使用默认的起始点
    //int maze[20][20] = {                    //测试迷宫1
    //    {0},
    //    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    //    {0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
    //    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    //    {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    //    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    //    {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    //    {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    //    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    //    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    //    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    //};
    //int maze[20][20] = {                        //测试迷宫2
    //{0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // };  
    int maze[20][20] = {                         //测试迷宫3
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
    std::cout << "迷宫为10*10的矩阵" << std::endl;
    std::cout << "选0为默认起点和终点，非零可以重新设定起点和终点" << std::endl;
    std::printf("请输入你的选择：");
    std::cin >> flag;

    if (flag != 0) {
        std::cout << "请输入起点位置（0<x<=10,0<y<=10）" << std::endl;
        std::cout << "(起点x):";
        std::cin >> ix;
        std::cout << "(起点y):";
        std::cin >> iy;
        startX = ix, startY = iy;
        std::cout << "请输入终点位置（0<x<=10,0<y<=10）" << std::endl;
        std::cout << "(终点x):";
        std::cin >> ox;
        std::cout << "(终点y):";
        std::cin >> oy;
        endX = ox, endY = oy;
    }
    else {
        std::cout << "选择默认对角线为起始点" << std::endl;
    }
    std::system("cls");
    std::printf("起点坐标是：[%d,%d]", startX, startY);
    std::printf("终点坐标是：[%d,%d]\n", endX, endY);

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
    bool solved = false; // 使用solved来进行记录是否解决的当前状态
    std::vector<std::pair<int, int>> path;
    int temp = 0;
    double test[20] = {};//初始化数组为0,定义为double类型，方便记录时间
    int p = 0;
    while (true) {
        if (temp == 0) {
            std::cout << "恭喜你，迷宫初始化完毕！" << std::endl;
            std::cout << "\t\t\t\t欢迎来到迷宫寻路小游戏" << std::endl;
            std::cout << "\t\t\t输入你想要使用的算法来解决这个迷宫:" << std::endl;
            std::cout << "\t\t\t1. 深度优先遍历(DFS)" << std::endl;
            std::cout << "\t\t\t2. 广度优先遍历 (BFS)" << std::endl;
            std::cout << "\t\t\t3. A*算法遍历（A* Algorithm）" << std::endl;
            std::cout << "\t\t\t4. 玩家进行操作走出迷宫（使用上下左右的箭头进行移动)" << std::endl;
            std::cout << "\t\t\t5.输出不同查找的排序所需时间的排序" << std::endl;
            std::cout << "\t\t\t 请输入你的选择：";
            temp = temp + 1;
        }
        else {
            std::cout << "请在右侧输入（1,2,3,4,5）：" ;
        }
        std::cin >> choice;

        auto start_time = std::chrono::high_resolution_clock::now(); // 记录开始时间

        switch (choice) {
        case 1:
            solved = solver.solveDFS();//调用solveDFS
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
                            //使用一个计时器来计时
                            auto end_time = std::chrono::high_resolution_clock::now(); // 记录结束时间 
                            std::chrono::duration<double> elapsed = end_time - start_time; // 计算耗时
                            std::cout << "\t\t\t\t恭喜你成功到达终点！用时：" << elapsed.count() << " 秒" << std::endl;
                            break;
                        }
                    }
                }

                // 退出条件：按 ESC 键退出
                if (_kbhit() && _getch() == 27) { // ESC 的 ASCII 值为 27
                    break;
                }
            }
            break;
        case 5:

            if (p == 0) {
                std::cout << "\t\t\t\t没有存储的路径求解时间" << std::endl;
            }
            else {
                solver.bubbleSort(test, p);
                std::cout << "\t\t\t\t排序后的路径求解时间: ";
                solver.printArray(test, p);
            }
            continue; // 继续循环，不进行后续操作
        default:
            std::cout << "\t\t\t\t无效的选择，请重新输入" << std::endl;
            continue;
        }

        if (choice != 4) {
            if (solved) {
                solver.visualizePath(path);
                solver.printPath(path);
                auto end_time = std::chrono::high_resolution_clock::now(); // 记录结束时间
                std::chrono::duration<double> all_time = end_time - start_time; // 计算耗时,使用计时器来计时不同查询速度的差别
                test[p] = all_time.count();//使用一个数组存储总用时
                p = p + 1;
                std::cout << "\t\t\t\t恭喜你成功到达终点！用时：" << all_time.count() << " 秒" << std::endl;
            }
            else {
                std::cout << "\t\t\t\t没有找到路径" << std::endl;
            }
        }

        // 清除路径以备下次使用
        //path.clear();
        //solver.clearPath();

        // 询问是否继续
        std::cout << "\t\t\t\t是否继续？(y/n): ";
        char cont;
        while (true) {
            std::cin >> cont;
            if (cont == 'n' || cont == 'N') {
                printf("哈哈哈游戏结束");
                goto end_game; //使用goto语句跳出外层循环
            }
            else if(cont =='y' || cont =='Y') {
                printf("又来玩啦/t");
                break;
            }
            else {
                printf("(请输入正确的n(N)或者y(Y))：");//做异常检测
            }
        }
    }
end_game: 
    Sleep(100000); // 延迟100s关闭图形库
    closegraph(); // 关闭图形窗口
    return 0;
}