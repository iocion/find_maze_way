#pragma once
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

extern const int cell_size;   // 设置为常量每个格子的大小
extern const int MAXN;        // 最大迷宫大小（格子数量）
extern int maze[20][20];       // 迷宫矩阵，0 表示可通行，1 表示障碍
extern int n, m;               // 迷宫尺寸（行数和列数）
extern int startX, startY;     // 起点
extern int endX, endY;         // 终点
extern int X, Y;               // 玩家当前坐标

#endif // GLOBAL_VARS_H