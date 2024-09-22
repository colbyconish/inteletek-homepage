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
                SetColorTheme(new_theme)
            });

