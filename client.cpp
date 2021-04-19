#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define SEND_BUF_SIZE 1024

int main(int argc,char *argv[])
{
	if(argc !=2)
	{
		printf("\n Usage:%s < ip of server> \n",argv[0]);
		return -1;
	}

	char recvBUff[1024] = {0};
	int sockfd = 0,n = 0;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("\n Error :COuld not create socket \n");
		return 1;
	}
	struct sockaddr_in serv_addr;
	memset(&serv_addr,'0',sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	if(inet_pton(AF_INET,argv[1],&serv_addr.sin_addr) <= 0)
	{
		printf("\n inet_pton error occured\n");
		return 1;
	}

 	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("\n Error:Connect Failed \n");
		return 1;
	}
	char sendBuff[SEND_BUF_SIZE] = {0};
	char recvBuff[SEND_BUF_SIZE] = {0};
	const char* src = "Client ====";
	strncpy(sendBuff,src,SEND_BUF_SIZE -1);	
	
	write(sockfd,sendBuff,strlen(sendBuff));
	while(1)
	{
		if((n = read(sockfd,recvBuff,sizeof(recvBuff)-1))>0)
		{
			printf("%d\n",n);
			recvBuff[n] = 0;
			printf("%s\n",recvBuff);
		}
	}
	if(n<0)
	{
		printf("\n Read error \n");
	}

	return 0;
}

