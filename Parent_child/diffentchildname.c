#include <stdio.h>	// For perror().
#include <unistd.h>	// For fork().
#include <stdlib.h>	//	For atoi(), exit().
#include <string.h>	// For strlen().

#define CHILD_N 4
#define BUFFER_SZ 100

int main(int argc, char *argv[]){
	pid_t CID;	// Child process's ID
	int i, exeSt;
	char *msg = "Usage: ./differentNameChildren [<a> <b>]\n";

	/* Executable(i.e., exe) files of child processes. */
	char exeFile[CHILD_N][BUFFER_SZ] = {
		"/home/warrior/clone repo/System-Progamming-Lab/Mam/addition", 
		"/home/warrior/clone repo/System-Progamming-Lab/Mam/subtraction",
		"/home/warrior/clone repo/System-Progamming-Lab/Mam/multiplication",
		"/home/warrior/clone repo/System-Progamming-Lab/Mam/division"	
	};

	for(i = 0; i < CHILD_N; i++){
		CID = fork();
		if(CID == -1){
			perror("Error during fork()");
			exit(EXIT_FAILURE);	// Unsuccessful termination
		}

		if(CID == 0){
			switch(argc){
				case 1:
					exeSt = execlp(exeFile[i], exeFile[i], NULL);
				break;
				case 2:
					exeSt = execlp(exeFile[i], exeFile[i], argv[1], NULL);
				break;
				case 3:
					exeSt = execlp(exeFile[i], exeFile[i], argv[1], argv[2], NULL);
				break;
				default:
					write(1, msg, strlen(msg) + 1);
					exit(EXIT_FAILURE); // Unsuccessful termination
				break;
			}

			if(exeSt == -1){
				perror("Error during execlp()");
				exit(EXIT_FAILURE);	// Unsuccessful termination
			}
		}
	}
	
	/* 
		To keep parent process alive as long as child
		processes are alive. If parent process dies before
		child processes, they become orphan process. Process
		'systemd' / 'upstart' becomes parent of orphan processes. 
	*/
	while(1);

	exit(EXIT_SUCCESS);	//Successful Termination
}
