#include "global_vars.h"

const int cell_size = 40;   // ����Ϊ����ÿ�����ӵĴ�С
const int maxn = 20;        // ����Թ���С������������
int maze[20][20];           // �Թ�����0 ��ʾ��ͨ�У�1 ��ʾ�ϰ�
int n, m;                   // �Թ��ߴ磨������������
int startX, startY;         // ���
int endX, endY;             // �յ�
int X, Y;                   // ��ҵ�ǰ����