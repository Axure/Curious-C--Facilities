#include<stdio.h>
#include<stdbool.h>
int main() {
  int m;
  printf("Input row/column size:\n");
  scanf("%d", &m);
  int a[100][100], i, j, n;
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &a[i][j]);
  bool sym_flag = true;
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++) {
      if (a[i][j] != a[j][i]) {
        sym_flag = false;
        break;
      }
    }
    if (!sym_flag) break;
  }
  if (sym_flag) printf("Symmetric\n");

  bool asym_flag = true;
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      if (a[i][j] != -a[j][i]) {
        asym_flag = false;
        break;
      }
      if (!asym_flag) break;
    }
  if (asym_flag) printf("Symmetric\n");

  int k;
  bool trans_flag = true;
  for (i = 0; i < m; i++) {
    for (j = 0; j < m; j++)
      if (a[i][j] == 1) {
        for (k = 0; k < m; k++)
          if (!(a[i][k] == 1 && a[k][j] == 1)) {
            trans_flag = false;
            break;
          }
        if (!trans_flag) break;
      }
    if (!trans_flag) break;
  }
  if (trans_flag) printf("Transitive\n");
}