#pragma once
#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "easyx_config.h"
#include "global_vars.h"

class MazeSolver {
public:
    MazeSolver(int** maze, int rows, int cols, int startX, int startY, int endX, int endY);
    //~MazeSolver();

    bool solveDFS();
    bool solveBFS();
    bool solveAStar();
    void visualizePath(const std::vector<std::pair<int, int>>& path);

    void drawMaze();
    void drawPlayer(int x, int y);
    void clearPlayer(int x, int y);

    void printPath(const std::vector<std::pair<int, int>>& path);
    std::vector<std::pair<int, int>> getPath() const { return path; }

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