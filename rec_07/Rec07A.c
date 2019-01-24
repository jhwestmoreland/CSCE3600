/*
 * usage: ./a.out text_pattern input_file output_file
 * Executes the command "grep text_pattern < input_file > output_file"
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int ifp, ofp;

	if (argc == 4)
	{
		// grep on text_pattern
  		char *grep_args[] = {"grep", argv[1], NULL};

		// open input and output files
		ifp = open(argv[2], O_RDONLY);
		ofp = open(argv[3], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

		// replace standard input with input file
		dup2(ifp, 0);

		// replace standard output with output file
		dup2(ofp, 1);

		// close 2 unused file descriptors
		close(ifp);
		close(ofp);

		// execute grep
		execvp("grep", grep_args);
	}
	else
	{
		printf("usage: %s text_pattern input_file output_file\n", argv[0]);
	}
}