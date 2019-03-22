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
	uint32_t array[100],suma, n;
	printf("n= "); scanf("%d",&n);
	for(int i=0;i<n;i++){
		printf("a[%d]= ",i);
		scanf("%d",&array[i]);
	}
	sendto(c, &n, sizeof(n), 0, (struct sockaddr *) &server, sizeof(server));
	sendto(c, &array, sizeof(array), 0, (struct sockaddr *) &server, sizeof(server));
	recvfrom(c, &suma, sizeof(suma), 0, (struct sockaddr *) &server, sizeof(server));
	printf("suma e %d",suma);

	close(c);
}