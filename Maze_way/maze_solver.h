#pragma once
#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include "easyx_config.h"
#include "global_vars.h"
//��ʹ��һ��MazeSolver�������г���ͷ�װ����Ҫ�ĺ��������Լ�����Ҫ������

class MazeSolver {
public:
    MazeSolver(int** maze, int rows, int cols, int startX, int startY, int endX, int endY);
    //~MazeSolver();

    bool solveDFS();//DFS����
    bool solveBFS();//BFS����
    bool solveAStar();//A*�㷨����
    void visualizePath(const std::vector<std::pair<int, int>>& path);//���ӻ�·��

    void drawMaze();//����maze
    void drawPlayer(int x, int y);//�������
    void clearPlayer(int x, int y);//������λ��
    void clearPath(); // ����������ɾ��·��
    void bubbleSort(double a[], int n);//ʹ��ð��������
    void printArray(const double a[], int n);//���������

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