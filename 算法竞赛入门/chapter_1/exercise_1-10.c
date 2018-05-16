/*
* 算法竞赛入门 1.5.6
*     习题 1-10
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>

int main()
{      
      int n;
      scanf("%d", &n);
      printf("%s\n", ( (n%400 == 0)||(n%100 != 0 && n%4 == 0) )?"yes":"no");
      // 判断闰年的标准是：1、能整除4且不能整除100  2、能整除400
      return 0;
}
