#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(){
	int c;
	struct sockaddr_in server;
	
	c=socket(AF_INET,SOCK_STREAM,0);
	if(c<0){
		printf("err la crearea sock client\n");
		return 1;
	}
	
	memset(&server, 0 ,sizeof(server));
	server.sin_port=htons(1234);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	if( connect(c, (struct sockaddr *) &server, sizeof(server))<0 ){
		printf("err la conn la server\n");
		return 1;
	}

	char s1[100],s2[100];
	printf("dati un sir\n");
	fgets(s1,100,stdin);
	send(c,&s1,sizeof(s1),0);
	recv(c,&s2,sizeof(s2),0);
	printf("ogindit este %s: ",s2);
	close(c);

}