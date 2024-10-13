#pragma once

#include <array>

enum class Pages 
{
    None,
    Home,
    Services,
    About,
    Contact,
    NotFound
};

static std::array names
{
    "None",
    "Home",
    "Services",
    "About",
    "Contact",
    "404"
};

inline const char *to_string(Pages page)
{
    return names.at((uint32_t) page);
}

inline Pages from_string(const char *name)
{

    uint32_t i = 0;
    for(auto &str : names)
    {
        if(strcasecmp(str, name) == 0) return (Pages) i;
        i++;
    }

    return (Pages) 0;
}
