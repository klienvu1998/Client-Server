#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
	char message[256] = "Hello Guy";
	int server_socket = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr=INADDR_ANY;
	bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket,4);
	int client_socket;
	client_socket=accept(server_socket,NULL,NULL);
	send(client_socket,message,sizeof(message),0);
	return 0;
}
