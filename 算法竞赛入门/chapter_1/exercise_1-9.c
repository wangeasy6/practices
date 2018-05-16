/*
* 算法竞赛入门 1.5.6
*     习题 1-9
* 编译环境：Win10 + g++.exe (GCC) 3.4.0 (mingw special)
*/

#include <stdio.h>
#include <math.h>

int main()
{
      int a,b,c, t;
      scanf("%d %d %d", &a, &b, &c);
      if(a < b)
      {
            t = a;
            a = b;
            b = t;
      }
      if(a < c)
      {
            t = a;
            a = c;
            c = t;
      }

      if(a <= 0 || b <=0 || c <=0 || a >= (b+c))
      {
            printf("not a triangle\n");
            return 0;
      }

      if(pow(a, 2.0) == (pow(b, 2.0) + pow(c, 2.0)))
      {
            printf("yes\n");
      }
      else
      {
            printf("no\n");
      }

      return 0;
}
