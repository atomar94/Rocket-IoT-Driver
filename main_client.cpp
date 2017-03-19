#include "server.h"
#include "client.h"

#include <utility>
#include <string>

using namespace std;

int main()
{
    Client c;

    c.get("127.0.0.1", 8000, "/identify");

}
