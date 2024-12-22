#include "maze_solver.h"

MazeSolver::MazeSolver(int** maze, int rows, int cols, int startX, int startY, int endX, int endY)//构造函数
    : maze(maze), rows(rows), cols(cols), startX(startX), startY(startY), endX(endX), endY(endY) {}



bool MazeSolver::isValid(int x, int y) {
    return (x >= 1 && x <= rows && y >= 1 && y <= cols && maze[x][y] == 0); //maze[x][y] == 0检验路径是否可行 是不是合法路径
}

bool MazeSolver::isVisited(int x, int y, const std::vector<std::pair<int, int>>& visited) { //检验是否是访问过的路径
    for (const auto& p : visited) {
        if (p.first == x && p.second == y) {
            return true;
        }
    }
    return false;
}
//使用A*算法
double MazeSolver::heuristic(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); //  使用欧拉距离来判断预估代价，还有需要计算的曼哈顿距离
}

//核心DFS算法求解路径，主要体现
bool MazeSolver::solveDFS() {
    std::stack<std::pair<int, int>> stack;//使用栈
    std::vector<std::pair<int, int>> visited;//表示访问过
    stack.push({ startX, startY });
    visited.push_back({ startX, startY });

    while (!stack.empty()) {
        auto &current = stack.top();
        stack.pop();
        int x = current.first;
        int y = current.second;

        if (x == endX && y == endY) {
            path.push_back({ x, y });
            return true;
        }

        path.push_back({ x, y });//当前节点加入路径并实现可视化
        visualizePath(path);//可视化实现

        Sleep(50); // 延时50ms

        static const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            //if (isVisited(newX, newY, visited)) {
            //    path.clear();
            //}
            //path.clear();//边走边清除
            if (isValid(newX, newY) && !isVisited(newX, newY, visited)) {
                stack.push({ newX, newY });
                visited.push_back({ newX, newY });
            }
        }
    }
    return false;
}
//核心BFS算法求解路径
bool MazeSolver::solveBFS() {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::pair<int, int>> visited;//用来记录是否是visited
    queue.push({ startX, startY });
    visited.push_back({ startX, startY });

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        int x = current.first;
        int y = current.second;

        if (x == endX && y == endY) {
            path.push_back({ x, y });
            return true;
        }

        path.push_back({ x, y });
        visualizePath(path);
        Sleep(50); // Delay for visualization

        static const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            //path.clear();//边走边清除
            if (isValid(newX, newY) && !isVisited(newX, newY, visited)) {
                queue.push({ newX, newY });
                visited.push_back({ newX, newY });
            }
        }
    }
    return false;
}

bool MazeSolver::solveAStar() {     //使用A*算法//openSet声明一个优先队列，存储待处理的节点，按照fScore进行排序
    std::priority_queue<std::pair<double, std::pair<int, int>>, std::vector<std::pair<double, std::pair<int, int>>>, std::greater<>> openSet;
    std::vector<std::vector<bool>> closedSet(rows + 1, std::vector<bool>(cols + 1, false));//标记已经处理的节点
    std::vector<std::vector<std::pair<int, int>>> cameFrom(rows + 1, std::vector<std::pair<int, int>>(cols + 1, { -1, -1 }));//cameFrom记录每一个节点从哪里来
    std::vector<std::vector<double>> gScore(rows + 1, std::vector<double>(cols + 1, INFINITY));//起点到当前节点的实际代价
    std::vector<std::vector<double>> fScore(rows + 1, std::vector<double>(cols + 1, INFINITY));//起点到当前节点的总估计代价

    openSet.push({ 0, {startX, startY} });
    gScore[startX][startY] = 0;
    fScore[startX][startY] = heuristic(startX, startY, endX, endY);//刚开始没有移动的时候，初始化

    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();
        int x = current.second.first;
        int y = current.second.second;//取出fScore里面最小代价的节点作为当前节点

        if (x == endX && y == endY) {
            int cx = x, cy = y;
            while (cx != -1 && cy != -1) {
                path.push_back({ cx, cy });
                auto &prev = cameFrom[cx][cy];
                cx = prev.first;
                cy = prev.second;
            }
            std::reverse(path.begin(), path.end());
            return true;
        }

        closedSet[x][y] = true;//标记已经找到的路径

        static const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (isValid(newX, newY) && !closedSet[newX][newY]) {
                double test_gScore = gScore[x][y] + 1;//每走一步实际代价就要加上一
                if (test_gScore < gScore[newX][newY]) {
                    cameFrom[newX][newY] = { x, y };
                    gScore[newX][newY] = test_gScore;
                    fScore[newX][newY] = test_gScore + heuristic(newX, newY, endX, endY);//代价是当前代价+预估代价
                    openSet.push({ fScore[newX][newY], {newX, newY} });
                }
            }
        }

        // 使用临时向量存储 openSet 的元素
        path.clear();
        std::vector<std::pair<double, std::pair<int, int>>> tempOpenSet(openSet.size());
        size_t index = 0;
        while (!openSet.empty()) {
            tempOpenSet[index++] = openSet.top();//暂存在临时向量
            openSet.pop();
        }
        for (const auto& item : tempOpenSet) {
            path.push_back(item.second);
        }
        // 重新将 tempOpenSet 中的元素放回 openSet
        for (const auto& item : tempOpenSet) {
            openSet.push(item);
        }

        visualizePath(path);
        Sleep(50); //延时50ms
    }
    return false;
}

void MazeSolver::visualizePath(const std::vector<std::pair<int, int>>& path) {
    // 绘制可通行路径为白色
    setfillcolor(WHITE);
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (maze[i][j] == 0) {
                int x1 = (j - 1) * cell_size;
                int y1 = (i - 1) * cell_size;
                int x2 = j * cell_size;
                int y2 = i * cell_size;
                solidrectangle(x1, y1, x2, y2);
            }
        }
    }
    // 绘制路径为黄色
    setfillcolor(YELLOW);
    for (const auto& p : path) {
        int x = p.first;
        int y = p.second;
        int x1 = (y - 1) * cell_size;
        int y1 = (x - 1) * cell_size;
        int x2 = y * cell_size;
        int y2 = x * cell_size;
        solidrectangle(x1, y1, x2, y2);
    }
    // 绘制玩家位置
    drawPlayer(X, Y);
}

void MazeSolver::drawMaze() {
     //绘制障碍物
    for (int i = 1; i <= rows; i++) { 
        for (int j = 1; j <= cols; j++) {
            if (maze[i][j] == 1) {
                setfillcolor(BLACK);
                int x1 = (j - 1) * cell_size;
                int y1 = (i - 1) * cell_size;
                int x2 = j * cell_size;
                int y2 = i * cell_size;
                solidrectangle(x1, y1, x2, y2);//设置矩形填充
            }
        }
    }
     //绘制起点和终点
     //绘制障碍物
    setfillcolor(GREEN);
    solidrectangle((startY - 1) * cell_size, (startX - 1) * cell_size, startY * cell_size, startX * cell_size);
    setfillcolor(RED);
    solidrectangle((endY - 1) * cell_size, (endX - 1) * cell_size, endY * cell_size, endX * cell_size);
}


void MazeSolver::drawPlayer(int x, int y) {     //绘制玩家位置
    setfillcolor(GREEN);
    int x1 = (y - 1) * cell_size;
    int y1 = (x - 1) * cell_size;
    int x2 = y * cell_size;
    int y2 = x * cell_size;
    solidrectangle(x1, y1, x2, y2);
}

void MazeSolver::clearPlayer(int x, int y) {    //清除玩家位置
    setfillcolor(WHITE);
    int x1 = (y - 1) * cell_size;
    int y1 = (x - 1) * cell_size;
    int x2 = y * cell_size;
    int y2 = x * cell_size;
    solidrectangle(x1, y1, x2, y2);
}

void MazeSolver::clearPath() {
    for (const auto& p : path) {
        setfillcolor(RGB(255, 255, 255)); // 设置填充颜色为白色
        fillrectangle(p.first * cell_size + 1, p.second * cell_size + 1, (p.first + 1) * cell_size - 1, (p.second + 1) * cell_size - 1);
    }
    path.clear();
}


void MazeSolver::printPath(const std::vector<std::pair<int, int>>& path) {  //输出行走的路径
    if (path.empty()) {
        std::cout << "没有找到对应的路" << std::endl;
        return;
    }
    std::cout << "你所测试的路径的总长度为:" << path.size() << std::endl;
    std::cout << "路径路线所示 ";
    for (const auto& p : path) {   //auto迭代器
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << std::endl;
}
// 冒泡排序函数
void MazeSolver::bubbleSort(double a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                // 交换 a[j] 和 a[j + 1]
                double temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// 打印数组函数
void MazeSolver::printArray(const double a[], int n) {
    printf("算法耗时排序为：");
    for (int i = 0; i < n; ++i) {
        printf("%.5f",a[i]) ;
        if (i < 2) {
            printf("<");
        }
    }
    std::cout << std::endl;
}
