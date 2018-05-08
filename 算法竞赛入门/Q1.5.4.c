/*
* 算法竞赛入门 1.5.4
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>
#include <limits.h>

int main()
{
      /*************** 1 ******************/
      int max = 0x7fffffff, min = max + 1;
      /*
      int max = 0xffffff, min;
      while(max+1 > max)
      {
            max++;
      }
      min = max + 1;
      */
      printf("%d %d\n", max, min);        // 2147483647 -2147483648
      //0x7fffffff 是 32 位个1

      /*************** 2 ******************/
      printf("%lf\n", 0.0000001);
      //最大精度为小数点后6位

      /*************** 3 ******************/
      //减去小数的6位，最大值为26位，0x3ffffffffffffff(此路不通，不确定存储方式和位数)
      //逐步逼近法，再使用 ++，需要运行很久的时间
      /*（先通过 *10 确定数量级）
      double max_d = 1/-1, min_d,tmp = 10,i;
      for(i = 0; i < 400; i++)
      {
            max_d *= tmp;
            printf("%lf\n", max_d);
      }
      // 99999999999999981000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000
      // -99999999999999981000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000
      // 308 位
      */
      //再用tmp作为间隔递增
      double max_d = 179769313486172390000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000,\
       min_d,tmp = 9999999810000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000;   
      while(max_d+tmp != 1.0/0.0)
      {
            max_d += tmp;
            printf("%lf\n", max_d);
      }
      min_d = max_d + tmp;
      printf("%lf %lf\n", max_d, min_d);
      //按照以下演进，tmp 每次减少4位运行，就可以让 max_d 的精确度增加 4 位

      /*************** 4 ******************/
      printf("%d\n", 0&&1||1);      // 1
      // 说明优先级从左向右

      /*************** 5 ******************/
      //简略

      return 0;
}
