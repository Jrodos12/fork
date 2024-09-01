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
	if (primo == 0)
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
		for (int i = 1; i <= 10; i++)
		{
			printf("%d \n",primo*i);
		}
		printf("\n");
		
	}

	/*
	int num = 0;
	int prime = 0;
	read(fds_read[0], &prime, sizeof(prime));
	printf("%d \n", prime);
	if (prime == n){ exit(1);}
	

	int fds_write[2];
	int r = pipe(fds_write);
	int  i = fork();
	if (i == 0)
	{
		prime ++;
		write(fds_write[1], &(prime),sizeof(prime) );
		filter(fds_write,n);
		
	}
	if (i > 0)
	{
		while (read(fds_read[0], &prime, sizeof(prime)) > 0)
		{
			read(fds_read[0], &num, sizeof(n));
			close(fds_read[1]);
			if (n % prime != 0)
			{
				write(fds_write[1], &prime, sizeof(prime));
				close(fds_write[0]);
				wait();
			}
		}
		
	}
	
	
	exit(1);
	*/
}
main(int argc, char *argv[])
{
	int fds_write[2];
	int r = pipe(fds_write);
	int primo = atoi(argv[1]) ;

	write(fds_write[1], &primo, sizeof(primo));

	filter(fds_write, atoi(argv[1]) );
	return 0;
}