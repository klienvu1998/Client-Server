#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>  //standard symbolic constants and types (_POSIX2_C_VERSION, _POSIX2_CHAR_TERM,...)
#include<netdb.h>   //netdb.h - definitions for network database operations
#include<arpa/inet.h>   //arpa/inet.h - definitions for internet operations (struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna);)
#include<string.h>
using namespace std;

int main(){
    //CREATE A SOCKET
    int listening = socket(AF_INET,SOCK_STREAM,0);
    if(listening==-1){
        cerr << "Can't create a socket";
        return -1;
    }
    //BIND THE SOCKET TO A IP/PORT
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(12345);
    hint.sin_addr.s_addr =INADDR_ANY;
    if(bind(listening,(sockaddr *) &hint,sizeof(hint))==-1){
        cerr<< "Can't bind";
        return -1;
    }
    //MARK THE SOCKET FOR LISTENING IN
    if(listen(listening,SOMAXCONN)==-1){
        cerr<<"Can't listen";
        return -1;
    }
    //ACCEPT A CALL
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);   //data byte count
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    int client_socket=accept(listening,(sockaddr*) &client,&clientSize);
    if(client_socket==-1){
        cerr<<"Problem with client connecting";
        return -1;
    }
    close(listening);
    memset(host,0,NI_MAXHOST);  //clear host
    memset(svc,0,NI_MAXSERV);   //clear service

    int result = getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0); //translate a socket address to a node name and service location
    if(result){
        cout<<host<<" connected on "<<svc<<endl;
    }
    else{
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);  //Convert to a String
        cout<<host<< " connected on "<<ntohs(client.sin_port)<<endl;
    }
    //WHILE RECERIVING - DISPLAY MESSAGE, ECHO MESSAGE
    char buf[4096];
    while(true){
        //CLEAR BUFFER
        memset(buf,0,4096);
        //WAIT FOR MESSAGE
        int bytesRecv = recv(client_socket,buf,4096,0);
        if(bytesRecv==-1){
            cerr<<"There was a connection error"<<endl;
            break;
        }
        if(bytesRecv==0){
            cerr<<"Client disconnected"<<endl;
            break;
        }
        //DISPLAY MESSAGE
        cout<<"Received: "<<string(buf,0,bytesRecv)<<endl;
        //RESENT MESSAGE
        send(client_socket,buf,bytesRecv+1,0);
    }
    close(client_socket);
    return 0;
}