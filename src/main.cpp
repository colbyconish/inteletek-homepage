#include <iostream>
#include <unistd.h>

#include <drogon/drogon.h>

#include "Pages.hpp"

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

    HttpViewData data;
    data.insert("page", Pages::NotFound);
    auto page404 = HttpResponse::newHttpViewResponse("notfound404.csp", data);
    app().loadConfigFile(conf_file);
    app().setCustom404Page(page404);
    app().run();
    return 0;
}
