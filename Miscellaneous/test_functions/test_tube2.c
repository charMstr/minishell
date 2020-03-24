#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void	cant_write_handler(int num)
{
	printf("here the signal number handled: %d\n", num);
	exit(EXIT_FAILURE);
}

void fils(int d_ecriture)
{
	char msg_fils[] = "some nous rentres dans le fils?\n";

	write(1, msg_fils, sizeof(msg_fils));
	char message[] = "abcdefghijklmnopqrstuvwxyz";
	int no_ecrit;

	if ((no_ecrit = write(d_ecriture, message, sizeof(message))) == -1)
	{
		perror("it was impossible to write");
		exit(EXIT_FAILURE);
	}
	printf("Je suis le fils et j'ai ecrit %d characters sur le fd %d\n", no_ecrit, d_ecriture);
	exit(EXIT_SUCCESS);
}

void	pere(int d_lecture)
{
	char tampon[10 + 1];
	int no_lu;

	while ((no_lu = read(d_lecture, tampon, 10)) > 0)
	{
		printf("Je suis le pere et j'ai lue %d characteres sur le fd %d\n", no_lu, d_lecture);
		tampon[10] = '\0';
		printf("jai lue: [%s]\n", tampon);
	}
	if (no_lu == -1)
	{
		printf("we could not Read in the pere() func.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	int p[2];
	int res_fork;
	int res_wait;

	if (pipe(p) == -1)
	{
		perror("pipe function could not open a pipe...");
		exit(EXIT_FAILURE);
	}
	if ((res_fork = fork()) == -1)
	{
		perror("faillure in fork function");
		exit(EXIT_FAILURE);
	}
	signal(SIGPIPE, cant_write_handler);
	if (res_fork) //we are in the dad, the reader...
	{
		close(p[1]);
		close(p[0]);
		//waitpid(res_fork, &res_wait, WUNTRACED);
		/*
	experience: on comment le wait, on met un sleep chez le fils, et on
				n'appel pas le pere, comme ca il ny a pas de read, le pere est
				fini bien avant le fils...
	resultat: si on n'attend pas le fils et que le pere fini completent de
	s'exectuter, on a le prompt qui se reaffiche (normale, le fils du shell,
	a savoir le pere ici est termine...) Apres ca: le fils vient tout
	degueulasser en ecrivant apres un sleep(1); ...
	nb: cela ne se produirait pas si le read attendait sagement...

	DONC: cela met en evidence la necessite du wait, au cas ou le processus qui
	read par exemple est arrete/kille ou autre.
*/

		printf("le pid a kill est le: %d\n", getpid());
		waitpid(res_fork, &res_wait, WUNTRACED);
/*
	context: le waitpid est reactive.
	autre test effectue: si je kill le pere grace a son getpid() pendant un
	sleep(15) cote fils, et bien  le fils tourne toujours en tache de fond.

	DONC:c'est de ma responsabilite quand je fork de ne pas laisser des process
	orphelins...
*/
		//pere(p[0]);
	}
	else //we are in the son: the writer
	{
		close(p[0]);
		printf("le pid fils a kill est le: %d\n", getpid());
		sleep(15);
		fils(p[1]);
	}
	close(p[0]); //is this usefull?
	close(p[1]);
	return (0);
}
