#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class InsecureFilter : public HttpFilter<InsecureFilter>
{
  public:
    InsecureFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

