const serverConfigs = require('../configs/server.json')

const isAUTH = (req, resp, next) => {
    if(req.session.isAuth) {
        next();
    }

    /* redirect to the login page */
    resp.status(401).redirect(`${serverConfigs.fullUrl}/views/login.html`)
}

module.exports = isAUTH
