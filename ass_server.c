// server code

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int cnt=0;

int main(int argc,char* argv[])
{
	//variable declarition
	int sockfd,newsockfd,portno,n;
	struct sockaddr_in server_addr,client_addr;
	char buf[1024];
	socklen_t addr_size;
	pid_t child_pid;
	int i =0;

	//check for appropriate no. of command line input

	if(argc<2)
	{
		printf("provide required command line...\n");
		exit(1);
	}

	portno=atoi(argv[1]);
	//created the socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	//check if socket is created properly
	if(sockfd<0)
	{
		printf("error in opening socket\n");
		exit(1);
	}
	printf("server socket is created\n");

	memset(&server_addr,'\0',sizeof(server_addr));

	//build the structure of server address
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(portno);

	//bind the socket to the address and port no specified in structure

	if(bind(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr))<0)
	{
		printf("error in binding address\n");
	}

	//listen to any incoming client

	listen(sockfd,10);
	addr_size=sizeof(client_addr);


	while(1)
	{

		newsockfd=accept(sockfd,(struct sockaddr *)&client_addr,&addr_size);

		cnt++;

		//check if yhe client socket is created properly

		if(newsockfd<0)
		{
			printf("error in accepying in request\n");
			exit(1);
		}
		printf("connection accepted from %s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

		if((child_pid=fork())==0)
		{
			//		close(sockfd);
			while(1)
			{


				// clear buffer
				bzero(buf,sizeof(buf));
				
				//now read some data from the client
				read(newsockfd,buf,sizeof(buf));

				for(int i=0;buf[i]!='\0';i++)
				{
					if (buf[i] >= 'a' && buf[i] <= 'z')
					{
						buf[i]-=32;
					}
					else if(buf[i] >= 'A' && buf[i] <= 'Z')
					{
						buf[i]+=32;
					}
				}

				printf("from client %d:%s \tto client:",cnt,buf);



				bzero(buf,sizeof(buf));

				//now write some data to the client

				int n=0;
				while((buf[n++]=getchar())!='\n');
				write(newsockfd,buf,sizeof(buf));


						
			}
		}

	}
	// close the files
		close(newsockfd);
	//	close(sockfd);
	return 0;

}


