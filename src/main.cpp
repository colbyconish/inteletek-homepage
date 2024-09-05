#include <drogon/HttpAppFramework.h>

int main(int argc, char *argv[]) 
{
    drogon::app().loadConfigFile("/etc/webserver.json");
    drogon::app().run();
    return 0;
}
