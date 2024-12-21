#include "maze_solver.h"

MazeSolver::MazeSolver(int** maze, int rows, int cols, int startX, int startY, int endX, int endY)//���캯��
    : maze(maze), rows(rows), cols(cols), startX(startX), startY(startY), endX(endX), endY(endY) {}

//MazeSolver::~MazeSolver() {
//   // Clean up if necessary
//}  //��������

bool MazeSolver::isValid(int x, int y) {
    return (x >= 1 && x <= rows && y >= 1 && y <= cols && maze[x][y] == 0); //maze[x][y] == 0����·���Ƿ����
}

bool MazeSolver::isVisited(int x, int y, const std::vector<std::pair<int, int>>& visited) {
    for (const auto& p : visited) {
        if (p.first == x && p.second == y) {
            return true;
        }
    }
    return false;
}
//ʹ��A*�㷨
double MazeSolver::heuristic(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); //ʹ��math����������pow�������м���λ����Ϣ
}

//����DFS�㷨���·��
bool MazeSolver::solveDFS() {
    std::stack<std::pair<int, int>> stack;
    std::vector<std::pair<int, int>> visited;
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

        path.push_back({ x, y });
        visualizePath(path);
        Sleep(50); // Delay for visualization

        static const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (isValid(newX, newY) && !isVisited(newX, newY, visited)) {
                stack.push({ newX, newY });
                visited.push_back({ newX, newY });
            }
        }
    }
    return false;
}
//����BFS�㷨���·��
bool MazeSolver::solveBFS() {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<std::pair<int, int>>> paths;
    std::vector<std::pair<int, int>> visited_bfs;//���һ���Ƿ������visited:2024/12/18,������Ҫ������Ƿ����ʹ��visited_bfs->
    queue.push({ startX, startY });
    paths.push_back({ {startX, startY} });

    while (!queue.empty()) {
        auto &current = queue.front();
        queue.pop();
        auto &currentPath = paths.front();
        paths.erase(paths.begin());
        int x = current.first;
        int y = current.second;
        
        if (x == endX && y == endY) {
            path = currentPath;
            return true;    //����Ŀ�ĵغ�x,y��Ⱦͳɹ�����true
        }

        path = currentPath;
        visualizePath(path);
        Sleep(50); //�ӳ�һ��ʱ��
        
        static const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            //if (isValid(newX, newY) && !isVisited(newX, newY))
            if (isValid(newX, newY)) {
                std::vector<std::pair<int, int>> newPath = currentPath;
                newPath.push_back({ newX, newY });
                queue.push({ newX, newY });
                paths.push_back(newPath);
            }
        }
    }
    return false;
}


bool MazeSolver::solveAStar() {
    std::priority_queue<std::pair<double, std::pair<int, int>>, std::vector<std::pair<double, std::pair<int, int>>>, std::greater<>> openSet;
    std::vector<std::vector<bool>> closedSet(rows + 1, std::vector<bool>(cols + 1, false));
    std::vector<std::vector<std::pair<int, int>>> cameFrom(rows + 1, std::vector<std::pair<int, int>>(cols + 1, { -1, -1 }));
    std::vector<std::vector<double>> gScore(rows + 1, std::vector<double>(cols + 1, INFINITY));
    std::vector<std::vector<double>> fScore(rows + 1, std::vector<double>(cols + 1, INFINITY));

    openSet.push({ 0, {startX, startY} });
    gScore[startX][startY] = 0;
    fScore[startX][startY] = heuristic(startX, startY, endX, endY);

    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();
        int x = current.second.first;
        int y = current.second.second;

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

        closedSet[x][y] = true;

        static const std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (isValid(newX, newY) && !closedSet[newX][newY]) {
                double tentativeGScore = gScore[x][y] + 1;
                if (tentativeGScore < gScore[newX][newY]) {
                    cameFrom[newX][newY] = { x, y };
                    gScore[newX][newY] = tentativeGScore;
                    fScore[newX][newY] = tentativeGScore + heuristic(newX, newY, endX, endY);
                    openSet.push({ fScore[newX][newY], {newX, newY} });
                }
            }
        }

        // ʹ����ʱ�����洢 openSet ��Ԫ��
        path.clear();
        std::vector<std::pair<double, std::pair<int, int>>> tempOpenSet(openSet.size());
        size_t index = 0;
        while (!openSet.empty()) {
            tempOpenSet[index++] = openSet.top();
            openSet.pop();
        }
        for (const auto& item : tempOpenSet) {
            path.push_back(item.second);
        }
        // ���½� tempOpenSet �е�Ԫ�طŻ� openSet
        for (const auto& item : tempOpenSet) {
            openSet.push(item);
        }

        visualizePath(path);
        Sleep(50); // Delay for visualization
    }
    return false;
}

void MazeSolver::visualizePath(const std::vector<std::pair<int, int>>& path) {
    // ���ƿ�ͨ��·��Ϊ��ɫ
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
    // ����·��Ϊ��ɫ
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
    // �������λ��
    drawPlayer(X, Y);
}

void MazeSolver::drawMaze() {
     //�����ϰ���
    for (int i = 1; i <= rows; i++) { 
        for (int j = 1; j <= cols; j++) {
            if (maze[i][j] == 1) {
                setfillcolor(BLACK);
                int x1 = (j - 1) * cell_size;
                int y1 = (i - 1) * cell_size;
                int x2 = j * cell_size;
                int y2 = i * cell_size;
                solidrectangle(x1, y1, x2, y2);//���þ������
            }
        }
    }
     //���������յ�
     //�����ϰ���
    setfillcolor(GREEN);
    solidrectangle((startY - 1) * cell_size, (startX - 1) * cell_size, startY * cell_size, startX * cell_size);
    setfillcolor(RED);
    solidrectangle((endY - 1) * cell_size, (endX - 1) * cell_size, endY * cell_size, endX * cell_size);
}

void MazeSolver::drawPlayer(int x, int y) {
    setfillcolor(GREEN);
    int x1 = (y - 1) * cell_size;
    int y1 = (x - 1) * cell_size;
    int x2 = y * cell_size;
    int y2 = x * cell_size;
    solidrectangle(x1, y1, x2, y2);
}

void MazeSolver::clearPlayer(int x, int y) {
    setfillcolor(WHITE);
    int x1 = (y - 1) * cell_size;
    int y1 = (x - 1) * cell_size;
    int x2 = y * cell_size;
    int y2 = x * cell_size;
    solidrectangle(x1, y1, x2, y2);
}

void MazeSolver::printPath(const std::vector<std::pair<int, int>>& path) {
    if (path.empty()) {
        std::cout << "û���ҵ���Ӧ��·" << std::endl;
        return;
    }
    std::cout << "·���ĳ���Ϊ" << path.size() << std::endl;
    std::cout << "·��·����ʾ ";
    for (const auto& p : path) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << std::endl;
}