#include<stdio.h>
int main() {
  int m;
  printf("Input row/column size:");
  scanf("%d", &m);
  int a[100][100], i, j, n;
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &a[i][j]);
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++) {
      if (a[i][j] == 1) {
        if (a[j][i] == 0)
          break;
      }
    }
    printf("Symmetric");
  }
/* 判断对称还这么写了
 if(a[i][j]！=a[j][i]&&i！=j||a[i][j]==0&&a[j][i]==0 break;
   else  printf("对称");*/

  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      if (a[i][j] + a[j][i] == 2 && i == j) break;
      else printf("Not symmetric");
    }

  int k;
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++)
      if (a[i][j] == 1) {
        for (k = 0; k < m; k++)
          if (a[j][k] == 1 && a[j][k] == 1) break;
      }
    printf("Transitive");
  }
}