#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"graphics.h"
#define MAXNUM 50

void initGraph() {
  /* 要求自动检测 */
  int gdriver = DETECT, gmode, errorcode;

  /* 初始化图形模式 */
  initgraph(&gdriver, &gmode, "");

  /* 读取初始化结果 */
  errorcode = graphresult();

  if (errorcode != grOk)  /* 发生错误 */
  {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);             /* 具有错误代码的返回 */
  }
}

int main() {
  int m, n, i, j, x, maze[50][50];
  int move[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
  int *quei[2500] = {0};//储存行坐标队列
  int *quej[2500] = {0};//储存列坐标队列
  int *prep[2500] = {0};//储存之前一步在队列中的位置
  int head, rear, length;//队列头，队列尾，队列长度
  head = 0;
  rear = 1;
  length = 1;
  quei[head] = 1;
  quej[head] = 1;
  prep[head] = -1;//入口位置进队列

  int pos;//当前节点在队列中的位置，
  int ii, jj, ni, nj;//当前节点的坐标，新节点的坐标
  int dir;//移动方向

  scanf("%d%d", &m, &n);
  for (i = 0; i <= m + 1; i++) {
    for (j = 0; j <= n + 1; j++) {
      if (i == 0 || j == 0 || i == m + 1 || j == n + 1)
        maze[i][j] = 1;
      else {
        x = rand() % 1000;
        if (x > 700) { maze[i][j] = 1; } //控制矩阵中1的个数，太多1迷宫很容易走不通
        else { maze[i][j] = 0; }
      }
      if (i == m && j == n) maze[i][j] = 0;
      printf("%d ", maze[i][j]);
    }
    printf("\n");
  }
  //以上是输入和迷宫生成，一下是走迷宫

  if (maze[1][1] == 1)length = 0;//第一点就不能通过
  else maze[1][1] = 1;
  while (length)//队列非空继续
  {
    for (pos = head; pos < head + length; pos++)//寻找这一层所有节点
    {
      ii = quei[pos];
      jj = quej[pos];//当前位置坐标
      if (ii == m && jj == n)break;
      for (dir = 0; dir < 4; dir++)//寻找8个方向
      {
        ni = ii + move[dir][0];
        nj = jj + move[dir][1];//新坐标
        if (maze[ni][nj] == 0)//如果没有走过
        {
          quei[rear] = ni;
          quej[rear] = nj;
          prep[rear] = pos;//新节点入队
          rear = rear + 1;
          maze[ni][nj] = 1;//标记已经走过
        }
      }
    }
    if (ii == m && jj == n)break;
    head = head + length;
    length = rear - head;//这一层节点出列
  }
  int len = 300 / (m > n ? m : n);
  initGraph();  /*初始化图形模式*/
  cleardevice();
  setbkcolor(10);
  setcolor(4);
  setfillstyle(1, 4);
  for (i = 0; i < m + 2; i++)
    for (j = 0; j < n + 2; j++) {
      if (1 == mg[i][j]) {
        setfillstyle(1, 4);
        /*设定每个格子宽为20个单位，高为20个单位*/
        bar(50 + j * len, 50 + i * len, 50 + len + j * len, 50 + len + i * len);/*sleep(1);*/
      }
      else {
        setfillstyle(1, 15);
        bar(50 + j * len, 50 + i * len, 50 + len + j * len, 50 + len + i * len);/*sleep(1);*/\

      }
    }

  if (ii == m && jj == n) {

    while (pos != -1) {

      printf("%d,%d\n", quei[pos], quej[pos]);
      setfillstyle(1, 6);
      setcolor(2);
      circle(50 + (quej[pos]) * len + len / 2, 50 + (quei[pos]) * len + len / 2, len / 2);
      pos = prep[pos];

    }

  }

  else {

    printf("THERE IS NO PATH.");

  }


  delete[]quei;

  delete[]quej;

  delete[]prep;

  return 0;
}