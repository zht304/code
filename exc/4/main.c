#include <fcntl.h>
#include <stdio.h>
//#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>


#define err_ret(...)\
	do{\
		printf(__VA_ARGS__);\
		return -1;\
	}while(0); 

off_t get_cur_offset(int fd)
{
	return lseek(fd, 0, SEEK_CUR);
}

void dbg_curr_offset(int fd)
{
	printf("curr seek offset of fd %d is: %d \n", fd, get_cur_offset(fd));
}

void dump_stat(struct stat *buf)
{
	char *s = NULL;
	char mode[10] = {0};
	int i;

	printf("st_mode: %x\n", buf->st_mode);
	printf("st_uid: %x\n", buf->st_uid);
	printf("st_gid: %x\n", buf->st_gid);

	if(S_ISREG(buf->st_mode))
		s = ("regular file");
	else if(S_ISDIR(buf->st_mode))
		s =("direcotory");
	else if(S_ISBLK(buf->st_mode))
		s =("block special file");
	else if(S_ISCHR(buf->st_mode))
		s =("character special file");
	else if(S_ISFIFO(buf->st_mode))
		s =("fifo file");
	else if(S_ISLNK(buf->st_mode))
		s =("link file");
	else if(S_ISSOCK(buf->st_mode))
		s =("socket file");


	printf("%s", s);
	if(buf->st_mode & S_ISUID )
		printf(", set uid");
	if(S_ISGID & (buf->st_mode))
		printf(", set gid");

	for(i = 0; i < 9; ++i)
		mode[i] = '-';
	if(buf->st_mode & S_IRUSR)
		mode[0] = 'r';
	if(buf->st_mode & S_IWUSR)
		mode[1] = 'w';
	if(buf->st_mode & S_IXUSR)
		mode[2] = 'x';
	if(buf->st_mode & S_IRGRP)
		mode[3] = 'r';
	if(buf->st_mode & S_IWGRP)
		mode[4] = 'w';
	if(buf->st_mode & S_IXGRP)
		mode[5] = 'x';
	if(buf->st_mode & S_IROTH)
		mode[6] = 'r';
	if(buf->st_mode & S_IWOTH)
		mode[7] = 'w';
	if(buf->st_mode & S_IXOTH)
		mode[8] = 'x';

	mode[9] = '\0';

	printf(", %s", mode);

	putchar('\n');


}
int main(int argc, char*argv[])
{
	int 	fd = -1, newfd = -1, fd2 = -1;
	struct 	stat buf;
	int 	ret;
	int	i;

	fd = open("testfile", O_RDWR /*| O_CREAT */, S_IRWXU);
	if(fd == -1) {
		err_ret(("open file failed! \n"));
		/*printf("open file failed!\n");
		return -1;*/
	}

	ret = stat("./testfile", &buf );
	printf("stat ret %d\n", ret);


	dump_stat(&buf);


	ret = fstat(fd, &buf);

	dump_stat(&buf);


	for(i = 1; i < argc; ++i) {
		printf("%s\n", argv[i]);
		puts("===================");
		if(lstat(argv[i], &buf) != 0) {
			printf("error: \n");
			continue;
		}

		dump_stat(&buf);
	}

	if(fd > 0)
		close(fd);
	fd = -1;
	return 0;
}
