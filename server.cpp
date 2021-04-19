#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>  //close(server_fd)
#include <unistd.h>      // memset
#include <arpa/inet.h>   // inet_ntoa
#include <thread>
#include <string.h>
using namespace std;
void workthread(int client_fd)
{
	if(client_fd != -1)
	{
		while(true)
		{
			char readbuff[1024] = {0};
			int readlen = recv(client_fd,readbuff,sizeof(readbuff),0);
			std::cout<<"rec:"<<readbuff<<std::endl;
			send(client_fd,readbuff,readlen,0);
		}
	}
}

int main(int argc,char **argv)
{
  	int i;
	for(i=0;i<argc;i++)
	{
		printf("parameter%d is %s.\n",i,argv[i]);
	}
	if(argc!=2)
	{
		std::cout<<"application only accepts one parameter"<<std::endl;
		return -1;
	}
	std::cout<<"input par:"<<argv[1]<<","<<std::endl;
	char* appname = argv[0];
	int port = atoi(argv[1]);

        int server_fd = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(sockaddr_in));
	serveraddr.sin_port= htons(port);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
        
	if(0 != bind(server_fd,(sockaddr*)&serveraddr,sizeof(sockaddr_in)))
	{
		cout<<"bind error"<<endl;
		return -1;
	}
	
	if(0!=listen(server_fd,5))
	{
 		cout<<"listen error"<<endl;
		return -1;
	}
	while(true)
	{
		sockaddr_in client_addr;
		socklen_t client_addrlen;
		int client_fd = accept(server_fd,(sockaddr*)&client_addr,&client_addrlen);
		std::cout<<"client ip:"<<inet_ntoa(client_addr.sin_addr)<<std::endl;
		std::cout<<"client port:"<<client_addr.sin_port<<std::endl;
	        char sendBuff[1024] = {0};
		char recvBuff[1024] = {0};
		const char* src = "Server=====";
		strncpy(sendBuff,src,1024-1);
 		write(client_fd,sendBuff,strlen(sendBuff));
		//std::thread thread(workthread,client_fd);
		//thread.detach();
		read(client_fd,recvBuff,sizeof(recvBuff)-1);
		printf("\n recv:%s\n",recvBuff);
	}
	close(server_fd);
	return 0;
}
