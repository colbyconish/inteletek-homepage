async function show_failure() {
    const popup_container = document.querySelector("#popup-container");
    const popup_template = document.querySelector("#popup-template");

    var pop_up = popup_template.cloneNode(true);
    pop_up.classList.add("alert-danger");
    pop_up.classList.remove("hidden")
    popup_container.appendChild(pop_up);

    var alert = new bootstrap.Alert(pop_up);
    setTimeout(function(alert) { alert.close(); }, 3000, alert);
}

async function send_form_data(form) {
    form.querySelector("button").disabled = true;

    var form_data = new FormData(form);
    try 
    {
        var fullname = form_data.get("fullname");
        var email = form_data.get("email");
        var message = form_data.get("message");
        var url = `/contact?fullname=${fullname}&email=${email}&message=${message}`;

        const response = await fetch(url, {method: "POST"});
        if (response.ok)
        {
            // Hide imput form
            document.querySelector("#contact-main").classList.add("hidden");

            // Show thanks message
            document.querySelector("#contact-email").innerHTML = form_data.get("email");
            document.querySelector("#contact-thanks").classList.remove("hidden");
            form.reset();
        }
        else
            show_failure();
    } 
    catch (e) 
    {
        console.error(e);
        show_failure();
    }

    form.querySelector("button").disabled = false;
}

const themes = ['light', 'dark'];
function setTheme(toggle = false) {
    let theme = localStorage.getItem('bs-theme');
    if(theme === null)
    {
        const system_light = window.matchMedia('(prefers-color-scheme: light)').matches;
        theme = system_light ? 0 : 1;
    }
    else
        theme = parseInt(theme);

    if(toggle) 
    {
        document.querySelector(`#svg-${themes[theme]}`).classList.add('hidden');
        theme = (1 - theme);
    }
    
    const theme_str = themes[theme];
    localStorage.setItem('bs-theme', theme);

    // Set theme for bootstrap
    document.documentElement.setAttribute('data-bs-theme', theme_str);

    // Toggle svg image
    document.querySelector(`#svg-${theme_str}`).classList.remove('hidden');
}

// Setup forms
(() => {
  'use strict'

  // Fetch all the forms we want to apply custom Bootstrap validation styles to
  const forms = document.querySelectorAll('.needs-validation')

  // Loop over them and prevent submission
  Array.from(forms).forEach(form => {
    form.addEventListener('submit', event => {
      event.preventDefault()

      if (!form.checkValidity()) 
      {
        event.stopPropagation()
      }
      else
      {
        send_form_data(form);
      }

      form.classList.add('was-validated')
    }, false)
  })
})()

// Setup theme
window.matchMedia('(prefers-color-scheme: light)').addEventListener('change', () => setTheme(true));
window.addEventListener('load', () => setTheme() )
