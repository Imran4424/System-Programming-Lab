#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>			// For close().  
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>       // for boolean type variables
#include <pthread.h>       // for multi thread operation
#include <string.h>        // for strcmp and strlen
#include <stdlib.h>        // for exit system call


//global variable
int good_bye_count = 0;
int client_socket;
bool connection_status = false;
bool file_share_mode = false;
char file_share[] = "share file";



void *sender()
{
    
    //declaring the variables

	char messenger_two_message[1024];
	

	while(good_bye_count != 2)
	{
        //printf("sender in while\n");

        input:

		scanf ("%[^\n]%*c", messenger_two_message);  ///send good bye to finish the conversation

		//scanf("%[^\n]s",server_message);

        if(strcmp(messenger_two_message,"read my file") == 0)
        {
            FILE *ptr;

            ptr = fopen("read_me.txt","r");
            
            if(ptr == NULL)
            {
                printf("Error\n");

                return 0;
            }

            char contents[1024];

            fscanf(ptr,"%[^\n]s",contents); // to read file contents

            printf("my file contents:\n%s\n",contents);

            goto input;
        }

        if(strcmp(messenger_two_message,"read received file") == 0)
        {
            FILE *ptr;

            ptr = fopen("received_file.txt","r");
            
            if(ptr == NULL)
            {
                printf("Error\n");

                return 0;
            }

            char contents[1024];

            fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

            printf("my file contents:\n%s\n",contents);

            goto input;
        }
				
	   	int sending = send(client_socket,&messenger_two_message,sizeof(messenger_two_message),0);

                
        if(sending < 0)
        {
            perror("In server sending");
        }

        if(strcmp(messenger_two_message,file_share) == 0)
        {
            file_share_mode = true;
            
        }
		
        if(strcmp(messenger_two_message,"good bye") == 0)
        {
                good_bye_count++;
        }
	}


}


void *received()
{
    //printf("receiver\n");

	// STEP-1: socket()
    // 1.1. Create a socket.
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 1.2. Specify an address for the above socket.
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(12000);
    //inet_pton(AF_INET, "192.168.1.36", &(server_address.sin_addr)); //to connect other pc 
    server_address.sin_addr.s_addr = INADDR_ANY; // Local IP address

    // STEP-2: connect()
    // 2.1. Connect to the remote socket
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *) &server_address;



    int server_socket;

    line:

    server_socket = connect(client_socket, sockaddr_ptr, addr_len);

    if(server_socket == 0)
    {
    	connection_status = true;
	    printf("connection stablish\n");
    }


    //printf("%d\n",server_socket );


    
    // STEP-3: recv()
    // 3.1. Receive data from the server

    //declaring the variables

	char messenger_one_response[1024];


	while(good_bye_count != 2)
	{
		if(!connection_status)
		{
			goto line;
		}

        int receiving = recv(client_socket, &messenger_one_response, sizeof(messenger_one_response), 0);



        if(receiving < 0)
        {
            printf("received is failed\n");
        }
        else if(!file_share_mode)
        {

            // 3.2. Check sever's response.
            printf("Imran: %s\n", messenger_one_response);
        }

        if(file_share_mode)
        {
            //char contents[1024];

            //printf("Hi I am here\n");

            char msg[] = "File received successful";

            FILE *ptr;

            ptr = fopen("received_file.txt","w");

            fprintf(ptr, "%s\n",messenger_one_response ); // to write on file

            printf("%s\n",msg );

            int sending = send(client_socket,&msg,strlen(msg)+1,0);

            
            if(sending < 0)
            {
                perror("In server sending");
            }

            

            fclose(ptr);

            file_share_mode = false;
        }

		
        if(strcmp(messenger_one_response,file_share) == 0)
        {
            FILE *ptr;

            ptr = fopen("cfile.txt","r");
            
            if(ptr == NULL)
            {
                printf("Error\n");

                return 0;
            }

            char contents[1024];

            fscanf(ptr,"%[^\n]s",contents); // to read file contents

            int sending = send(client_socket,&contents,sizeof(contents),0);
                
            if(sending < 0)
            {
                printf("file send failed\n");
            }
            else
            {
                printf("File send successful\n");
            }

            fclose(ptr);
        } 


        if(strcmp(messenger_one_response,"good bye") == 0)
	    {
	        good_bye_count++;
	        
	    }
	}



	// STEP-4: close()
    // 4.1. Close the socket
    close(client_socket);
}



int main()
{
	pthread_t TID[3];
    int tdstatus;


    
	tdstatus = pthread_create(&TID[0],NULL,sender,NULL);
	
	if(tdstatus != 0)
	{
		perror("Error during pthread_create()");
		//exit(EXIT_FAILURE); // Equivalent of "return 1;".

        return 1;
	}


	tdstatus = pthread_create(&TID[1],NULL,received,NULL);
	
	if(tdstatus != 0)
	{
		perror("Error during pthread_create()");
		//exit(EXIT_FAILURE); // Equivalent of "return 1;".

        return 1;
	}

    

    while(1)
    {
        if(good_bye_count == 2)
        {
            break;
        }
    }

	return 0;
}
