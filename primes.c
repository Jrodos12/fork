#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void filter(int fds_read, int n);

void filter(int fds_read, int n)
{
	int primo;
	//read(fds_read[0], &primo, sizeof(primo));
	//printf("voy a filtrar\n");
	if (read(fds_read, &primo, sizeof(primo)) == 0)
	{
		exit(1);
	}
	
	printf("%d\n", primo);

	int fds_write[2];
	int r = pipe(fds_write);

	int id = fork();

	if (id == 0)
	{
		//child
		//write(fds_write[1],&primo, sizeof(primo));
		filter(fds_write[0], n);
		close(fds_write[1]);
	}
	else
	{
		int num;
		while (read(fds_read, &primo, sizeof(primo)) > 0)
		{
			if (num % primo != 0)
			{
				write(fds_write[1], &num, sizeof(num));
				close(fds_write[1]);
			}
			
		}
		
	}

	
	return;
}

main(int argc, char *argv[])
{
	int fds_write[2];
	int r = pipe(fds_write);
	int primo = 2 ;

	write(fds_write[1], &primo, sizeof(primo));
	close(fds_write[1]);
	filter(fds_write[0], atoi(argv[1]));
	return 0;
}