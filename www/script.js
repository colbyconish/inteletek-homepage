async function send_form_data(form) {
    var form_data = new FormData(form);

    try 
    {
        var fullname = form_data.get("fullname");
        var email = form_data.get("email");;
        var message = form_data.get("message");;
        var url = `/contact/submit?fullname=${fullname}&email=${email}&message=${message}`;
        const response = await fetch(url, {method: "POST"});

        if (response.ok)
        {
            document.querySelector("#contact-main").classList.add("hidden");
            document.querySelector("#contact-thanks").classList.remove("hidden");
            document.querySelector("#contact-email").innerHTML = form_data.get("email");
            form.reset();
        }
    } 
    catch (e) 
    {
        console.error(e);
    }
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
