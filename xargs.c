#ifndef NARGS
#define NARGS 4
#endif
#include <unistd.h>
#include <stdio.h>

void xargs(char* comand);
void xargs(char* comand)
{
	char *line = NULL;
	size_t len = 0;
	size_t n = 0;
	//printf("recibi %s\n", comand);
	int id  = fork();
	
	if (id == 0 )
	{
		
		char* strg[6] = {comand,0,0,0,0, NULL};
		for (int i = 0; i < NARGS; i++)
		{
			n = getline(&strg[i+1], &len,stdin);
			strg[i+1][n-1] = '\0'; 
		}
		execvp(comand, strg);
	}
	else
	{
		wait();
		xargs(comand);
	}
}

int
main(int argc, char *argv[])
{
	//printf("recibi %s\n", argv[1]);
    char *line = NULL;
    size_t len = 0;
	size_t n = 0;
	/*
	int id  = fork();
	
	if (id == 0 )
	{
		//xargs();
		//execvp(argv[1], argv+1);
	}
	else
	{
		wait();
		char* strg[6] = {argv[1],0,0,0,0, NULL};
		for (int i = 0; i < NARGS; i++)
		{
			n = getline(&strg[i+1], &len,stdin);
			strg[i+1][n-1] = '\0'; 
		}
		execvp(argv[1], strg);
	}
	*/
	xargs(argv[1]);
	return 0;
}
