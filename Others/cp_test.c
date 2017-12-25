/*
*     功能：
*           测试两个线程，当一个线程在读文件的时候，另一个线程是否可以拷贝这个文件
*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define FILE_NAME "/mnt/usrdb/common.dat"
#define FILE_CP_CMD "cp /mnt/usrdb/common.dat /mnt/usrdb/back_common.dat"

void *thread_A(void *arg)
{
      FILE *fd = NULL;
      char buf[50] = {0};

      fd  = fopen(FILE_NAME, "r");
      if ( fd == NULL )
      {
            perror("thread_A fopen");
      }
      else
      {
            printf("pthread_A fopen success\n");

            if (fread(buf, 1, sizeof(buf),   fd ) == 0)
            {
                  printf("thread_A fwrite error\n");
            }
            printf("pthread_A fread success, buf:%s\n", buf);

            printf("pthread_A sleep\n");
            sleep(5);
            printf("pthread_A wake\n");

            printf("pthread_A fclose\n");
            fclose(fd);
      }

}

void *thread_B(void *arg)
{
      printf("pthread_B sleep\n");
      sleep(1);
      printf("pthread_B wake\n");

      printf("pthread_B cp\n");
      system(FILE_CP_CMD);
      system("sync");
      printf("pthread_B cp done\n");
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
*           程序无中断，拷贝正常
*/