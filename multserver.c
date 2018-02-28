#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <sys/time.h>
#include <errno.h>
#include <netdb.h> 
#include <fcntl.h> 


#define max_clients 5
int main(int argc, char *argv[])
{
	// declaration variables 
	int listen_socket, addrlen, new_socket, bufsize = 1025, reuse=1,
		 activity, i, j, errno;
        short port=1234;
	int *client_socket;
	struct sockaddr_in address;
	char *message,*buffer,*buffer2;
        fd_set readfds;
         message= (char*) malloc (26 * sizeof(char));
		 buffer = (char*) malloc(bufsize * sizeof(char)); 
 		 buffer2 = (char*) malloc(bufsize * sizeof(char)); 
		
			
	client_socket = (int *) malloc (max_clients * sizeof(int));

        for (j = 0; j < max_clients; j++) client_socket[j]=0; //initialisation du tableau des socket à 0

	if (argc > 1)
		port=atoi( argv[1]);
	  
	// message pour les  participants
	strcpy(message, "Welcome to the Chat.\n\r" );
	
	
	if ((listen_socket = socket(AF_INET, SOCK_STREAM,0)) < 0) 
	{	perror("Create master_socket");exit(EXIT_FAILURE); }
	
	
	if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int))<0) 
		{perror("setsockopt");exit(EXIT_FAILURE);}
	
	/// Bind the socket to a an Address/Port
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
		

    if(bind (listen_socket, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {   perror("\nBind error %d"); exit(1); }

    
	
	
	if (listen(listen_socket, max_clients)<0) 
		{perror("listen"); exit(1);}
	
	while (1==1) 
	{
		FD_ZERO(&readfds);
		/// ajouter le socket d'écoute à l'ensemble readfs 
		FD_SET(listen_socket, &readfds);
		
		for (i = 0; i < max_clients; i++) 
		{
			if (client_socket[i] > 0) 
			{	
               /// ajouter le socket client à l'ensemble readfs
				FD_SET(client_socket[i], &readfds);
			}
		}
		
		
		activity=select(max_clients +3, &readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno!=EINTR)) 
		{perror("select: !!"); exit(1);}
		
		
		if (FD_ISSET(listen_socket, &readfds))  // si nouveau client -> accept
		{	
			addrlen=sizeof(address);
			if ((new_socket = accept(listen_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
			{
				
				perror("accept");exit(1);
			}
			 
			printf("New socket -Valeur descripteur = : %d\n",new_socket);

		
			if (write(new_socket, message, strlen(message)) != strlen(message)) 
				perror("envoi ");
			
			puts("message envoyer avec succes au client \n");
			/// ajouter socket à la liste des sockets
			for (i=0; i < max_clients; i++) 
			{
				if (client_socket[i] == 0) 
				{
					client_socket[i] = new_socket;
					printf("Ajout du client Num %d\n", i);
					i = max_clients;
				}
			}
		}
		for (i=0; i < max_clients; i++) 
		{
			if (FD_ISSET(client_socket[i], &readfds)) 
			{
				if ((activity = read(client_socket[i], buffer, 1024)) < 0) 
				{
					close(client_socket[i]);
					client_socket[i] = 0;
				} else 
				{
					/// ajouter 0 en fin de chaine
					buffer[activity] = 0;
                                        sprintf(buffer2,"%d : %s",i,buffer); 
					for (j = 0; j < max_clients; j++) 
					{
					
						if (j != i && client_socket[j]!=0)
							write(client_socket[j], buffer2, strlen(buffer2));

					}
				}
			}
		}
		
	}
	
	/// close  sockets 
	for (i=0; i < max_clients; i++) 
		close(client_socket[i]);
		
	close(listen_socket);
	
	return 0;
}
