#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFSIZE 4096

int
main(int argc, char *argv[])
{
	ssize_t n;
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

	int dirfd_dstn = open(argv[3], O_RDONLY);
	if(dirfd_dstn < 0)
	{
		perror("open destiny directory");
		exit(1);
	}

	int fd_dstn = openat(dirfd_dstn, argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	while((n = read(fd_src, buf, BUFSIZE)) > 0)
	{
		if(write(fd_dstn, buf, n) != n)
		{
			perror("write");
			exit(1);
		}
	}
		if(n < 0)
		{
			perror("read");
			exit(1);
		}


	close(fd_dstn);
	close(dirfd_dstn);
	close(fd_src);
	close(dirfd_src);

	return 0;
}

