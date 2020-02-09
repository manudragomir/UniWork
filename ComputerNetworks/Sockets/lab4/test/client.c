#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc < 3){
		printf("Nr params invalid\n");
		return 1;
	}

	int c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	int port = atoi(argv[2]);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	
	if(connect(c, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("eroare la conectarea la server\n");
		return 1;
	}
	
	uint16_t x, a, b;
	printf("x = ");
	scanf("%hu", &x);

	printf("a = ");
	scanf("%hu", &a);

	printf("b = ");
	scanf("%hu", &b);

	x = htons(x);
	a = htons(a);
	b = htons(b);

	send(c, &x, sizeof(x), 0);
	send(c, &a, sizeof(a), 0);
	send(c, &b, sizeof(b), 0);
	
	struct sockaddr_in serverUdp;
	int sudp = socket(AF_INET, SOCK_DGRAM, 0);
	if(sudp < 0){
		printf("eroare la crearea socketului udp\n");
		return 1;
	}

	memset(&serverUdp, 0, sizeof(serverUdp));
	serverUdp.sin_port = x;
	serverUdp.sin_family = AF_INET;
	serverUdp.sin_addr.s_addr = INADDR_ANY;

	if(bind(sudp, (struct sockaddr*)&serverUdp, sizeof(serverUdp)) < 0){
		printf("eroare la bind\n");
		return 1;
	}

	uint16_t suma;
	struct sockaddr_in altClient;
	int ll = sizeof(altClient);
	recvfrom(sudp, &suma, sizeof(suma), MSG_WAITALL, (struct sockaddr*)&altClient, &ll);
	
	printf("%hu\n", suma);
	close(c);
	return 0;
}

