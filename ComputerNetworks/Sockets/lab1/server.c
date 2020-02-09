#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		printf("Eroare la crearea socketului server\n");
		return 1;
	}	

	struct sockaddr_in server, client;
	

	memset(&server, 0, sizeof(server)); 
	server.sin_port = htons(9696);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(s, (struct sockaddr*) &server, sizeof(server)) < 0){
		printf("Eroare la BIND\n");
		return 1;
	}


	listen(s, 5);
	int l = sizeof(client);
	memset(&client, 0, sizeof(client));

	int c;
	while(1){
		uint16_t len, spaces = 0;
	        char str[100];	
		c = accept(s, (struct sockaddr *)&client, &l);
		printf("S-a conectat un client\n");
		
		recv(c, &len, sizeof(len), MSG_WAITALL);
		len = ntohs(len);
		recv(c, str, len+1, MSG_WAITALL);

			
		for(int i=0; i<len; i++){
			if(str[i] == ' '){
				++spaces;
			}
		}
		
		spaces = htons(spaces);
		send(c, &spaces, sizeof(spaces), 0);
		close(c);	
		
	}	
	return 0;
}
