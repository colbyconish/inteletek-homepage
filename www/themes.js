var auto_theme = true;
const Themes = Object.freeze({
    Dark:   Symbol("DarkTheme"),
    Light:  Symbol("LightTheme"),
});

function GetColorTheme()
{
    if(!window.matchMedia) return;
    if(window.matchMedia('(prefers-color-scheme: dark)').matches)
        return Themes.Dark; 
    else
        return Themes.Light;
}

function SetColorTheme(theme)
{
    if(theme == null) return;
    if(theme == Themes.Dark)
        document.body.dataset.bsTheme = "dark";
    else
        document.body.dataset.bsTheme = "light";
}

window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', event => {
    const new_theme = event.matches ? Themes.Dark : Themes.Light;
    if(auto_theme) SetColorTheme(new_theme);
});

$(document).ready(function() {
    const drop = document.getElementById('bd-theme');
    const button = drop.querySelector('button');
    const ul = drop.querySelector('ul');
    var last = ul.querySelector('.active');
    drop.addEventListener('hide.bs.dropdown', event => 
    {
        if(!event.clickEvent) return;

        var target = event.clickEvent.target;
        if(target.classList.contains('active')) 
            return;

        var theme = target.dataset.bsThemeValue;
        if(theme == null) 
                return;

        if(theme == 'auto')
        {
            auto_theme = true;
            SetColorTheme(GetColorTheme());
        }
        else if(theme == 'dark')
        {
            auto_theme = false;
            SetColorTheme(Themes.Dark);
        }
        else
        {
            auto_theme = false;
            SetColorTheme(Themes.Light);
        }

        var href = target.querySelector('use').href.baseVal;
        button.querySelector('use').href.baseVal = href

        last.classList.remove('active');
        target.classList.add('active');
        last = target;
    })

    hljs.highlightAll();
    if(auto_theme)
        SetColorTheme(GetColorTheme());
});
