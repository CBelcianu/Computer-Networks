#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l, i;
	s = socket(AF_INET, SOCK_DGRAM, 0);
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

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	
	//tratare
	while(1){
		uint32_t array[100],n,suma=0;
		recvfrom(s, &n, sizeof(n), MSG_WAITALL, (struct sockaddr *) &client, &l);
		recvfrom(s, &array, sizeof(array), MSG_WAITALL, (struct sockaddr *) &client, &l);
		for(int i=0;i<n;i++)
			suma=suma+array[i];
		sendto(s, &suma, sizeof(suma), 0, (struct sockaddr *) &client, l);
		
		
	}
	close(s);
}