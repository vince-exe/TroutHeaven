const table = document.getElementById('table')

const addPlayer = (nickname, score, money) => {
    let row = table.insertRow(-1)
    row.className = 'table-row-content'

    let cellNickname = row.insertCell(0)
    cellNickname.className = 'table-div'

    let cellScore = row.insertCell(1)
    cellScore.className = 'table-div'

    let cellMoney = row.insertCell(2)
    cellMoney.className = 'table-div'

    cellNickname.innerHTML = nickname
    cellScore.innerHTML = score
    cellMoney.innerHTML = money
}

/* request to get the players list */
fetch('http://localhost:3000/homepage/api/v1/get-players')
.then(response => {
    
    if(response.status == 401) {
        return window.location.replace('http://localhost:3000/views/login.html')
    }

    response.text().then(value => {
        let playerArray = JSON.parse(value).playersList
        
        playerArray.forEach(player => {
            addPlayer(player.nickname, player.score, player.money)
        })
    })
})
.catch(error => {
    console.error(error)
})