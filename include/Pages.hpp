#pragma once

enum class Pages 
{
    None,
    Home,
    Products,
    About,
    Contact,
    NotFound
};
inline const char *to_string(Pages page)
{
    static const char *names[] =
    {
        "None",
        "Home",
        "Products",
        "About",
        "Contact",
        "404"
    };

    return names[(int) page];
}
