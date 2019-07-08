#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>  //standard symbolic constants and types (_POSIX2_C_VERSION, _POSIX2_CHAR_TERM,...)
#include<netdb.h>   //netdb.h - definitions for network database operations
#include<arpa/inet.h>   //arpa/inet.h - definitions for internet operations (struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna);)
#include<string.h>
using namespace std;

int main(){
    int listening = socket(AF_INET,SOCK_STREAM,0);
    if(listening==-1){
        cerr<<"Can't create socket";
        return -1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(12345);
    
    if(inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr)<=0)  
    { 
        cout<<("Address not supported \n"); 
        return -1; 
    } 
     if (connect(listening, (struct sockaddr *)&hint, sizeof(hint)) < 0) 
    { 
        cout<<("\nConnection Failed \n"); 
        return -1; 
    } 
    char buf[4096];
    string a;
    while(true){
        cout<<"> ";
        getline(cin,a);
        send(listening,a.c_str(),sizeof(a),0);
    }  
    close(listening);
    return 0;

}