#include <stdio.h>
#include <unistd.h>

/* Import user configuration: */
#include <sys/epoll.h>
#include <uk/print.h>


int main(int argc __unused, char *argv[] __unused)
{
        int epoll_fd;
        int stdin_fd = 0;
        struct epoll_event event;

        uk_pr_debug("running main.c from app/helloworld\n");
	epoll_fd = epoll_create(0);

	if(epoll_fd < 0) {
    		perror("Failed to create epoll file descriptor\n");
    		return 1;
  	}
	uk_pr_debug("epoll file descriptor opened successfully (fd = %d)\n", epoll_fd);

	/* Listen for input on file descriptor 0 (stdin) */
	event.events = EPOLLIN;
	event.data.fd = stdin_fd;

        if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, stdin_fd, &event) < 0)
        {
                perror("failed to add file descriptor to epoll\n");
                close(epoll_fd);
                return 1;
        }

  	if(close(epoll_fd)) {
    		perror("Failed to close epoll file descriptor\n");
    		return 1;
  	}
  	return 0;
}
