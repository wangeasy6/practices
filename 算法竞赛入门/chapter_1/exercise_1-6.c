/*
* 算法竞赛入门 1.5.6
*     习题 1-6
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>

int main()
{
      int n;
      scanf("%d", &n);
      printf("%s\n", n&0x01?"no":"yes");
      return 0;
}
