//ClientUDP
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
	int sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockClient < 0){
		printf("eroare la crearea socketului client\n");
	}
	
	struct sockaddr_in server;

	memset(&server, 0 , sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8686);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int a, b, sum;
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	
	a = htonl(a);
	b = htonl(b);
	int l = sizeof(server);
	sendto(sockClient, &a, sizeof(a), 0, (struct sockaddr *)&server, sizeof(server));
	sendto(sockClient, &b, sizeof(b), 0, (struct sockaddr *)&server, sizeof(server));
	recvfrom(sockClient, &sum, sizeof(sum), 0, (struct sockaddr *)&server, &l);
	sum = ntohl(sum);

	printf("Suma e %d\n", sum);

	return 0;
}
