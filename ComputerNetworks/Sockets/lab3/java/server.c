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
        server.sin_port = htons(1234);
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
                c = accept(s, (struct sockaddr *)&client, &l);
                printf("S-a conectat un client\n");
			
		/*
		recv(c, &nr, sizeof(nr), MSG_WAITALL);
                nr = ntohs(nr);
		nr = nr + 1;
		//printf("%hu\n", nr);
		nr = htons(nr);
		send(c, &nr, sizeof(nr), 0);
		*/

		char character;
		recv(c, &character, sizeof(character), MSG_WAITALL);
		printf("Caracterul primit e: %c\n", character);	
		
		int len;
		recv(c, &len, sizeof(len), MSG_WAITALL);
		len = ntohl(len);

		printf("Lungimea e: %d\n", len);
		
		char string[100];
		recv(c, string, len, 0);
		printf("Sirul e: %s\n", string);		
		
		//pun \0 
		string[len] = '\0';

		//Trimit caracterul primit inapoi
		send(c, &character, sizeof(character), 0);
		
		char newString[100];
		int k = 0;
		for(int i=0; i<len; i++){
			if(string[i] != character){
				newString[k++] = string[i];
			}
		}
		newString[k] = 0;
		printf("Sirul modificat e: %s\n", newString);	
		
		send(c, &newString, strlen(newString)+1, 0);
		printf("TRIMIS REZULTAT\n");
		close(c);

	}
	return 0;
}
