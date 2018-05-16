/*
* 算法竞赛入门 1.5.6
*     习题 1-1
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>

#define ARRY_LEN 3

int main()
{
      int i;
      double arry[ARRY_LEN], tmp, avr;

      for(i = 0; i < ARRY_LEN; i++)
      {
            scanf("%lf", &arry[i]);
      }

      tmp = (arry[0] - arry[ARRY_LEN-1]) / 2;
      avr = arry[0] + tmp;
      for(i = 1; i < ARRY_LEN; i++)
      {
            printf("%lf\n", avr);
            tmp = (avr - arry[i]) / 2;
            avr = arry[i] + tmp;
      }

      printf("%.3lf\n\n", avr);
      /*
      1 2 5
      -1.000000
      0.500000
      2.750000
      */

      for(i = 0; i < ARRY_LEN; i++)
      {
            scanf("%lf", &arry[i]);
            printf("%.3lf\n", arry[i]);
      }
      printf("%.3lf\n", (arry[0] + arry[1] + arry[2]) / 3.0 );      // 2.666667
      // 依次算平均值，会有精度上的误差，但是三位相加计算可能会 溢出

      return 0;
}
