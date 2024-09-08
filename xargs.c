#ifndef NARGS
#define NARGS 4
#endif
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int
main(int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		printf("Error cantidad de argumentos invalida");
		return -1;
	}
	int wstatus;
	size_t len = 0;
	int n = 0;
	int i = 0;
	int id = 0;
	char* strg[NARGS + 2]; // {COMANDO, 0, 0 ,0 ,0, null}
	strg[0] = argv[1];
	strg[NARGS+1] = NULL;
	while (n != EOF)
	{
		
		if (i == NARGS)
		{
			id = fork();
			if (id == 0)
			{

				execvp(argv[1], strg);			
			}
			else
			{
				wait(&wstatus);
				i = 0;
			}
			
		}
		n = getline(&strg[i+1], &len,stdin);
		strg[i+1][n-1] = '\0';
		i++;
	}
	id =  fork();
	if (id == 0)
	{
		strg[i] = NULL;
		execvp(argv[1], strg);
	}
	else
	{
		wait(&wstatus);
		for (size_t i = 1; i <= NARGS; i++)
		{
			free(strg[i]);
		}
		
	}
	return 0;
}
