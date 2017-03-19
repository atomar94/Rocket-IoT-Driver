//client.h

#include <string>

#ifndef CLIENT_H
#define CLIENT_H

using namespace std;

class Client
{
    public:
        void identify(string ip_addr, int port, string name); //identify with the server who we are
        void update(string ip_addr, int port, string json_data);

    private:
        void write_to(string ip_addr, int portnum, string msg);
        void get(string ip_addr, int port, string path);
        void post(string ip_addr, int port, string path, string data);

};

#endif
