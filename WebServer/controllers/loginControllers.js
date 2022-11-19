/* Database schema ( users ) */
const userSchema = require('../schema/userSchema')

const applicationConfigs = require('../configs/application.json')

const bcrypt = require('bcrypt')

const utilities = require('../utils/utilities')

exports.handleLogin = async (req, resp) => {
    if ((!req.body.email || !req.body.password) || !utilities.Utils.checkEmail(req.body.email, applicationConfigs.domainsArray)) {
        return resp.sendStatus(422)
    }
    if (req.body.email.length > applicationConfigs.emailLen || req.body.password.length > applicationConfigs.passwordLen) {
        return resp.sendStatus(422)
    }

    const result = await userSchema.findOne({ email: req.body.email })
    if(!result) {
        return resp.sendStatus(401)
    }
    
    const isMatch = await bcrypt.compare(req.body.password, result.password)
    if(!isMatch) {
        return resp.sendStatus(401)
    }

    resp.sendStatus(200)
}