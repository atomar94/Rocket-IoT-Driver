//client.cpp

#include "arpa/inet.h"
#include "client.h"
#include "sys/types.h" //lseek
#include "sys/socket.h"
#include "netinet/in.h" //socket
#include <string>
#include <iostream>
#include "unistd.h"
#include "sstream"

using namespace std;

//send a post request to /identify with our name
void Client::identify(string ip_addr, int port, string name)
{
    stringstream json_name;
    // '{"name": "<name variable>"}'
    json_name << "'{\"name\": \"" << name << "\"}'";
    post(ip_addr, port, "/identify", json_name.str());
}

//send a post request to /update with some data.
//data needs to be jsonized already
void Client::update(string ip_addr, int port, string json_data)
{
    post(ip_addr, port, "/update", json_data);
}


void Client::get(string ip_addr, int port, string path)
{
    stringstream ss;
    ss << "GET " << path << " HTTP/1.1" << "\r\n";
    ss << "Host: Rocket-IoT-Driver" << "\r\n\r\n"; 
    
    write_to(ip_addr, port, ss.str());
}

//send json data via post request
//data should be jsonized already
void Client::post(string ip_addr, int port, string path, string data)
{
    stringstream ss;
    ss << "POST " << path << " HTTP/1.1\r\n";
    ss << "Host: Rocket-IoT-Driver\r\n";
    ss << "Content-Type: application/json\r\n";
    ss << "\r\n"; //end of header

    ss << data << "\r\n\r\n"; //end req.

    write_to(ip_addr, port, ss.str());
}

void Client::write_to(string ip_addr, int portnum, string msg)
{
    struct sockaddr_in serv_addr;
    int sockfd;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        //error
        return;
    }

    serv_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum); 

    if ( connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0 )
    {
        //error
        close(sockfd);
        return;
    }

    cout << "sending: " << msg << endl;
    if ( send(sockfd, msg.c_str(), msg.length(), 0) < 0)
    {
        //error
        close(sockfd);
        return;
    }
    
    char server_reply[512];//set this to 0
    if ( recv(sockfd, server_reply, 512, 0) < 0)
    {
        //error
        close(sockfd);
        return;
    }
    string stdstr = server_reply;
    cout << stdstr << endl;
    close(sockfd);
}
