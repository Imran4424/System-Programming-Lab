#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

const int m_size = 3000;

int main(int argc, char const *argv[])
{
	int fd ,fd2;

	sem_t *sem;

	sem = sem_open("/semaphore_brotherhood", O_CREAT, 0766, 1);

	char *pipeName = "mknod_brotherhood";

	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(pipeName,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions

	char dante_to_vergil[m_size];
	char dante_received[m_size];

	printf("vergil is waiting for your reply\n");

	scanf("%[^\n]",dante_to_vergil);


	fd = open(pipeName,O_WRONLY);
	write(fd,dante_to_vergil,strlen(dante_to_vergil)+1);
	close(fd);

	fd2 = open(pipeName,O_RDONLY);
	read(fd2,dante_received,m_size);
	close(fd2);

	printf("vergil: %s\n",dante_received );


	sem_close(sem);

	return 0;
}