const express = require('express')
const mongoose = require('mongoose')
const cors = require('cors')
const bodyParser = require('body-parser')
const expressSession = require('express-session')
const mongoDbSession = require('connect-mongodb-session')(expressSession)
const MongoDBStore = require('connect-mongodb-session')

const serverConfigs = require('./configs/server.json')

const app = express()

/* create the store and the session */
const store = new mongoDbSession({
    uri: serverConfigs.databaseUrl,
    collection: 'sessions'
})

app.use(expressSession({
    secret: 'idk how to use it',
    resave: false,
    saveUninitialized: false,
    store: store
}))

app.use(cors())
app.use(bodyParser.json())
app.use(express.static('public'))

/* routers ( no AUTH required ) */
app.use('/registration', require('./routers/registrationRouter'))
app.use('/login', require('./routers/loginRouter'))

app.get(['/', '/welcome(.html)?'], (req, resp) => {
    resp.redirect(`${serverConfigs.fullUrl}/views/welcome.html`)
})

app.get('/*', (req, resp) => {
    resp.redirect(`${serverConfigs.fullUrl}/views/404.html`)
})

/* middleware for authentication */
app.use(require('./middlewares/AUTH'))

/* routers ( AUTH required ) */
app.use('/homepage', require('./routers/homepageRouter'))

/* try to connect to the database */
mongoose.connect(serverConfigs.databaseUrl)
.then(() => {
        console.log(`\nDatabase open on port ${serverConfigs.databasePort}`)

        app.listen(serverConfigs.port, serverConfigs.hostname, () => {
            console.log(`Server is listening on port [ ${serverConfigs.port} ]`)
        })
})
.catch(reason => {
        console.log('Failed to connect to the database')
        console.error(reason)
        process.exit(1)
})
