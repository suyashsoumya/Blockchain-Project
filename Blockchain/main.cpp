#include "Block.h"
#include "Blockchain.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <Winsock2.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fstream>
#include <unistd.h>
#include <_types.h>
#include <thread>

using namespace std;

const int BUFFSIZE = 1024;
const int MAXLINK = 10;
const int DEFAULT_PORT = 8080;

char* get_file_name (char* buff) {
    char* file_name = buff + 5;
    char *space = strchr(file_name, ' ');
    *space = '\0';
    return file_name;
}

void deal_get_http(int connect_fd, char* buff) {
    char* file_name = get_file_name(buff);
    const char http_correct_header[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
    int res = write(connect_fd, http_correct_header, strlen(http_correct_header));
    if (res > 0) {
        cout<<"send success"<<endl;
    }
}

bool is_get_http(char* buff) {
    if (!strncmp(buff, "GET", 3)) {
        return true;
    }
    else {
        return false;
    }
}

void addingthread(char* buff, int connect_fd, int socket_fd, &Blockchain b){
    
    
    thread broadcast(broadcastthread, b, connect_fd);
    broadcast.detach();
    memset(buff, '\0', sizeof(buff));
    recv(connect_fd, buff, BUFFSIZE - 1, 0);
    cout<<buff<<endl;
    //
    time_t time1;
    b.addBlock(buff, time(&time1));
    //
    send(connect_fd, buff, sizeof(buff), 0);
    close(connect_fd);
    //close(socket_fd);
    
}

void broadcastthread(&Blockchain b, int connect_fd){
    
    
    sleep(30);
    char * s= b.returnBlockchainAsString();
    send(connect_fd, s, sizeof(s) ,0);
    // fill it with your output char * s = b.output();
}


int main(){

    Blockchain b(4); // pass in difficulty value
    
    cout << "Mining Block 0..." << endl;
    time_t time1;
    b.addBlock("Hello", time(&time1)); // pass in data & timestamp
    cout << "Mining Block 0 complete" << endl;

    cout << "Mining Block 1..." << endl;
    time_t time2;
    b.addBlock("Bye", time(&time2));
    cout << "Mining Block 1 complete" << endl;
    
    //b.displayBlockchain();
    cout << b.returnBlockchainAsString() << endl;
    
    // network
    
    
    int socket_fd, connect_fd;
    struct sockaddr_in servaddr;
    char buff[BUFFSIZE];
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        cout<<"create socket error"<<endl;
        return -1;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);
    
    if ( ::bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        cout<<"bind error"<<endl;
        return -1;
    }
    bool flag = true;
    while(flag){
        if (listen(socket_fd, MAXLINK) == -1) {
            cout<<"listen error"<<endl;
            flag  = false;
            break;
        }
        
        connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);
        if (connect_fd == -1) {
            cout<<"accept error"<<endl;
        }
        else {
            cout<<"Connect Success"<<endl;
            thread task(addingthread, buff, connect_fd, socket_fd);
            task.detach();
            
        }
    }
    
    close(connect_fd);
    close(socket_fd);
    
    // network end
    
    
    
    
    
    return 0;
}


//
