#include "global_vars.h"

const int cell_size = 40;   // 设置为常量每个格子的大小
const int maxn = 20;        // 最大迷宫大小（格子数量）
int maze[20][20];           // 迷宫矩阵，0 表示可通行，1 表示障碍
int n, m;                   // 迷宫尺寸（行数和列数）
int startX, startY;         // 起点
int endX, endY;             // 终点
int X, Y;                   // 玩家当前坐标