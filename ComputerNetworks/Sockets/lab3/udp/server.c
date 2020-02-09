#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
	int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(serverSocket < 0){
		printf("Eroare la crearea socketului server\n");
		return 1;
	}

	struct sockaddr_in server, client;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(8686);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("eroare la bind\n");
		return 1;
	}

	int l = sizeof(client);
	memset(&client, 0, sizeof(client));
	
	while(1){
	int a, b;
	recvfrom(serverSocket, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*)&client, &l);
	recvfrom(serverSocket, &b, sizeof(b), MSG_WAITALL, (struct sockaddr*)&client, &l);
	a = ntohl(a);
	b = ntohl(b);

	int sum = a + b;

	printf("SUMA S_A CALCULAT!\n");
	sum = htonl(sum);
	sendto(serverSocket, &sum, sizeof(sum), 0, (struct sockaddr *)&client, sizeof(client));
	}
	return 0;
}
