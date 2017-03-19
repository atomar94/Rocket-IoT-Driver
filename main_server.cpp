#include "Networking/server.h"
#include "Networking/client.h"

#include <utility>
#include <string>

using namespace std;

int main()
{
    Server s;

    pair<string, string> retval = s.read_request(8000);

    string method = retval.first;
    string path = retval.second;
    
}
