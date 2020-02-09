#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char** argv){
	if(argc <= 2){
		printf("Nu-i ok!\n");
		return 1;
	}

	const char *ipAddr = argv[1];
	const int port = atoi(argv[2]);
	
	int c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
		printf("eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ipAddr);

	if(connect(c, (struct sockaddr*)&server, sizeof(server)) < 0){
		printf("eroare la conectarea la server\n");
		return 1;
	}
	
	char s[100];
	printf("introdu un string: ");
	scanf("%s", s);
	uint16_t len = strlen(s);
	len = htons(len);
	send(c, &len, sizeof(len), 0);
	send(c, s, strlen(s) + 1, 0);
	close(c);
	return 0;
}
