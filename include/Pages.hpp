#pragma once

#include <array>
#include <cstdint>
#include <strings.h>

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
    ""
};

inline const char *to_string(Pages page)
{
    return names.at((uint32_t) page);
}

inline Pages from_string(const char *name)
{
    for(int i = (int)Pages::Home;i < names.size();++i)
    {
        if(strcasecmp(names[i], name) == 0) 
            return (Pages) i;
    }

    return Pages::None;
}
