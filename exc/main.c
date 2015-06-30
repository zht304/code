#include <fcntl.h>
#include <stdio.h>
//#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

off_t get_cur_offset(int fd)
{
	return lseek(fd, 0, SEEK_CUR);
}

void dbg_curr_offset(int fd)
{
	printf("curr seek offset of fd %d is: %d \n", fd, get_cur_offset(fd));
}

int main(int argc, char*argv[])
{
	int fd = -1, newfd = -1, fd2 = -1;
	char name [256]  = {0};
	int i;
	off_t offset;
	ssize_t rd;
	int fdflag = 0;

	for(i = 0; i < 256; ++i)
		name[i]= 'a';
//	name[254] = '\0';

	fd = open("testfile", O_RDWR | O_CREAT, S_IRWXU);
	printf("open file hd = %d\n", fd);
	printf("NAME_MAX = %d\n", NAME_MAX);
	dbg_curr_offset(fd);
	lseek(fd, 2, SEEK_SET);
	write(fd, "abc", 4);
	dbg_curr_offset(fd);
	
	lseek(fd, -2, SEEK_CUR);
	rd = read(fd, name, 3);
	printf("rd=%d, cont=%s\n", rd, name);

	dbg_curr_offset(fd);
	lseek(fd, 0, SEEK_SET);
	rd = pread(fd, name, 3, 0);
	dbg_curr_offset(fd);

	newfd = dup(fd);
	printf("new fd = %d\n", newfd);

	fd2 = fcntl(fd, F_DUPFD, 0);
	printf("fcntl dup: fd2=%d\n", fd2);

	fdflag = fcntl(fd, F_GETFD);
	printf("fdflag of fd = %d\n", fdflag);
	
	fdflag = fcntl(fd2, F_GETFD);
	printf("fdflag of fd2 = %d, FD_CLOEXEC=%d\n", fdflag ,FD_CLOEXEC);

	close(fd);

	rd = pread(newfd, name, 3, 2);
	printf("read the newfd after the fd has been closed: %d, %s\n", rd, name);

	fd = open(name, O_RDWR | O_CREAT, S_IRWXU);
	printf("open long name fd = %d, ENAMETOOLONG=%d, errno=%d\n", fd, ENAMETOOLONG, errno);
	
	dbg_curr_offset(STDIN_FILENO);
	dbg_curr_offset(STDOUT_FILENO);
	dbg_curr_offset(STDERR_FILENO);

	if(fd > 0)
		close(fd);
	fd = -1;
	return 0;
}
