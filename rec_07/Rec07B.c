/*
 * usage: ./a.out input_file text_pattern
 * Executes the command "cat input_file | grep text_pattern | cut -b 1-10".
 * Note that only minimal error checking is done for simplicy and shortness of code
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int status;
	int i;

	if (argc == 3)
	{
		// arguments for commands
		char *cat_args[]  = {"cat", argv[1], NULL};
		char *grep_args[] = {"grep", argv[2], NULL};
		char *cut_args[]  = {"cut", "-b", "1-10", NULL};

		// make 2 pipes (cat to grep and grep to cut); each has 2 fds
		int fd1[2], fd2[2];

		// fd1[0] = read  end of cat->grep pipe (read by grep)
		// fd1[1] = write end of cat->grep pipe (written by cat)
		pipe(fd1);

		// fd2[0] = read  end of grep->cut pipe (read by cut)
		// fd2[1] = write end of grep->cut pipe (written by grep)
		pipe(fd2);


		// fork the first child (to execute cat)
		if (fork() == 0)
		{
			// replace cat's stdout with write part of 1st pipe
			dup2(fd1[1],1);

			// close all pipes (very important!); end we're using was safely copied
			close(fd1[0]);
			close(fd1[1]);
                	close(fd2[0]);
                	close(fd2[1]);


      			execvp(*cat_args, cat_args);
 	 	}
  		else // parent (assume no error)
    		{
      			// fork second child (to execute grep)
      			if (fork() == 0)
			{
	  			// replace grep's stdin with read end of 1st pipe
				dup2(fd1[0], 0);

	  			// replace grep's stdout with write end of 2nd pipe
				dup2(fd2[1], 1);

	  			// close all ends of pipes
				close(fd1[0]);
                		close(fd1[1]);
                		close(fd2[0]);
                		close(fd2[1]);

				execvp(*grep_args, grep_args);
			}
      			else // parent (assume no error)
			{
	  			// fork third child (to execute cut)
	  			if (fork() == 0)
	    			{
	      				// replace cut's stdin with input read of 2nd pipe
					dup2(fd2[0], 0);

	      				// close all ends of pipes
					close(fd1[0]);
                			close(fd1[1]);
                			close(fd2[0]);
                			close(fd2[1]);

	      				execvp(*cut_args, cut_args);
	    			}
			}
    		}

  		// only the parent gets here and waits for 3 children to finish
  		close(fd1[0]);
  		close(fd1[1]);
  		close(fd2[0]);
  		close(fd2[1]);

  		for (i = 0; i < 3; i++)
		{
    			wait(&status);
		}
	}
	else
	{
		printf("usage: %s input_file text_pattern\n", argv[0]);
	}

	return 0;
}
