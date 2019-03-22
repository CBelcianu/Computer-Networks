#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
	int c;
	struct sockaddr_in server;

	c = socket(AF_INET, SOCK_DGRAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//trimitere
	char sir[100];
	uint32_t count;
	printf("introduceti sirul: ");
	fgets(sir,100,stdin);
	sendto(c, &sir, sizeof(sir), 0, (struct sockaddr *) &server, sizeof(server));
	recvfrom(c, &count, sizeof(count), 0, (struct sockaddr *) &server, sizeof(server));
	
	printf("sirul are %d spatii\n",count);

	close(c);
}