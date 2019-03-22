#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {

	int c;
	struct sockaddr_in server;

	c = socket(AF_INET, SOCK_STREAM, 0);

	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server\n");
		return 1;
	}
	char message[100],all[1000];
	while(1){
		printf("introduceti unn mesaj\n");
		if(message[0]=='-' && message[1]=='1'){send(c,&message,sizeof(message),0); break; }
		fgets(message,100,stdin);
		send(c,&message,sizeof(message),0);
		recv(c,&all,sizeof(all),0);
		printf("%s\n",all);
	}
	close(c);
}