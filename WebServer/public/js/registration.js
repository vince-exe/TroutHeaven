const emailInput = document.getElementById('email_input')
emailInput.value = ""

const passwordInput = document.getElementById('pwd_input')
passwordInput.value = ""

const nicknameInput = document.getElementById('nickname_input')
nicknameInput.value = ""

const errorDiv = document.getElementById('error_text_div')
const errorText = document.getElementById('error_text')

const registrationBtn = document.getElementById('register_btn')

const displayMessage = (message) => {
    errorDiv.style.display = 'flex'
    errorText.style.display = 'block'
    errorText.innerHTML = message
} 

window.addEventListener('keyup', (e) => {
    if (e.code === 'Enter') {
        registrationBtn.click()
    }
})

registrationBtn.addEventListener('click', () => {
    fetch('http://localhost:3000/registration/api/v1/registration', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(
            { 
                'email': emailInput.value,
                'password': passwordInput.value,
                'nickname': nicknameInput.value
            })
    })
    .then(response => {
        switch(response.status) {
            case 422:
                displayMessage('Invalid credentials :/')
                break

            case 409:
                displayMessage('There is already an account with this email')
                break

            case 410:
                displayMessage('There is already an account with this nickname')
                break

            case 200:
                console.log('success')
                break
        }
    })
    .catch(error => {
        displayMessage(error)
    })
})
