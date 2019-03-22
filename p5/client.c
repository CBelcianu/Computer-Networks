//client send to server a string, server return no. spaces UDP
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(){
	int c;
	struct sockaddr_in server;
	c=socket(AF_INET,SOCK_DGRAM,0);
	if(c<0){
		printf("bai la socket\n"); return 1;
	}
	memset(&server,0,sizeof(server));
	server.sin_port=htons(1234);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	char s[100];
	uint32_t res;
	printf("introduceti un string:\n");
	fgets(s,100,stdin);
	sendto(c,&s,sizeof(s),0,(struct sockaddr *) &server, sizeof(server));
	recvfrom(c,&res,sizeof(res),0,(struct sockaddr *) &server, sizeof(server));
	printf("sirul are %d spatii\n",res);
	close(c);

}