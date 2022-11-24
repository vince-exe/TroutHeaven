const bcrypt = require('bcrypt')

const userSchema = require('../schema/userSchema')

exports.isAUTH = (req, resp, next) => {
    if(req.session.isAuth) {
        return next();
    }

    return resp.sendStatus(401)
}
