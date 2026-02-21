#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFSIZE 4096

int
main(int argc, char *argv[])
{
	ssize_t n = 0;
	char buf[BUFSIZE];

	if(argc != 4)
	{
		write(STDERR_FILENO, 
				"try: ./program <origin dir> <file> <destiny dir>\n",
					sizeof("try: ./program <origin dir> <file> <destiny dir>\n") -1);
		exit(1);
	}

	int dirfd_src = open(argv[1], O_RDONLY);
	if(dirfd_src < 0)
	{
		perror("open origin directory");
		exit(1);
	}

	int fd_src = openat(dirfd_src, argv[2], O_RDONLY);
	if(fd_src < 0)
	{
		perror("open origin file");
		exit(1);
	}

	if(close(dirfd_src))
  	{
	perror("close");
	exit(1);
  	}

	int dirfd_dstn = open(argv[3], O_RDONLY);
	if(dirfd_dstn < 0)
	{
		perror("open destiny directory");
		exit(1);
	}

	int fd_dstn = openat(dirfd_dstn, argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd_dstn < 0)
	{
		perror("openat");
		exit(1);
	}

	if(close(dirfd_dstn))
 	{
	perror("close");
	exit(1);
 	}
	while((n = read(fd_src, buf, BUFSIZE)) > 0)
	{
	ssize_t t = 0;
	while (t < n)
	{
    ssize_t w = write(fd_dstn, buf + t, n - t);
    if (w < 0)
    {
        perror("write");
        exit(1);
    }

    t += w;
	}
	}
	if(n < 0)
	{
		perror("read");
		exit(1);
	}

	fdatasync(fd_dstn);


	if(close(fd_dstn))
	{
		perror("close");
		exit(1);
	}

    if(close(fd_src))
	{
		perror("close");
		exit(1);
	}

	return 0;
}

