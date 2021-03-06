// eightNumber.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define LIST_MAX 10000  //breadth first open and closed array number
#define OPEN_MAX 2000
#define CLOSED_MAX 8000
#define SLN_MAX 20  //solution array number
#define DEPTH_LIMIT 15

using namespace std;

typedef enum {
    LEFT = 1,
    UP,
    RIGHT,
    DOWN
} Dir_t;

clock_t start, stop;

void input(int original_node[9], int target_node[9]);
void generateOriginalNode(int original_node[9], const int target_node[9], const int step);
bool check(const int node1[9], const int node2[9]);
bool breadthFirstSearch(const int original_node[9], const int target_node[9]);
bool depthFirstSearch(const int original_node[9], const int target_node[9]);

int main()
{
    int original_node[9] = { 2,8,3,1,6,4,7,0,5 };
    int target_node[9] = { 1,2,3,8,0,4,7,6,5 };
    int step = 1;
    int algorithm = 0;
    int input_way = 0;

    printf("\n please choose algorithm ( 1 --- BFS; 2 --- DFS ) : ");
    cin >> algorithm;
    if (algorithm < 1 || algorithm > 2)
    {
        printf("input error! \n\n");
        return 1;
    }

    printf("\n please choose input way \n 1 --- automatic generation;\n 2 --- user input;\n other --- default: ");
    cin >> input_way;
    if (input_way == 1)
    {
        printf("\n please input step number (1~15) : ");
        cin >> step;
        if (step > 0 && step < 16)
            generateOriginalNode(original_node, target_node, step);
        else
        {
            printf("input error! \n\n");
            return 1;
        }
    }
    else if (input_way == 2)
        input(original_node, target_node);
    
    if (check(original_node, target_node))
    {
        if (algorithm == 1 && breadthFirstSearch(original_node, target_node))
            printf("\n find solution! \n");
        else if (algorithm == 2 && depthFirstSearch(original_node, target_node))
            printf("\n find solution! \n");
        else
            printf("\n not find! \n");

        printf("run time: %d ms \n", stop - start);
    }
    else
    {
        printf("input error! \n\n");
    }

    return 0;
}

void input(int original_node[9], int target_node[9])
{
    int i;
    printf("please input original_node:\n");
    for (i = 0; i<9; i++)
    {
        cin >> original_node[i];
    }
    printf("please input target_node:\n");
    for (i = 0; i<9; i++)
    {
        cin >> target_node[i];
    }
}

bool isSame(const int node1[9], const int node2[9])
{
    for (int i = 0; i < 9; ++i)
    {
        if (node1[i] != node2[i])
        {
            return false;
        }
    }
    return true;
}

void swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void sort(int *a)
{
    int i, j;
    for (i = 1; i < 9; i++)
    {
        for (j = 0; j < 9 - 1; j++)
        {
            if (a[j]>a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

bool check(const int node1[9], const int node2[9])
{
    int node[9] = { 0,1,2,3,4,5,6,7,8 };
    int node11[9], node22[9];

    memcpy(node11, node1, 9 * sizeof(int));
    memcpy(node22, node2, 9 * sizeof(int));
    sort(node11);
    sort(node22);

    if (isSame(node11, node) && isSame(node22, node))
    {
        return true;
    }
    return false;
}

int findIndex0(const int node[9])
{
    for (int i = 0; i < 9; ++i)
    {
        if (node[i] == 0)
        {
            return i;
        }
    }
    return 0;
}

void generateOriginalNode(int original_node[9], const int target_node[9], const int step)
{
    int r = 1;
    int last_step = 0;
    int index = 0;
    memcpy(original_node, target_node, 9 * sizeof(int));
    srand((int)time(0));
    
    for (int i = 0; i < step; i++)
    {
        index = findIndex0(original_node);
        int flag_node[4] = { 1,1,1,1 };
        if (index == 0 || index == 1 || index == 2)
            flag_node[UP - 1] = 0;
        if (index == 0 || index == 3 || index == 6)
            flag_node[LEFT - 1] = 0;
        if (index == 6 || index == 7 || index == 8)
            flag_node[DOWN - 1] = 0;
        if (index == 2 || index == 5 || index == 8)
            flag_node[RIGHT - 1] = 0;
        if (last_step == 1 || last_step == 2)
            flag_node[last_step + 1] = 0;
        else if (last_step == 3 || last_step == 4)
            flag_node[last_step - 3] = 0;
 
        do
        {
            r = rand() % 4;
        } while (flag_node[r] == 0);
        

        switch (r + 1)
        {
        case UP:swap(&original_node[index], &original_node[index - 3]); break;
        case LEFT:swap(&original_node[index], &original_node[index - 1]); break;
        case DOWN:swap(&original_node[index], &original_node[index + 3]); break;
        case RIGHT:swap(&original_node[index], &original_node[index + 1]); break;
        }

        last_step = r + 1;
    }
}

bool compareBF(const int list[LIST_MAX][11], const int nextNode[11], const int Pclose)
{
    for (int i = 0; i < Pclose; ++i)
    {
        if (isSame(&list[i][2], &nextNode[2]))
        {
            return false;
        }
    }
    return true;
}

void createNodeBF(int list[LIST_MAX][11], int type, int index, int Pclose, int *Popen)
{
    int nextNode[11];
    memcpy(nextNode, list[Pclose], 11* sizeof(int));

    nextNode[0] = Pclose + 1;
    nextNode[1] = type;

    switch (type)
    {
    case UP:swap(&nextNode[index], &nextNode[index - 3]); break;
    case LEFT:swap(&nextNode[index], &nextNode[index - 1]); break;
    case DOWN:swap(&nextNode[index], &nextNode[index + 3]); break;
    case RIGHT:swap(&nextNode[index], &nextNode[index + 1]); break;
    }

    if (compareBF(list, nextNode, Pclose))
    {
        memcpy(list[*Popen], nextNode, 11* sizeof(int));
        (*Popen)++;
        if (*Popen == LIST_MAX-1)
        {
            printf("list array out! \n");
        }
    }
}

void findNextNodeBF(int list[LIST_MAX][11], int Pclose, int *Popen)
{
    int index, i;
    int flag_node[4] = { 1,1,1,1 };

    index = findIndex0(&list[Pclose][2]);

    if (index == 0 || index == 1 || index == 2)
        flag_node[UP - 1] = 0;
    if (index == 0 || index == 3 || index == 6)
        flag_node[LEFT - 1] = 0;
    if (index == 6 || index == 7 || index == 8)
        flag_node[DOWN - 1] = 0;
    if (index == 2 || index == 5 || index == 8)
        flag_node[RIGHT - 1] = 0;
    if(list[Pclose][1] == 1 || list[Pclose][1] == 2)
        flag_node[list[Pclose][1] + 1] = 0;
    else if (list[Pclose][1] == 3 || list[Pclose][1] == 4)
        flag_node[list[Pclose][1] - 3] = 0;
    for (i = 0; i < 4; i++)
    {
        if (flag_node[i])
        {
            createNodeBF(list, i + 1, index + 2, Pclose, Popen);
        }
    }
}

void showListBF(const int list[LIST_MAX][11], const int Pclose)
{
    printf("\n    --------- CLOSED ---------\n\n");
    for (int i = 0; i < LIST_MAX; ++i)
    {
        if (list[i][0] == 0 && list[i][1] == 0 && i>1)
            return;
        if (i == Pclose)
            printf("\n    ---------- OPEN ----------\n\n");
        printf("%5d", i + 1);
        for (int j = 0; j < 11; ++j)
        {
            printf("%5d", list[i][j]);
        }
        printf("\n");
    }
}

void showSolutionBF(const int list[LIST_MAX][11], int num)
{
    int sln[SLN_MAX][11] = { 0 };
    char option[5] = { ' ', 'L', 'U', 'R', 'D' };
    int i, j;
    for (i = 0; i < SLN_MAX; ++i)
    {
        memcpy(sln[i], list[num], 11* sizeof(int));
        if (num == 0)
            break;
        num = sln[i][0] - 1;
        if (i == SLN_MAX -1)
        {
            printf("sln array out! \n");
        }
    }
    printf("\n    --------- process ---------\n\n");
    for (; i >= 0; i--)
    {
        for (j = 2; j < 11; ++j)
        {
            printf("%3d", sln[i][j]);
            if (j == 4 || j == 7 || j == 10)
                printf("\n");
        }
        if (i > 0)
        {
            printf("%c\n", option[sln[i - 1][1]]);
        }
    }
}

bool breadthFirstSearch(const int original_node[9], const int target_node[9])
{
    start = clock();
    int list[LIST_MAX][11] = { 0 };
    int Pclose = 0, Popen = 1;
    int t;

    if (isSame(original_node, target_node))
    {
        printf("the original node is equal to target node.\n");
        return true;
    }

    memcpy(&list[0][2], original_node, 9* sizeof(int));

    while (true)
    {
        if (Pclose == Popen)
        {
            return false;
        }

        t = Popen;

        findNextNodeBF(list, Pclose, &Popen);

        Pclose++;

        for (int i = 0; i < Popen - t; ++i)
        {
            if (isSame(&list[t + i][2], target_node))
            {
                stop = clock();
                //showListBF(list, Pclose);
                showSolutionBF(list, t + i);
                return true;
            }
        }
    }
}

bool compareDF(int closed[CLOSED_MAX][12], int open[OPEN_MAX][12], int nextNode[12], const int Pclose, const int Popen)
{
    int i;
    for (i = 0; i < Pclose; i++)
    {
        if (isSame(&closed[i][2], &nextNode[2]))
        {
            return false;
        }
    }
    for (i = 0; i < Popen; i++)
    {
        if (isSame(&open[i][2], &nextNode[2]))
        {
            return false;
        }
    }
    return true;
}

void createNodeDF(int closed[CLOSED_MAX][12], int open[OPEN_MAX][12], int type, int index, const int Pclose, int *Popen)
{
    int nextNode[12];
    memcpy(nextNode, closed[Pclose], 12 * sizeof(int));

    nextNode[0] = Pclose + 1;
    nextNode[1] = type;
    nextNode[11] = closed[Pclose][11] + 1;

    switch (type)
    {
    case UP:   swap(&nextNode[index], &nextNode[index - 3]); break;
    case LEFT: swap(&nextNode[index], &nextNode[index - 1]); break;
    case DOWN: swap(&nextNode[index], &nextNode[index + 3]); break;
    case RIGHT:swap(&nextNode[index], &nextNode[index + 1]); break;
    }

    if (compareDF(closed, open, nextNode, Pclose, *Popen))
    {
        memcpy(open[*Popen], nextNode, 12 * sizeof(int));
        (*Popen)++;
        if (*Popen == OPEN_MAX - 1)
        {
            printf("open array out! \n");
        }
    }
}

void findNextNodeDF(int closed[CLOSED_MAX][12], int open[OPEN_MAX][12], int Pclose, int *Popen)
{
    int index, i;
    int flag_node[4] = { 1,1,1,1 };

    index = findIndex0(&closed[Pclose][2]);

    if (index == 0 || index == 1 || index == 2)
        flag_node[UP - 1] = 0;
    if (index == 0 || index == 3 || index == 6)
        flag_node[LEFT - 1] = 0;
    if (index == 6 || index == 7 || index == 8)
        flag_node[DOWN - 1] = 0;
    if (index == 2 || index == 5 || index == 8)
        flag_node[RIGHT - 1] = 0;
    if (closed[Pclose][1] == 1 || closed[Pclose][1] == 2)
        flag_node[closed[Pclose][1] + 1] = 0;
    else if (closed[Pclose][1] == 3 || closed[Pclose][1] == 4)
        flag_node[closed[Pclose][1] - 3] = 0;

    for (i = 0; i < 4; i++)
    {
        if (flag_node[i])
        {
            createNodeDF(closed, open, i + 1, index + 2, Pclose, Popen);
        }
    }
}

void showListDF(int closed[CLOSED_MAX][12], int open[OPEN_MAX][12], const int Popen)
{
    int i, j, k;
    printf("\n     --------- CLOSED ---------\n\n");
    for (i = 0; i < CLOSED_MAX; ++i)
    {
        if (closed[i][0] == 0 && closed[i][1] == 0 && i>1)
            break;
        printf("%5d", i + 1);
        for (j = 0; j < 12; ++j)
        {
            printf("%5d", closed[i][j]);
        }
        printf("\n");
    }
    printf("\n     ---------- OPEN ----------\n\n");
    for (j = 0; j < OPEN_MAX; ++j)
    {
        if (j == Popen)
            break;
        printf("%5d", i + j + 1);
        for (k = 0; k < 12; ++k)
        {
            printf("%5d", open[j][k]);
        }
        printf("\n");
    }
}

void showSolutionDF(int closed[CLOSED_MAX][12], int Pclose)
{
    int sln[SLN_MAX][12] = { 0 };
    char option[5] = { ' ', 'L', 'U', 'R', 'D' };
    int i, j;
    for (i = 0; i < SLN_MAX; ++i)
    {
        memcpy(sln[i], closed[Pclose], 12 * sizeof(int));
        if (Pclose == 0)
            break;
        Pclose = sln[i][0] - 1;
        if (i == SLN_MAX - 1)
        {
            printf("sln array out! \n");
        }
    }
    printf("\n    --------- process ---------\n\n");
    for (; i >= 0; i--)
    {
        for (j = 2; j < 11; ++j)
        {
            printf("%3d", sln[i][j]);
            if (j == 4 || j == 7 || j == 10)
                printf("\n");
        }
        if (i > 0)
        {
            printf("%c\n", option[sln[i - 1][1]]);
        }
    }
}

bool depthFirstSearch(const int original_node[9], const int target_node[9])
{
    start = clock();
    int open[OPEN_MAX][12] = { 0 };//father option data... depth
    int closed[CLOSED_MAX][12] = { 0 };
    int Pclose = 0, Popen = 1;
    int t = 0;

    if (isSame(original_node, target_node))
    {
        printf("the original node is equal to target node.\n");
        return true;
    }

    memcpy(&open[0][2], original_node, 9 * sizeof(int));

    for (int cnt = 0; ; cnt++)
    {
        if (Popen == 0)
        {
            return false;
        }
        memcpy(closed[Pclose], open[Popen-1], 12 * sizeof(int));
        t = --Popen;
        if (closed[Pclose][11] < DEPTH_LIMIT)      //judge DEPTH_LIMIT
        {
            findNextNodeDF(closed, open, Pclose, &Popen);
        }
        Pclose++;

        for (int i = 0; i < Popen - t; ++i)
        {
            if (isSame(&open[t + i][2], target_node))
            {
                memcpy(closed[Pclose], open[t + i], 12 * sizeof(int));
                stop = clock();
                showListDF(closed, open, Popen);
                showSolutionDF(closed, Pclose);
                return true;
            }
        }
    }
}

