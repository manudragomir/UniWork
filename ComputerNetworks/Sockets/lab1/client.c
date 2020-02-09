#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(int argc, char** args){
	int c;
	struct sockaddr_in server;	

	c = socket(AF_INET, SOCK_STREAM, 0);
	if( c < 0 ){
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	if(argc < 3){
		printf("NU NU\n");
		return 1;
	}


	memset(&server, 0, sizeof(server));
	server.sin_port = htons(atoi(args[2]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(args[1])

	if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare la conectarea la server\n");
		return 1;
	}

	char s[100];
	uint16_t len, spaces;
	printf("Scrie un sir de caractere: ");
	fgets(s, 100, stdin);
	len = strlen(s);
	len = htons(len);
	send(c, &len, sizeof(len), 0);
	send(c, s, strlen(s)+1, 0);
	recv(c, &spaces, sizeof(spaces), 0);
	spaces = ntohs(spaces);
	printf("Number of spaces is %hu\n", spaces);
	close(c);
	return 0;
}
