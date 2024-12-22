#include "easyx_config.h"
#include "maze_solver.h"
#include "global_vars.h"

int main() {
    // ��ʼ���Թ�

    int ix, iy, ox, oy;     // �����������ı���
    int flag = 0;           // ��������Ƿ�ʹ��Ĭ�ϵ���ʼ��
    //int maze[20][20] = {                    //�����Թ�1
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
    //int maze[20][20] = {                        //�����Թ�2
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
    int maze[20][20] = {                         //�����Թ�3
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
    std::cout << "�Թ�Ϊ10*10�ľ���" << std::endl;
    std::cout << "ѡ0ΪĬ�������յ㣬������������趨�����յ�" << std::endl;
    std::printf("���������ѡ��");
    std::cin >> flag;

    if (flag != 0) {
        std::cout << "���������λ�ã�0<x<=10,0<y<=10��" << std::endl;
        std::cout << "(���x):";
        std::cin >> ix;
        std::cout << "(���y):";
        std::cin >> iy;
        startX = ix, startY = iy;
        std::cout << "�������յ�λ�ã�0<x<=10,0<y<=10��" << std::endl;
        std::cout << "(�յ�x):";
        std::cin >> ox;
        std::cout << "(�յ�y):";
        std::cin >> oy;
        endX = ox, endY = oy;
    }
    else {
        std::cout << "ѡ��Ĭ�϶Խ���Ϊ��ʼ��" << std::endl;
    }
    std::system("cls");
    std::printf("��������ǣ�[%d,%d]", startX, startY);
    std::printf("�յ������ǣ�[%d,%d]\n", endX, endY);

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
    bool solved = false; // ʹ��solved�����м�¼�Ƿ����ĵ�ǰ״̬
    std::vector<std::pair<int, int>> path;
    int temp = 0;
    double test[20] = {};//��ʼ������Ϊ0,����Ϊdouble���ͣ������¼ʱ��
    int p = 0;
    while (true) {
        if (temp == 0) {
            std::cout << "��ϲ�㣬�Թ���ʼ����ϣ�" << std::endl;
            std::cout << "\t\t\t\t��ӭ�����Թ�Ѱ·С��Ϸ" << std::endl;
            std::cout << "\t\t\t��������Ҫʹ�õ��㷨���������Թ�:" << std::endl;
            std::cout << "\t\t\t1. ������ȱ���(DFS)" << std::endl;
            std::cout << "\t\t\t2. ������ȱ��� (BFS)" << std::endl;
            std::cout << "\t\t\t3. A*�㷨������A* Algorithm��" << std::endl;
            std::cout << "\t\t\t4. ��ҽ��в����߳��Թ���ʹ���������ҵļ�ͷ�����ƶ�)" << std::endl;
            std::cout << "\t\t\t5.�����ͬ���ҵ���������ʱ�������" << std::endl;
            std::cout << "\t\t\t ���������ѡ��";
            temp = temp + 1;
        }
        else {
            std::cout << "�����Ҳ����루1,2,3,4,5����" ;
        }
        std::cin >> choice;

        auto start_time = std::chrono::high_resolution_clock::now(); // ��¼��ʼʱ��

        switch (choice) {
        case 1:
            solved = solver.solveDFS();//����solveDFS
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
                            //ʹ��һ����ʱ������ʱ
                            auto end_time = std::chrono::high_resolution_clock::now(); // ��¼����ʱ�� 
                            std::chrono::duration<double> elapsed = end_time - start_time; // �����ʱ
                            std::cout << "\t\t\t\t��ϲ��ɹ������յ㣡��ʱ��" << elapsed.count() << " ��" << std::endl;
                            break;
                        }
                    }
                }

                // �˳��������� ESC ���˳�
                if (_kbhit() && _getch() == 27) { // ESC �� ASCII ֵΪ 27
                    break;
                }
            }
            break;
        case 5:

            if (p == 0) {
                std::cout << "\t\t\t\tû�д洢��·�����ʱ��" << std::endl;
            }
            else {
                solver.bubbleSort(test, p);
                std::cout << "\t\t\t\t������·�����ʱ��: ";
                solver.printArray(test, p);
            }
            continue; // ����ѭ���������к�������
        default:
            std::cout << "\t\t\t\t��Ч��ѡ������������" << std::endl;
            continue;
        }

        if (choice != 4) {
            if (solved) {
                solver.visualizePath(path);
                solver.printPath(path);
                auto end_time = std::chrono::high_resolution_clock::now(); // ��¼����ʱ��
                std::chrono::duration<double> all_time = end_time - start_time; // �����ʱ,ʹ�ü�ʱ������ʱ��ͬ��ѯ�ٶȵĲ��
                test[p] = all_time.count();//ʹ��һ������洢����ʱ
                p = p + 1;
                std::cout << "\t\t\t\t��ϲ��ɹ������յ㣡��ʱ��" << all_time.count() << " ��" << std::endl;
            }
            else {
                std::cout << "\t\t\t\tû���ҵ�·��" << std::endl;
            }
        }

        // ���·���Ա��´�ʹ��
        //path.clear();
        //solver.clearPath();

        // ѯ���Ƿ����
        std::cout << "\t\t\t\t�Ƿ������(y/n): ";
        char cont;
        while (true) {
            std::cin >> cont;
            if (cont == 'n' || cont == 'N') {
                printf("��������Ϸ����");
                goto end_game; //ʹ��goto����������ѭ��
            }
            else if(cont =='y' || cont =='Y') {
                printf("��������/t");
                break;
            }
            else {
                printf("(��������ȷ��n(N)����y(Y))��");//���쳣���
            }
        }
    }
end_game: 
    Sleep(100000); // �ӳ�100s�ر�ͼ�ο�
    closegraph(); // �ر�ͼ�δ���
    return 0;
}