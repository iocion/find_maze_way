#pragma once
#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include "easyx_config.h"
#include "global_vars.h"
//我使用一个MazeSolver类来进行抽象和封装所需要的函数部分以及所需要的内容

class MazeSolver {
public:
    MazeSolver(int** maze, int rows, int cols, int startX, int startY, int endX, int endY);
    //~MazeSolver();

    bool solveDFS();//DFS查找
    bool solveBFS();//BFS查找
    bool solveAStar();//A*算法查找
    void visualizePath(const std::vector<std::pair<int, int>>& path);//可视化路径

    void drawMaze();//绘制maze
    void drawPlayer(int x, int y);//绘制玩家
    void clearPlayer(int x, int y);//清除玩家位置
    void clearPath(); // 新增函数，删除路径
    void bubbleSort(double a[], int n);//使用冒泡排序函数
    void printArray(const double a[], int n);//输出排序后的

    void printPath(const std::vector<std::pair<int, int>>& path);
    std::vector<std::pair<int, int>> getPath() const { return path;}

private:
    int** maze;
    int rows, cols;
    int startX, startY, endX, endY;
    std::vector<std::pair<int, int>> path;

    bool isValid(int x, int y);
    bool isVisited(int x, int y, const std::vector<std::pair<int, int>>& visited);
    double heuristic(int x1, int y1, int x2, int y2);
};

#endif // MAZE_SOLVER_H