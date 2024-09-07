#ifndef NARGS
#define NARGS 4
#endif
#include <unistd.h>
#include <stdio.h>

void xargs();
void xargs()
{

	FILE *stream;
    char *line = NULL;
    size_t len = 0;
	int id  = fork();
	if (id == 0 )
	{
		// estoy en el hijo
		xargs();
	}
}

int
main(int argc, char *argv[])
{
	printf("recibi %s\n", argv[1]);
    char *line = NULL;
    size_t len = 0;
	int id  = fork();
	
	if (id == 0 )
	{
		// estoy en el hijo
		//xargs();
		execvp(argv[1], argv+1);
	}
	else
	{
		wait();
		while(getline(&line, &len,stdin) != -1)
		{
			printf("hola %s", line);
		}
	}
	
	
	

	
	
	return 0;
}
