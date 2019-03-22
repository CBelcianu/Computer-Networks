#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
	printf("Eroare la crearea socketului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}
	listen(s, 5);
	l = sizeof(client);
	memset(&client, 0, sizeof(client));
	char all[1000];
	while (1) {
		c = accept(s, (struct sockaddr *) &client, &l);
		struct in_addr ipAddr = client.sin_addr;
		char str[INET_ADDRSTRLEN];
		inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
		printf("S-a conectat un client.\n");
		strcat(all,str);
		strcat(all," a spus: ");
		char m[100];
		int k=1;
		while(k){
			recv(c,&m,sizeof(m),0);
			if(m[0]=='-' && m[1]=='1'){ break; }
			strcat(all,m);
			send(c,&all,sizeof(all),0);
		}
		close(c);
	}

}