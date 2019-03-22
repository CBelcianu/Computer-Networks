//the client send to the server 2 arrays of numbers and recieves an array of the common numbers
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
		printf("bai la socket\n"); return 1;
	}
	memset(&server,0,sizeof(server));
	server.sin_port=htons(1234);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(c,(struct sockaddr *) &server,sizeof(server))<0){
		printf("bai la conectarea la server\n"); return 1;
	}
	uint32_t a1[100],a2[100],a3[100],n1,n2,n3;
	printf("n1 ="); scanf("%d",&n1);
	for(int i=0;i<n1;i++){
		printf("a1[%d]= "); scanf("%d",&a1[i]);
	}
	printf("n2 ="); scanf("%d",&n2);
	for(int i=0;i<n2;i++){
		printf("a2[%d]= "); scanf("%d",&a2[i]);
	}
	send(c,&n1,sizeof(n1),0);
	send(c,&a1,sizeof(a1),0);
	send(c,&n2,sizeof(n2),0);
	send(c,&a2,sizeof(a2),0);
	recv(c,&n3,sizeof(n3),0);
	recv(c,&a3,sizeof(a3),0);
	printf("the common numbers are: ");
	for(int i=0;i<n3;i++)
		printf("%d ",a3[i]);
	close(c);

}