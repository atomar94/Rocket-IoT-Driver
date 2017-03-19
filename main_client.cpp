#include "Networking/server.h"
#include "Networking/client.h"

#include <utility>
#include <string>

using namespace std;

int main()
{
    Client c;

    c.identify("localhost", 8000, "vcb1");
}
