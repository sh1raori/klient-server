#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <map>
#include <unistd.h>
#define adr "127.0.0.1"
using namespace std;

map<int,string> mp;

void write(int new_sock){
	char inf[1024];int n;
	read(new_sock, inf, sizeof(inf));
	string inn(inf);
	n = stoi(inn);
		bzero(inf,sizeof(inf));
	    map <int,string> :: iterator it;
	    it = mp.find(n);
	    strcpy(inf,(it->second).c_str());
		write(new_sock, inf, sizeof(inf));
}

void read(int new_sock){
	char inf[1024];int n;int key;string znach;
	for (;;){
		bzero(inf,sizeof(inf));
		read(new_sock, inf, sizeof(inf));
		if (strncmp("exit",inf,4) == 0){ break;}
		string inn(inf);
		key = stoi(inn.substr(0,inn.find(",")));
		znach = inn.substr(inn.find(",") + 1);
		mp[key] = znach;
	}
}

int main(int argc, char *argv[]){
	int listener, new_sock, sock;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buf[1024];char inf[1024];
	int bytes_read;

	if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket error");
		exit(1);
	}

	int port = stoi(argv[1]);
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(adr);


	if(bind(listener,(struct sockaddr *)&address,sizeof(address)) < 0){
		perror("bind error");
		exit(2);
	}

	listen (listener,1);
	
	if ((new_sock = accept(listener, NULL, NULL)) < 0){
		perror("accept error");
		exit(4);
	}

	// mp[1] = "a";mp[2] = "b";mp[3] = "c";


	read(new_sock);
	write(new_sock);
	// map <int,string> :: iterator it = mp.begin();
	// cout<<it->first<<" "<<it->second<<endl;
	close(new_sock);
	return 0;
}

