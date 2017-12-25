/*
*	这是一个简单的事件推送示例
* 	事件检测程序负责检测是否有事件发生
* 	主程序维护一个事件的回掉注册表，当有事件发生的时候，将消息发送给所有注册的回掉程序
*/

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "pthread.h"
#include "sys/time.h"

enum Boolean{
	false = 0,
	true = (!false)
};

typedef enum		//事件类型，可以根据自己的需要而添加
{
	T_NOTICE = 0,
	T_TIME = 1
}event_type;

typedef struct 		//事件消息定义
{
	event_type type;
	union{
		char txt[200];
		time_t time;
	}content;		//两类消息，对应的有自己的数据类型
}event_msg;
event_msg g_msg;
volatile static event_flag = false;

typedef void (*event_cb)(event_msg *msg);	//回调申明
unsigned int event_num = 0;		//MAX值此处未定义
typedef struct event_factory	//回调函数的注册表
{
	event_cb cb;
	struct event_factory *next;
}EVENT_FACTORY;
EVENT_FACTORY event_head;

int event_factory_init()
{
	memset(&event_head,0,sizeof(event_head));
	event_head.cb = NULL;
	event_head.next = NULL;
	return true;
}

int event_factory_insert(event_cb cb)
{
	if(cb == NULL)
		return false;

	EVENT_FACTORY *new = NULL,*tmp = NULL;

	if(event_num == 0)
	{
		event_head.cb = cb;
	}
	else
	{
		new = malloc(sizeof(EVENT_FACTORY));
		memset(new,0,sizeof(EVENT_FACTORY));
		new->cb = cb;
		new->next = NULL;
		tmp = &event_head;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	event_num++;

	return true;
}
int event_factory_delete(void)
{
	EVENT_FACTORY *tmp,*now=&event_head;
	while(now->next != NULL)
	{
		tmp = now;
		now = now->next;
		free(tmp);
	}
	return true;
}

static void UI_process(event_msg *msg)		//模拟UI处理线程
{
	switch(msg->type)
	{
		case T_NOTICE:
			printf("%s, %s\n", __FUNCTION__, (char *) &msg->content);
			break;
		case T_TIME:
			printf("%s, Display %d\n", __FUNCTION__, *(int*)&msg->content.time);
			break;
		default:
			printf("%s, event_type error\n", __FUNCTION__);
			break;
	}
}

static void Music_process(event_msg *msg)	//模拟音乐播放器处理线程
{
	switch(msg->type)
	{
		case T_NOTICE:
			printf("%s, %s\n",__FUNCTION__, (char *) &msg->content);
			break;
		case T_TIME:
			printf("%s, jump\n",__FUNCTION__);
			break;
		default:
			printf("%s, event_type error\n", __FUNCTION__);
			break;
	}
}

static void* event_process(void* data)		//模拟事件响应，不同进程使用消息队列来发送消息
{
	struct timeval tv;
	struct timezone tz;
	while(1){
		while(event_flag == true) sleep(0.2);
		printf("check get T_NOTICE\n");			//while(get_notice());
		memset(&g_msg, 0, sizeof(g_msg));
		g_msg.type = T_NOTICE;
		strncpy(g_msg.content.txt,"test",sizeof(g_msg.content.txt));
		event_flag = true;
		sleep(2);

		while(event_flag == true) sleep(0.2);
		printf("check get T_TIME\n");			//while(get_time());
		memset(&g_msg, 0, sizeof(g_msg));
		g_msg.type = T_TIME;
		gettimeofday(&tv, &tz);
		g_msg.content.time = tv.tv_sec;
		event_flag = true;
		sleep(2);
	}
	pthread_exit(0);
}

int main()
{
	int i = 0;
	pthread_t event_thread;
	EVENT_FACTORY *tmp = NULL;
	event_factory_init();
	event_factory_insert(UI_process);
	event_factory_insert(Music_process);

	if(0 != pthread_create(&event_thread, NULL, event_process, NULL))
	{
		perror("event_thread create");
	}

	while(1)
	{
		while(event_flag == false) sleep(0.2);
		tmp = &event_head;
		for(i = 0; i < event_num ; i++)
		{
			if(tmp->cb == NULL) continue;
			tmp->cb(&g_msg);
			tmp = tmp->next;
		}
		event_flag = false;
		printf("------------\n");
	}
	if(0 !=pthread_join(event_thread,NULL))
		perror("pthread_join");
	event_factory_delete();
	return 0;
}
