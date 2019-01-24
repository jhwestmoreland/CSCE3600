#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int fd,i,nbytes;
	char *str = malloc(sizeof(char));

	fd = open("labexam2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

	dup2(fd,1);
	close(fd);

	for(i = 1; i < 6; i++)
	{
		sprintf(str, "%d", i);
		nbytes = sizeof(char);
		write(nbytes, str, nbytes);
	}
	pid_t pid = fork();
	if(pid == 0)//child
	{
		str = malloc(4* sizeof(char));
		sprintf(str, "%d", 6789);
		execlp("echo", "echo", str ,(char*)0);
		perror("execlp");
	}
	else//parent
	{
		waitpid(pid, NULL, 0);
	}
	return 0;
}
