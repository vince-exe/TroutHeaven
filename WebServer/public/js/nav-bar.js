const hamburgher = document.querySelector('.hamburgher')

const mainNavBar = document.querySelector('.main-nav-bar')
const secondDiv = document.querySelector('.second-div')
const navListHeaders = document.querySelector('.nav-list-headers')

window.onresize = () => {
    if (window.innerWidth >= 800) {
        mainNavBar.classList.remove('active')
        secondDiv.classList.remove('active')
        navListHeaders.classList.remove('active')
    }
}

hamburgher.addEventListener('click', () => {
    mainNavBar.classList.toggle('active')
    secondDiv.classList.toggle('active')
    navListHeaders.classList.toggle('active')
})