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

void function(int c){
	uint16_t a, b, x;
	recv(c, &x, sizeof(x), MSG_WAITALL);
	recv(c, &a, sizeof(a), MSG_WAITALL);
	recv(c, &b, sizeof(b), MSG_WAITALL);
	x = ntohs(x);
	a = ntohs(a);
	b = ntohs(b);
	printf("%hu %hu %hu\n", x, a, b);
}

int main(int argc, char** argv){
	if(argc < 2){
	 	printf("Nr params invalid\n");
	        return 1;	
	}
	
	int port = atoi(argv[1]);
	
	struct sockaddr_in server, client;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		printf("eroare la crearea socketului server\n");
		return 1;
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("eroare la bind\n");
		return 1;
	}

	listen(s, 5);

	int c;
	int l = sizeof(client);
	memset(&client, 0, sizeof(client));
	while(1){
		c = accept(s, (struct sockaddr*) &client, &l);
		printf("S-a conectat un client\n");
		if(fork()==0){
			char *ip = inet_ntoa(client.sin_addr);
			uint16_t a, b, x;
			recv(c, &x, sizeof(x), MSG_WAITALL);
			recv(c, &a, sizeof(a), MSG_WAITALL);
			recv(c, &b, sizeof(b), MSG_WAITALL);
			x = ntohs(x);
			a = ntohs(a);
			b = ntohs(b);
			printf("%hu %hu %hu\n", x, a, b);
			uint16_t sum = a + b;			 
	
			int cc = socket(AF_INET, SOCK_DGRAM, 0);
			if(cc < 0){
				printf("eroare la crearea socketului client udp\n");
				return 1;
			}

		struct sockaddr_in toClient;
		toClient.sin_port = htons(x);
		toClient.sin_family = AF_INET;
		toClient.sin_addr.s_addr = inet_addr(ip);
		sendto(cc, &sum, sizeof(sum), 0, (struct sockaddr*) &toClient, sizeof(toClient));
		}

		close(c);
	}

	return 0;
}
