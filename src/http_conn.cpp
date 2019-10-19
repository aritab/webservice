#include "http_conn.h"
const char* ok_200_title="OK";
const char* error_400_title="BAD Request";
const char* error_400_form="Your request has bad syntax or is inherently impossible to satisfy.\n";
const char* error_403_title="Forbidden";
const char* error_403_form="You do not have permission to get file from this server.\n";
const char* error_404_title="Not Found";
const char* error_404_form="The requested file was not found on this server.\n";
const char* error_500_title="Internal Erroe";
const char* error_500_form="There was an unusual problem servng the requested file.\n";
const char* doc_root="/var/www/html";
int setnonblocking(int fd)
{
	int old_option=fcntl(fd, F_GETFL);
	int new_option=old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void addfd(int epollfd, int fd, bool one_shot)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN | EPOLLRDHUP;
	if(one_shot){
		event.events!=EPOLLONESHOT;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}


