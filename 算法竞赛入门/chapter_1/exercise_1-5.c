/*
* 算法竞赛入门 1.5.6
*     习题 1-5
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>
#include <stdlib.h>     // abs
#include <math.h>

int main()
{
      int x1,y1,x2,y2, distance;
      scanf("%d %d %d %d", &x1,&y1,&x2,&y2);
      printf("%lf\n", sqrt(pow(abs(x1 - x2), 2.0) + pow(abs(y1 - y2), 2.0)));
      return 0;
}
