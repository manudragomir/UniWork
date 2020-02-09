#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	
	int s;
	struct sockaddr_in server;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if(s < 0){
		printf("eroare la crearea socketului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(2233);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("10.152.3.119");

	int k = 25;
	k = ntohl(k);
	sendto(s, &k, sizeof(k), 0, (struct sockaddr *)&server, sizeof(server));
	
	int ss = socket(AF_INET, SOCK_STREAM, 0);
	if(ss < 0){
		printf("eroare la crearea clientului\n");
		return 1;
	}

	if(connect(ss, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("eroare la conectarea la server\n");
		return 1;
	}

	uint16_t nr;
	recv(ss, &nr, sizeof(nr), 0);
	printf("%hu\n", nr);
	nr = ntohs(nr);
	printf("%hu\n", nr);
	return 0;
}
