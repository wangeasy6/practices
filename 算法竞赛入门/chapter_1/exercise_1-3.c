/*
* 算法竞赛入门 1.5.6
*     习题 1-3
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>

int main()
{
      int n, avr;
      scanf("%d", &n);
      printf("%d\n", n&0x01?(n+1)*(n/2)+n/2 + 1:(n+1)*(n/2));
      return 0;
}
