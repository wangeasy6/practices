/*
*     功能：
*           测试两个线程，同时调用同一个函数对两个变量赋值，会不会存在交叉的情况
*/
#include <stdio.h>
#include <pthread.h>

int n;
int a1, a2;

void check_AB(void)
{
      a1 = n;
      a2 = n;
      n ++;
}

void *thread_A(void *arg)
{
      while(1)
      {
            check_AB();
            if (a1 != a2)
            {
                  printf("[Check_Error][%s] a1 = %d, a2 = %d\n",__FUNCTION__, a1, a2);
            }
      }
}

void *thread_B(void *arg)
{
      while(1)
      {
            check_AB();
            if (a1 != a2)
            {
                  printf("[Check_Error][%s] a1 = %d, a2 = %d\n",__FUNCTION__, a1, a2);
            }
      }
}

int main()
{
      pthread_t thr_a, thr_b;
      void *ret_a, *ret_b;

      if( pthread_create(&thr_a, NULL, thread_A, NULL) != 0)
      {
            printf("pthread create A, failed\n");
            return 0;
      }
      if( pthread_create(&thr_b, NULL, thread_B, NULL) != 0)
      {
            printf("pthread create B, failed\n");
            return 0;
      }

      if(!pthread_join(thr_a, &ret_a))
      {
            printf("thread A exit\n");
      }

      if(!pthread_join(thr_b, &ret_b))
      {
            printf("thread B exit\n");
      }

      return 1;
}

/*
    结果：
            [Check_Error][thread_B] a1 = 221999550, a2 = 221999549
            [Check_Error][thread_B] a1 = 222001833, a2 = 222001834
            [Check_Error][thread_B] a1 = 222004130, a2 = 222004131
            [Check_Error][thread_A] a1 = 222004130, a2 = 222004131
            [Check_Error][thread_A] a1 = 222081715, a2 = 222081716
            [Check_Error][thread_A] a1 = 222084177, a2 = 222084176
            [Check_Error][thread_A] a1 = 222086479, a2 = 222086480
            [Check_Error][thread_B] a1 = 222086479, a2 = 222086480
            [Check_Error][thread_B] a1 = 222094223, a2 = 222094223
            [Check_Error][thread_B] a1 = 222096623, a2 = 222096624
            [Check_Error][thread_A] a1 = 222096623, a2 = 222096624
            [Check_Error][thread_A] a1 = 222112395, a2 = 222112396
            [Check_Error][thread_B] a1 = 222112395, a2 = 222112396
            [Check_Error][thread_B] a1 = 222122604, a2 = 222122605
*/