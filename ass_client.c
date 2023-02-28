// client code

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char * argv[])
{
	//variable declarition
	int sockfd,portno,n;
	struct sockaddr_in server_addr;
	char buf[1024];

	//check for appropriate no. of command line input

	if(argc<3)
	{
		printf("provide required command line...\n");
		exit(1);
	}

	portno=atoi(argv[2]);

	//socket is created
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	//check if socket is created properly
	if(sockfd<0)
	{
		printf("error in opening socket\n");
		exit(1);
	}
	else
	{
		printf("client socket is created\n");
	}

	bzero(&server_addr,sizeof(server_addr));

	//build the structure of server address
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(portno);
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);

	// now try to connect to the server

	if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		printf("connection failed\n");
		exit(1);
	}
	printf("connected to server\n");


	while(1)
	{
		//clear buffer
		bzero(buf,sizeof(buf));
		printf("to server:");
		int n=0;

		//now write some data to the server
		//	fgets(buf,1024,stdin);
		while((buf[n++]=getchar())!='\n');
		write(sockfd,buf,sizeof(buf));
		/*	if(n<0)
			{
			printf("error in writing\n");
			exit(1);
			}
			*/
		//now read back from the sever
		/*	bzero(buf,sizeof(buf));//clear buffer
			n=read(sockfd,buf,sizeof(buf));
			if(n<0)
			{
			printf("error in reading");
			exit(1);	
			}

		// print servers response

		/*		printf(" \nserver--->%s",buf);
		/*
		// detect end of conversation
		if(!strncmp("bye",buf,3))
		//	exit(1);

		break;*/
		if(recv(sockfd,buf,1024,0)<0)
		{
			printf("[-]error receving data\n");
		}	
		else
		{
			printf("server :\t%s\n",buf);
		}
//		close(sockfd);
//		return 0;

	}

}
