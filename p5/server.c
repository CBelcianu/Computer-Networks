#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(){
	int c,s,l;
	struct sockaddr_in server,client;
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s<0){
		printf("bai la socket\n"); return 1;
	}
	memset(&server,0,sizeof(server));
	server.sin_port=htons(1234);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	if(bind(s,(struct sockaddr *) &server, sizeof(server))<0){
		printf("bai la bind\n"); return 1;
	}
	l=sizeof(client);
	memset(&client,0,sizeof(client));
	while(1){
		char sir[100];
		uint32_t res=0;
		recvfrom(s,&sir,sizeof(sir),MSG_WAITALL,(struct sockaddr *) &client,&l);
		for(int i=0;i<strlen(sir);i++)
			if(sir[i]==' ')res++;
		sendto(s,&res,sizeof(res),0,(struct sockaddr *) &client, l);
	}

}