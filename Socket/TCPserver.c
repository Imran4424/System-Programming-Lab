/* ======================================================================
	Socket Programming-1
   This progam is for creating a server socket. The server socket
       (a) is created with a socket() call
       (b) is bound with an IP address and Port
       (c) listens for connections with a listen() call 
       (d) accepts a connection with a accept() call
       (e) sends data with send() call and 
       (f) finshes its life with a close() call.
	---------------------------------------------------------------------- 
    *** htons(Port_No) is for converting HBO to NBO where
        ----> HBO: Host-Byte-Order
        ----> NBO: Network-Byte-Order
        Byte Order: Big Indian & Little Indian
	---------------------------------------------------------------------- 
    Necessary System Calls:
       1. socket(domain, type, protocol)
       2. bind()
       3. listen() 
       4. send()
       5. recv()
       6. close()         
   ---------------------------------------------------------------------- 
    Sangeeta Biswas
    Assistant Professor,
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
   ---------------------------------------------------------------------- 
    29/8/2017
	======================================================================
*/

#include <sys/socket.h> 	
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>



int main() {
    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the above socket to the specified IP and port
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *)&server_address;
    bind(server_socket, sockaddr_ptr, addr_len);
        
    // Listen
    listen(server_socket, 5);

    // Accept
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send message to the client
    

	//declaring the variables

	char server_message[256];
	char client_response[256];
	bool write = true;
    

	
	//just creating a infinite loop

	while(1)
	{
		if(write)
		{
			printf("client waiting for your response\n");

			scanf ("%[^\n]%*c", server_message);

			//scanf("%[^\n]s",server_message);
			
    	   	int sending = send(client_socket, server_message, sizeof(server_message), 0);
			
			if(sending < 0)
			{
				perror("In server sending");
			}

			write = false;
		}
		else
		{
			

			int receiving = recv(client_socket,client_response,sizeof(client_response),0);

			if(receiving < 0)
			{
				perror("In server receiving");
			}

			printf("client: %s\n", client_response);

			write = true;		

		}

	}


    // Close socket
    close(server_socket);

}
