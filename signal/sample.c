#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signalHandler(int sig);

int main()
{
    signal(SIGTERM, signalHandler);
    
    int i=0;

    printf("pid=%d\n\n\n",getpid());
    while(1)
    {
        printf("%d\n",i);
        i++;
        sleep(3);
    }
    return 0;
}

void signalHandler(int sig)
{

    printf("\t\tMy custom signal sent\n");
    
}