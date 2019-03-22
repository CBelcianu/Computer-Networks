#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(){
	int c,s,l;
	struct sockaddr_in server,client;
	s=socket(AF_INET,SOCK_STREAM,0);
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
	listen(s,5);
	l=sizeof(client);
	memset(&client,0,sizeof(client));
	while(1){
		c=accept(s,(struct sockaddr *) &client, &l);
		printf("s-a conectat un popandau\n");
		uint32_t a1[100],a2[100],a3[100],n1,n2,n3;
		recv(c,&n1,sizeof(n1),0);
		recv(c,&a1,sizeof(a1),0);
		recv(c,&n2,sizeof(n2),0);
		recv(c,&a2,sizeof(a2),0);
		n3=0;
		for(int i=0;i<n1;i++)
			for(int j=0;j<n2;j++)
				if(a1[i]==a2[j]) a3[n3++]=a1[i];
		send(c,&n3,sizeof(n3),0);
		send(c,&a3,sizeof(a3),0);
	}

}