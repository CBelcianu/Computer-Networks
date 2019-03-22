#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(){
	int c,s,l;
	struct sockaddr_in server, client;

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0){
		printf("err la socket server\n");
		return 1;
	}
	
	memset(&server, 0 ,sizeof(server));
	server.sin_port=htons(1234);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;

	if( bind(s, (struct sockaddr *) &server, sizeof(server))<0 ){
		printf("err la bind\n");
		return 1;
	}

	listen(s, 5);
	l= sizeof(client);
	memset(&client, 0, sizeof(client));
	
	while(1){
		c=accept(s, (struct sockaddr *) &client, &l);
		printf("s-a conectat un client\n");

		char s1[100],s2[100];
		recv(c,&s1,sizeof(s1),MSG_WAITALL);
		for(int i=0;i<strlen(s1);i++)
			s2[i]=s1[strlen(s1)-1-i];
		s2[strlen(s1)]='\0';
		send(c,&s2,sizeof(s2),0);
		close(c);
	}

}