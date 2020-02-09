#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

void helpClient(int c){
	uint16_t len;
	recv(c, &len, sizeof(len), MSG_WAITALL);
	len = ntohs(len);
	char s[100];
	recv(c, s, len+1, MSG_WAITALL);
	printf("%s\n", s);
}

int main(){
	struct sockaddr_in server, client;
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		printf("Eroare la crearea socketului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(9696);
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (const struct sockaddr*)&server, sizeof(server)) < 0){
		printf("Eroare la bind\n");	
	}

	
	listen(s, 5);
	
	int l = sizeof(client);
	while(1){
		int c = accept(s, (struct sockaddr*)&client, &l);
		printf("S-a conectat un client\n");
		if(fork() == 0){
			helpClient(c);
			return 0;
		}

	}
	close(s);
	return 0;
}
