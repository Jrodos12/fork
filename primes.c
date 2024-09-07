#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


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
				write(fds_write[1], &num, sizeof(num));
			}
			
		}
		close(fds_write[1]);
		close(fds_read);
		wait();
		
	}
	
	return;
	
}

int main(int argc, char *argv[])
{
	int fds_write[2];
	int r = pipe(fds_write);
	int n = atoi(argv[1]);
	int primo = 2 ;

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
			write(fds_write[1], &i, sizeof(i));
			
		}
		close(fds_write[1]);
		wait();
	}
	return 0;

}