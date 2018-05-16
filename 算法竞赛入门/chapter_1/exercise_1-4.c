/*
* 算法竞赛入门 1.5.6
*     习题 1-4
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>
#include <math.h>

double h2j(int n)
{
/* Define in math.h
M_PI        pi    //!!!!!!!!!!!!!!!!!这就是PI常数 M_PI
M_PI_2      One-half pi
M_PI_4      One-fourth pi
M_1_PI      One divided by pi
M_2_PI      Two divided by pi
M_1_SQRTPI        One divided by the square root of pi 
M_2_SQRTPI        Two divided by the square root of pi
*/
      return M_PI / 180 * n;
}

int main()
{
      int n;
      scanf("%d", &n);
      if(n >= 360 || n <= 0)
            return -1;
      printf("%lf %lf\n", sin(h2j(n)), cos(h2j(n)));
      // sin 函数 的参数是使用弧度制的,而不是角度制
      // 弧度与角度的关系为： 弧度 = 180 / π 角度 or 角度 = π / 180 弧度
      return 0;
}
