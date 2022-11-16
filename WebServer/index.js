const express = require('express')
const mongoose =require('mongoose')
const cors = require('cors')
const bodyParser = require('body-parser')
const serverConfigs = require('./configs/server.json')

const app = express()

app.use(cors())
app.use(bodyParser.json())
app.use(express.static('public'))

/* my routers */
app.use('/registration', require('./routers/registrationRouter'))

app.get(['/', '/homepage(.html)?'], (req, resp) => {
    resp.redirect(`${serverConfigs.fullUrl}/views/homepage.html`)
})

app.get('/*', (req, resp) => {
    resp.redirect(`${serverConfigs.fullUrl}/views/404.html`)
})

mongoose.connect(serverConfigs.databaseUrl)
.then(resp => {
        console.log(`\nDatabase open on port ${serverConfigs.databasePort}\n`)

        app.listen(serverConfigs.port, serverConfigs.hostname, () => {
            console.log(`Server is listening on port [ ${serverConfigs.port} ]`)
        })
})
.catch(error => {
        console.error(error)
})
