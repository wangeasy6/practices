/*
*     功能：
*           检测日志中的全局变量，以及变量地址
*     详细：
*           此全局变量只有开机的时候为 '0',之后为 '1'；还要全局变量地址使用 %p 打印出来
*/
#include <stdio.h>
#include <string.h>

#define VAR_STR "CASaveBackup="
#define ADDR_STR "addr="
#define INIT_INFO_P_TIMES 2

int main(int argc,char **argv)
{
      if(argc != 2)
      {
            printf("Usage: %s [log_file_name]\n", argv[0]);
            return 0;
      }

      FILE *fd = NULL;
      char *p = NULL;
      char buf[1024*4] = {0};
      char var = '0';
      char addr[16] = {0};
      unsigned int count_var = 0, count_addr = 0;
      unsigned int line = 0,read_len = 0,i = 0,j = 0,count = 1;

      fd = fopen(argv[1], "r");
      if (fd == NULL)
      {
            perror("fopen");
            return 0;
      }

      while (!feof(fd))
      {
            fgets(buf, sizeof(buf), fd);
            read_len = strlen(buf);
            ++line;

            if ( strstr(buf, "dtv_media") && strstr(buf, "start"))      // 开机标志，重新开机则重置
            {
                  count = 1;
                  var = '0';
                  continue;
            }

            if(p = strstr(buf, VAR_STR))
            {
                  p += strlen(VAR_STR);
                  if(var != *p)
                  {
                        count_var ++;
                        printf("[Var_Error] LINE: %d, TXT: %s\n", line, buf);
                  }
                  else
                  {
                        if ( var == '0' )
                        {
                              #if (INIT_INFO_P_TIMES == 1)
                                    var = '1';
                              #else
                                    if (count == INIT_INFO_P_TIMES)       // 开机为 '0' 的会打印N次
                                    {
                                          var = '1';
                                          count = 1;
                                    }
                              count ++;
                              #endif
                        }

                        if(p = strstr(buf, ADDR_STR))
                        {
                              if(addr[0] == 0)
                              {
                                    for(i=(p-buf)+strlen(ADDR_STR),j=0; j<sizeof(addr) && i<read_len;j++, i++)
                                    {
                                          addr[j] = buf[i];
                                          if(buf[i] == ' ')
                                          {
                                                break;
                                          }
                                    }
                                    printf("Var_Addr: %s\n", addr);
                              }
                              else
                              {
                                    if(NULL == strstr(buf, addr))
                                    {
                                          count_addr ++;
                                          printf("[Addr_Error] LINE: %d, TXT: %s\n", line, buf);
                                    }
                              }
                        }
                  }
            }
      }

      printf("Test Result: All_Line:%d, Var_Error: %d, Addr_Error: %d\n",line, count_var, count_addr);
      fclose(fd);
      return 1;
}