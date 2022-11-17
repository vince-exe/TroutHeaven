const emailInput = document.getElementById('email_input')
emailInput.value = ""

const passwordInput = document.getElementById('pwd_input')
passwordInput.value = ""

const errorDiv = document.getElementById('error_text_div')
const errorText = document.getElementById('error_text')

const loginBtn = document.getElementById('login_btn')

const displayMessage = (message) => {
    errorDiv.style.display = 'flex'
    errorText.style.display = 'block'
    errorText.innerHTML = message
} 

window.addEventListener('keyup', (e) => {
    if (e.code === 'Enter') {
        loginBtn.click()
    }
})

loginBtn.addEventListener('click', () => {
    fetch('http://localhost:3000/login/api/v1/login', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(
            {
                'email': emailInput.value,
                'password': passwordInput.value
            })
    })
    .then(response => {
        switch(response.status) {
            case 422:
                displayMessage('Invalid credentials :/')
                break

            case 401:
                displayMessage('Email or password wrong')
                break

            case 200:
                window.location.href = '../views/homepage.html'
                break
        }
    })
    .catch(error => {
        displayMessage(error)
    })
})