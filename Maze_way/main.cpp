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
    // ��ʼ���Թ�
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
    n = 10, m = 10;         // �Թ��ߴ磨������������
    startX = 1, startY = 1; // ���
    endX = 10, endY = 10;   // �յ�

    // ����ά����ת��Ϊָ������
    int* mazePtr[20]{};
    for (int i = 0; i <= n; i++) {
        mazePtr[i] = maze[i];
    }

    // ��ʼ������
    initgraph(m * cell_size, n * cell_size);
    setbkcolor(WHITE);
    cleardevice();

    MazeSolver solver(mazePtr, n, m, startX, startY, endX, endY);
    solver.drawMaze();
    int choice;
    /*while (true) {*/
        std::cout << "\t\t\t\t��ӭ�����Թ�Ѱ·С��Ϸ" << std::endl;
        std::cout << "\t\t\t��������Ҫʹ�õ��㷨���������Թ�:" << std::endl;
        std::cout << "\t\t\t1. ������ȱ���(DFS)" << std::endl;
        std::cout << "\t\t\t2. ������ȱ��� (BFS)" << std::endl;
        std::cout << "\t\t\t3. A*�㷨������A* Algorithm��" << std::endl;
        std::cout << "\t\t\t4.��ҽ��в����߳��Թ���ʹ���������ҵļ�ͷ�����ƶ�)" << std::endl;
        std::cout << "\t\t\t���������ѡ��";
        std::cin >> choice;
        bool solved = false;//ʹ��solved�����м�¼�Ƿ����ĵ�ǰ״̬
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
                if (_kbhit()) { // �����̰���
                    char key = _getch();

                    // �����⵽���������ͷ�������貶�����μ�ֵ
                    if (key == 0 || key == -32) {
                        key = _getch(); // �����ͷ����ʵ��ֵ

                        // ��¼��λ��
                        int oldX = X;
                        int oldY = Y;

                        // ���ݼ�ͷ��ֵ�����������
                        if (key == 72 && X > 1 && maze[X - 1][Y] == 0) { // �ϼ�ͷ
                            X--;
                        }
                        else if (key == 80 && X < n && maze[X + 1][Y] == 0) { // �¼�ͷ
                            X++;
                        }
                        else if (key == 75 && Y > 1 && maze[X][Y - 1] == 0) { // ���ͷ
                            Y--;
                        }
                        else if (key == 77 && Y < m && maze[X][Y + 1] == 0) { // �Ҽ�ͷ
                            Y++;
                        }

                        // ������λ��
                        solver.clearPlayer(oldX, oldY);
                        // �ػ���λ��
                        solver.drawPlayer(X, Y);

                        // �ж��Ƿ񵽴��յ�
                        if (X == endX && Y == endY) {
                            std::cout << "\t\t\t\t��ϲ��ɹ������յ�" << std::endl;
                            break;
                        }
                    }
                }

                // �˳��������� ESC ���˳�
                if (_kbhit() && _getch() == 27) { // ESC �� ASCII ֵΪ 27
                    break;
                }
            }
        default:
            std::cout << "\t\t\t\t��Ϸ����" << std::endl;
            break;
        }
    //}
    if (choice != 4) {
        if (solved) {
            solver.visualizePath(path);
            solver.printPath(path);
        }
        else {
            std::cout << "\t\t\t\tû���ҵ���·��" << std::endl;
        }
    }
    Sleep(100000); //�ӳ�100s�ر�ͼ�ο�
    closegraph(); // �ر�ͼ�δ���
    return 0;
}