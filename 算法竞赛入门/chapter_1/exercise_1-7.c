/*
* 算法竞赛入门 1.5.6
*     习题 1-7
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>

int main()
{
      int n;
      scanf("%d", &n);
      printf("%.2lf\n", n>3?n*95*0.85:n*95);
      return 0;
}
