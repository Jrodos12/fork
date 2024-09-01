#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void filter(int* fds_read, int n);

void filter(int* fds_read, int n)
{
	int fds_write[2];
	int r = pipe(fds_write);
	int primo = 0;
	read(fds_read[0], &primo, sizeof(primo));
	int id = fork();
	if (primo == 1)
	{
		close(fds_read[0]);
		close(fds_write[1]);
		close(fds_write[0]);
		exit(1);
	}
	
	if (id == 0)
	{
		
		int next = primo - 1;
		write(fds_write[1], &next, sizeof(next));
		close(fds_read[1]);
		filter(fds_write, n);
		close(fds_write[0]);

	}
	else
	{
		wait();
		for (int i = 1; primo*i <= n; i++)
		{
			printf("%d \n",primo*i);
		}
		printf("\n");
		
	}
}

void filtro(int* fds_read, int n);

void filtro(int* fds_read, int n)
{
	int fds_write[2];
	int r = pipe(fds_write);
	int primo = 0;
	read(fds_read[0], &primo, sizeof(primo));
	int id = fork();
	if (id == 0)
	{
		
		filtro(fds_write, n);
		
		exit(1);
	}
	else
	{
		read(fds_read[0], &primo,sizeof(primo));
		printf("%d \n",primo);
		while (read(fds_read[0], &primo,sizeof(primo)) != 0)
		{
			int num;
			read(fds_read[0], &num,sizeof(num));
			if (num % primo != 0)
			{
				write(fds_write[1], &num, sizeof(num));
			}
			
		}
		

	}

	
return;
}

main(int argc, char *argv[])
{
	int fds_write[2];
	int r = pipe(fds_write);
	int primo = atoi(argv[1]) ;

	write(fds_write[1], &primo, sizeof(primo));

	filtro(fds_write, atoi(argv[1]) );
	return 0;
}