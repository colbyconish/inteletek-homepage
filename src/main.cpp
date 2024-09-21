#include <iostream>
#include <unistd.h>

#include <drogon/drogon.h>

using namespace drogon;

char DEFAULT_CONF_LOC[] = "/etc/webserver.json";
int main(int argc, char *argv[]) 
{
    char *conf_file = DEFAULT_CONF_LOC; 

    int c;
    while((c = getopt(argc, argv, "c:")) != -1)
    {
        switch(c)
        {
        case 'c':
            conf_file = optarg;
            break;
        case '?':
        case '*':
            std::cout << "Incorrect usage." << std::endl; 
            break;
        }
    }

    auto page404 = HttpResponse::newFileResponse("/www/404.html");
    app().loadConfigFile(conf_file);
    app().setCustom404Page(page404);
    app().run();
    return 0;
}
