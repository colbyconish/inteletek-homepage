#include "HttpFilter.h"

using namespace drogon;

void InsecureFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    auto local_addr = req->getLocalAddr();
    if (local_addr.toPort() != (uint16_t) 443)
    {
        fcb(HttpResponse::newRedirectionResponse("https://inteletek.io"));
        return;
    }

    fccb();
}
