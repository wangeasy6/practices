/*
*     功能：
*           测试使用一个全局的文件描述符，两个线程分别用这个全局描述符去写两个不同的文件
*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define FILE_1 "/mnt/usrdb/1.txt"
#define FILE_2 "/mnt/usrdb/2.txt"

FILE *g_fd = NULL;

void *thread_A(void *arg)
{
      char buf[100] = {0};
      memset(buf, '1', sizeof(buf));
      buf[99] = '\n';

      while(1)
      {
            g_fd  = fopen(FILE_1, "a+");
            if ( g_fd == NULL )
            {
                  perror("thread_A fopen");
            }
            else
            {
                  if (fwrite(buf, 1, sizeof(buf),   g_fd ) == 0)
                  {
                        printf("thread_A fwrite error\n");
                  }
                  fclose(g_fd);
            }
      }

}

void *thread_B(void *arg)
{
      char buf[100] = {0};
      memset(buf, '2', sizeof(buf));
      buf[99] = '\n';

      while(1)
      {
            g_fd  = fopen(FILE_2, "a+");
            if ( g_fd == NULL )
            {
                  perror("thread_B fopen");
            }
            else
            {
                  if (fwrite(buf, 1, sizeof(buf),   g_fd ) == 0)
                  {
                        printf("thread_B fwrite error\n");
                  }
                  fclose(g_fd);
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
*     结果：
*           会有两个问题：1、重复close；2、写出的文件有空洞
*/