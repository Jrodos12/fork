#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void filter(int fds_read, int n);

void filter(int fds_read,int  n)
{
	int primo;
	if (read(fds_read, &primo, sizeof(primo)) == 0)
	{
		close(fds_read);
		exit(1);
	}
	int fds_write[2];
	int r = pipe(fds_write);
	if (r < 0)
	{
		printf("Error creacion del pipe\n");
		exit(-1);
	}
	
	int wstatus;
	printf("primo %d\n", primo);
	int id = fork();

	if (id == 0)
	{
		close(fds_write[1]);
		close(fds_read);
		filter(fds_write[0], n);
		close(fds_write[0]);
		exit(1);

	}
	else
	{
		int num;
		close(fds_write[0]);
		while (read(fds_read,&num, sizeof(num)) > 0)
		{
			if (num % primo != 0)
			{
				if ( write(fds_write[1], &num, sizeof(num)) < 0)
				{
					printf("Error de escritura\n");
					exit(-1);
				}
			}
			
		}
		close(fds_write[1]);
		close(fds_read);
		wait(&wstatus);
		
	}
	
	return;
	
}

int main(int argc, char *argv[])
{
	if (argc < 1)
	{
		printf("Error de entrada no se ingreso numero\n");
		return-1;
	}
	
	int fds_write[2];
	int r = pipe(fds_write);
	if (r < 0)
	{
		printf("Error al crear pipe\n");
		exit(-1);
	}
	
	int n = atoi(argv[1]);
	int wstatus;
	int id = fork();

	if (id == 0)
	{
		close(fds_write[1]);
		filter(fds_write[0],n );
		close(fds_write[0]);
		exit(1);
	}
	else
	{
		close(fds_write[0]);
		for (int i = 2; i <= n; i++)
		{
			if ( write(fds_write[1], &i, sizeof(i)) < 0)
			{
				printf("Error de escritura\n");
				exit(-1);
			}
			
			
		}
		close(fds_write[1]);
		wait(&wstatus);
	}
	return 0;

}