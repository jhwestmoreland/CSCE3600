#include <sys/stat.h>
#include <stdio.h>
#include <pthread.h> //for threading
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void interactive();
void batch(char *filename);
void execute(char *command);
