#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	pid_t childPID;

	childPID = fork();

	if(childPID < 0)
	{
		printf("child create failed\n");
	}
	else if(childPID == 0)
	{
		while(1)
		{

			printf("I am child process.My pid is %d\n",getpid());
		}


		
	}
	else
	{
		printf("I am parent process.My pid is %d\n",getpid());

		//return 0;
	}


	return 0;
}