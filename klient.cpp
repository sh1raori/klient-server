#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unistd.h>
#include <iostream>
#include <cstring>
#define adr "127.0.0.1"
#define port 8000

using namespace std;

void write(int sock){
	char inf[1024];int n;
	for (;;){
		bzero(inf,sizeof(inf));
		n = 0;
		while ((inf[n++] = getchar()) != '\n');
		write(sock, inf, sizeof(inf));
		if (strncmp("exit",inf,4) == 0){ break;}
	}
}

void read(int sock){
	int n = 0;char inf[1024];
	cout<<"Chto ishem?"<<endl;
	while ((inf[n++] = getchar()) != '\n');
	    write(sock,inf,sizeof(inf));
		bzero(inf,sizeof(inf));
		read(sock, inf, sizeof(inf));
		string h(inf);cout<<h;
}

int main(){
	int sock;
	struct sockaddr_in addr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket error");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(adr);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("connect error");
		exit(2);
	}
	
	write(sock);
	read(sock);
	close(sock);
	
}
