// Global cookie variable
var cookies = null

async function read_cookies()
{
    cookies = {};
    let decoded = decodeURIComponent(document.cookie).split(';');

    for(let i = 0;i < decoded.length; ++i)
    {
        let cookie_str = decoded[i].replace(/^\s+|\s+$/gm,'');
        let key_value = cookie_str.split('=');
        console.log(key_value)

        if(key_value.length != 2) continue;

        cookies[key_value[0]] = key_value[1];
    }

    return cookies
}

async function set_cookie(key, value)
{
    document.cookie = `${key} = ${value};`;

    if(cookies != null)
        cookies[key] = value;
}

async function get_cookie(key)
{
    if(cookies == null)
        read_cookies();

    return cookies[key];
}
