#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

void	my_handler(int num)
{
	printf("we are in my handler:\n" \
			"the int arg is: %d\n", num);
	printf("we are going to wait 3 secondes...\n");
	sleep(3);
	//note since it is a SIGINT, it will print 2!! yes!
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	signal(SIGINT, &my_handler);
	signal(SIGQUIT, &my_handler);
	//this works for both signals. one prints 3, the other prints 2 --> OK
	while (1)
	{
		printf("this process will do that indefinitely...\n");
		sleep(1);
	}
	return (0);
}
