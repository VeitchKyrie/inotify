/*
 *Inotify 是一个 Linux特性，它监控文件系统操作，比如读取、写入和创建。
 */
 
/********************************头文件****************************************/
#include <sys/inotify.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
/********************************宏定义****************************************/
#define INOTIFY_EVENT_BUF_SIZE  512
/*********************************函数*****************************************/
int main(int argc, char const *argv[])
{
	int inot_fd;
	int wd;
    char const *mont_dir; /*监视的目录*/
    char event_buf[INOTIFY_EVENT_BUF_SIZE];
	int event_buf_len;
    int inot_event_size;
    int offset = 0;
    char * ptmp;
    struct inotify_event *event;

	if (argc != 2) {
		printf("usage: %s <dir>\n", argv[0]);
		return -1;
	}

    mont_dir = argv[1];
    inot_fd = inotify_init();

	/* add watch ,监视目录下的文件创建于删除*/
    wd = inotify_add_watch(inot_fd, mont_dir, IN_DELETE | IN_CREATE);

    inot_event_size = sizeof(struct inotify_event);

	/* read */
	while (1) {
        event_buf_len = read(inot_fd, event_buf, INOTIFY_EVENT_BUF_SIZE);

        if(event_buf_len < inot_event_size) {
            if(errno != EINTR)
            printf("could not get event, %s\n", strerror(errno));
        }

        ptmp = event_buf;
        while(event_buf_len) {
            event = (struct inotify_event *)ptmp;
            if(!event->len)
                goto next;

            if (event->wd != wd) 
                goto next;
                
            if(event->mask & IN_CREATE) 
                printf("create file: %s\n", event->name);
            if(event->mask & IN_DELETE)
                printf("delete file: %s\n", event->name);

        next:  
            offset = inot_event_size + event->len;
            event_buf_len -= offset;
            ptmp += offset;
        }
	}

    return 0;
}
